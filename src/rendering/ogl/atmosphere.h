#pragma once

#include "opengl.h"

#include "structures/texture.h"
#include "structures/shader.h"

#include "window.h"

class atmosphere
{
public:
	atmosphere() :
		transmittanceBuilder("assets/sky/transmittanceLUT.csh"),
		singleScattering("assets/sky/generateLUT.csh"),
		atmosphereShader("assets/sky/atmosphere.vs", "assets/sky/atmosphere.fs"),
		scatterLut(tex_filter::Linear, tex_type::Tex3D, tex_wrap::Clamp),
		tLut(tex_filter::Linear, tex_type::Tex2D, tex_wrap::Clamp)
	{
		tLut.allocate(256, 64, 1, tex_format::RGBA32);
		scatterLut.allocate3D(128, 512, 512, 1, tex_format::RGBA16);
	}

	void runTransmittance()
	{
		transmittanceBuilder.bind();
		glBindImageTexture(2, tLut.getID(), 0, GL_FALSE, 0, GL_WRITE_ONLY, static_cast<GLenum>(tex_format::RGBA32));
		glDispatchCompute(256 / 32, 64 / 32, 1);

		glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
		
		singleScattering.bind();
		tLut.bind(1);
		glBindImageTexture(0, scatterLut.getID(), 0, GL_FALSE, 0, GL_WRITE_ONLY, static_cast<GLenum>(tex_format::RGBA16));
		glDispatchCompute(128 / 8, 512 / 8, 512 / 8);
		

	}


	float pitch = 0.0;
	float yaw = 0.0;

	f32 c = 0;
	void render(f32 clock)
	{
		pitch += glfwGetKey(window::windo, GLFW_KEY_W) * 0.01f;
		pitch -= glfwGetKey(window::windo, GLFW_KEY_S) * 0.01f;
		yaw += glfwGetKey(window::windo, GLFW_KEY_D) * 0.01f;
		yaw -= glfwGetKey(window::windo, GLFW_KEY_A) * 0.01f;

		scatterLut.bind(0);
		c += clock;
		atmosphereShader.bind();
		auto view = glm::inverse(view_matrix({ 0, 20, 0 }, yaw, pitch));
		auto proj = glm::inverse(projection_matrix(glm::radians(50.0f), 1280.0f / 720.0f, 0.01f, 2000.0f));
		atmosphereShader.uniform("viewInv", view);
		atmosphereShader.uniform("projInv", proj);
		atmosphereShader.uniform("camPos", { 0, 20, 0 });
		atmosphereShader.uniform("sunDirection", glm::normalize(glm::axis(glm::quat({ 0, 3.1415, clock}))));
		glDisable(GL_DEPTH_TEST);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}

private:
	texture tLut;
	texture scatterLut;

	shader transmittanceBuilder;
	shader singleScattering;
	shader atmosphereShader;
	//shader initialLUT;
	//shader iterateLUT;
};