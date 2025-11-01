//
// Created by allos on 10/16/2024.
//
#pragma once

#include <math/vecs.h>
#include <renderer/shader.h>

#include "math/matrix4.h"
#include "mesh.h"
#include "stl/string.h"
#include "loaders.h"

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

    enum ColorType: unsigned int {
        RGB = 0x1907,
        DEPTH_IMG  =  0x1902,
    };

    enum ImageType {
        IMG_2D = 0x0DE1,
        IMG_ARRAY = 0x8C1A,
    };

    struct RenderPassLogic {

        virtual ~RenderPassLogic() = default;

        virtual void onPassPrepare(RenderPass& pass, Matrix4& camera_matrix) {};
        virtual void onPassEnd(RenderPass& pass) {};


        virtual void onMeshPrepare(RenderPass& pass, Mesh& mesh) {};
        virtual void onMeshEnd(RenderPass& pass, Mesh& mesh) {};

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
        ColorType colorType = ColorType::RGB;
        ImageType imageType = ImageType::IMG_2D;

        int textureAmount = 1;

        RenderPass* next = nullptr;
        string&& name = "None";

        RenderPassLogic* passLogic = nullptr;

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
        bool shouldResize() { return _shouldResize; };

        PassType getPassType() { return _passType; };
        ColorType getColorType() { return _colorType; };
        ImageType getImageType() { return _imageType; };
        int getTexAmount() { return _tex_amount; };

        string& getName() { return name; };
        RenderPass* getNext() { return next; };
        Vector2 getSize() { return _size; };
        RenderPassLogic* getRenderPassLogic() { return _render_logic; };

        void destroyTextures();
        void setSize(const Vector2& newSize);

        void generateFrameBuffer(const Vector2& size);
        void generateColorBuffer(const Vector2& size, PassType type, ColorType colorType, ImageType imageType, int tex_amount);
        void generateRenderBuffer(const Vector2& size);

    private:

        unsigned int frameBuffer;
        unsigned int colorBuffer;
        unsigned int renderBuffer;

        Vector2 _size;

        bool _isFinal = false;
        bool _shouldResize = false;

        PassType _passType;
        ColorType _colorType;
        ImageType _imageType;
        int _tex_amount = 0;

        Shader& shader;
        RenderPassLogic* _render_logic;


        RenderPass* next = nullptr;
        string name = "None";

    };


}