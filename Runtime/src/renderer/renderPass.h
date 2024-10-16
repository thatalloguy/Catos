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

    enum PassType: unsigned int {
        COLOR =  0x8CE0,
        COLOR_SINGLE = 0x8CE1,
        DEPTH = 0x8D00,
        STENCIL = 0x8D20,
    };

    struct RenderPassCreationInfo {
        //If the Pass will be presented to the Window.
        bool willBeVisible = false;

        //The size of the Pass's image
        Vector2 size{512, 512};

        //If the pass should resize to the global Render size.
        bool resizeToRenderSize = false;

        PassType passType = PassType::COLOR;

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

        bool isFinal() { return _isFinal; };

    private:

        void generateFrameBuffer(const Vector2& size);
        void generateColorBuffer(const Vector2& size, PassType type);
        void generateRenderBuffer(const Vector2& size);


        unsigned int frameBuffer;
        unsigned int colorBuffer;
        unsigned int renderBuffer;

        bool _isFinal = false;
        bool _shouldResize = false;

        Shader& shader;

    };


}