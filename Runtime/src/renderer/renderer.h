//
// Created by allos on 10/16/2024.
//

#pragma once

#include <renderer/renderPipeline.h>

namespace catos {

    enum class RenderBackendType: unsigned int {
        UNKNOWN = 0,
        OPENGL_4_2 = 1,
    };

    enum RenderStatus: unsigned int {
        SUCCESSFUL = 0,

        RENDERER_ALREADY_INITIALIZED = 1,
    };


    struct RendererCreateInfo {
        RenderBackendType backendType = RenderBackendType::OPENGL_4_2;
    };


    class Renderer {

    public:

        static Renderer& getInstance();
        ~Renderer();

        RenderStatus init(const RendererCreateInfo& createInfo);

        RenderStatus renderObjects(const RenderPipeline& pipeline, void* data, unsigned int objectAmount);


    private:
        bool initialized = false;

    };

}


#endif //CATOS_RENDERER_H
