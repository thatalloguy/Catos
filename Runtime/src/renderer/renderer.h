//
// Created by allos on 10/16/2024.
//

#pragma once

#include <renderer/renderPipeline.h>
#include <renderer/renderPass.h>

namespace catos {

    /// What backend the renderer should use. NOTE: ONLY OPENGL 4.2 SUPPORTED
    enum class RenderBackendType: unsigned int {
        UNKNOWN = 0,
        OPENGL_4_2 = 1,
    };

    /// The statuses of the renderer's operation.
    enum RenderStatus: unsigned int {
        SUCCESSFUL = 0,

        RENDERER_ALREADY_INITIALIZED = 1,
    };


    struct RendererCreateInfo {
        RenderBackendType backendType = RenderBackendType::OPENGL_4_2;
    };


    /// The renderer is the Master class that handles everything getting drawn properly.
    class Renderer {

    public:

        /// Singleton
        static Renderer& getInstance();
        ~Renderer();

        /// If the renderer isnt already initialized then it initializes.
        RenderStatus init(const RendererCreateInfo& createInfo);

        /// Renders all objects via the pipeline given.
        RenderStatus renderObjects(const RenderPipeline& pipeline, void* data, unsigned int objectAmount);

        /// Renders the given pass to the screen. NOTE: its public for overriding.
        RenderStatus renderPassToScreen(RenderPass& pass);


    private:

        void setupFinalRenderPlane();

        bool initialized = false;

        unsigned int renderVAO;
        unsigned int renderVBO;
        Shader screenShader;

    };

}

