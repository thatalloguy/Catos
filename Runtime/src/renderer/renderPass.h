//
// Created by allos on 10/16/2024.
//
#pragma once

#include <math/vecs.h>
#include <renderer/shader.h>

using namespace catos::math;

namespace catos {

    typedef unsigned int ColorBuffer;
    typedef unsigned int FrameBuffer;
    typedef unsigned int RenderBuffer;

    struct RenderPassCreationInfo {
        //If the Pass will be presented to the Window.
        bool willBeVisible = false;

        //The size of the Pass's image
        Vector2 size{512, 512};

        //If the pass should resize to the global Render size.
        bool resizeToRenderSize = false;

        bool genColorAttachment = true;
        bool genDepthAttachment = true;
        bool genStencilAttachment = false;

    };

    class RenderPass {

    public:

        RenderPass(const RenderPassCreationInfo& info, Shader& shaderToUse);
        ~RenderPass();

        void bindPass();
        void unbindPass();

        FrameBuffer getFrameBuffer() { return frameBuffer; };
        ColorBuffer getPassTexture() { return colorBuffer; };
        RenderBuffer getRenderBuffer() { return renderBuffer; };

    private:

        void generateBuffers();
        void destroyBuffers();

        unsigned int frameBuffer;
        unsigned int colorBuffer;
        unsigned int renderBuffer;

        Shader& shader;

    };


}