#include "Renderer.h"

ag::Renderer::Renderer(std::shared_ptr<ag::RenderEngine> engine, std::shared_ptr<ag::SceneBuilder> scene)
{
    renderEngine = engine;
    sceneBuilder = scene;
}

void ag::Renderer::Render()
{
    /// TODO: CULL GRAPH
    /// TODO: Sort graph by model/material
    /// TODO: manage new resources to load/unload old resources
    renderEngine->Render(sceneBuilder->StartGraphRead());
    
    // SwapBuffers()

    sceneBuilder->EndGraphRead();
}
