//
// Created by allos on 10/16/2024.
//
#pragma once

#include <math/vecs.h>
#include <renderer/shader.h>

#include "stl/string.h"

using namespace catos::math;

namespace catos {
    class RenderPass;

    typedef unsigned int ColorBuffer;
    typedef unsigned int FrameBuffer;
    typedef unsigned int RenderBuffer;

    /// What kind of type the Pass Should be
    enum PassType: unsigned int {
        /// All colors
        COLOR =  0x8CE0,
        /// 1 single color support
        COLOR_SINGLE = 0x8CE1,

        DEPTH = 0x8D00,
        STENCIL = 0x8D20,
    };

    enum ImageType: unsigned int {
        RGB = 0x1907,
        DEPTH_IMG  =  0x1902,
    };

    ///Info about how the RenderPass should be created
    struct RenderPassCreationInfo {
        /// If the Pass will be presented to the Window.
        bool willBeVisible = false;

        /// The size of the Pass's image
        Vector2 size{512, 512};

        /// If the pass should resize to the global Render size.
        bool resizeToRenderSize = false;

        PassType passType = PassType::COLOR;
        ImageType imageType = ImageType::RGB;

        RenderPass* next = nullptr;
        string&& name = "None";

    };

    /* a RenderPass is a object that renders everything with a given shader
     * This then generates a texture which can be used for displaying or info for a different pass / shader.
     */
    class RenderPass {

    public:

        RenderPass(const RenderPassCreationInfo& info, Shader& shaderToUse);
        ~RenderPass();

        /// Binds and cleans the pass
        void bindPass();
        /// UnBinds and cleans the pass.
        void unbindPass();

        FrameBuffer getFrameBuffer() { return frameBuffer; };
        ColorBuffer getPassTexture() { return colorBuffer; };
        RenderBuffer getRenderBuffer() { return renderBuffer; };

        Shader& getShader() { return shader; };

        /// isFinal is wether or not the User will see this texture.
        bool isFinal() { return _isFinal; };

        string& getName() { return name; };
        RenderPass* getNext() { return next; };

        Vector2 getSize() { return _size; };

    private:

        void generateFrameBuffer(const Vector2& size);
        void generateColorBuffer(const Vector2& size, PassType type, ImageType imageType);
        void generateRenderBuffer(const Vector2& size);


        unsigned int frameBuffer;
        unsigned int colorBuffer;
        unsigned int renderBuffer;

        Vector2 _size;

        bool _isFinal = false;
        bool _shouldResize = false;

        Shader& shader;
        RenderPass* next = nullptr;
        string name = "None";

    };


}