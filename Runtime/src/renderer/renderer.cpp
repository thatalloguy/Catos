//
// Created by allos on 10/16/2024.
//

#include "renderer.h"

catos::Renderer &catos::Renderer::getInstance() {
    static Renderer _instance{};

    return _instance;
}

catos::Renderer::~Renderer() {

}

catos::RenderStatus catos::Renderer::init(const catos::RendererCreateInfo &createInfo) {

    if (initialized) {
        return RenderStatus::RENDERER_ALREADY_INITIALIZED;
    }


    // do init stuff


    return RenderStatus::SUCCESSFUL;
}


catos::RenderStatus catos::Renderer::renderObjects(const catos::RenderPipeline &pipeline, void *data, unsigned int objectAmount) {

    //do stuff.

    return RenderStatus::SUCCESSFUL;
}
