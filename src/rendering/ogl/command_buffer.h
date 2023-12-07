#pragma once

#include "rendering/ogl/buffer.h"

#include "lib/vector.h"

struct indirect_draw_command
{
	u32 indexCount;
	u32 instanceCount;
	u32 firstIndex; // Location of the first index in the EBO
	u32 baseVertex; // Offset into the VBO of the first vertex
	u32 baseInstance; // Offset into instanced attributes
};

class command_buffer
{
public:
	command_buffer();

	/**
	 * Pushes a command to the buffer.
	 * @param cmd the command
	*/
	void push(indirect_draw_command&& cmd);

	/**
	 * Submits the buffer to the GPU
	*/
	void submit();

	/**
	 * Binds the buffer as the current command buffer.
	*/
	void bind();


private:
	buffer buf;

	vector<indirect_draw_command> cmds;
};