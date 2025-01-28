//
// Created by allos on 11/12/2024.
//
#pragma once

#include <glad/glad.h>
#include <math/vecs.h>


using namespace catos::math;

namespace catos {

    struct TextureSource {
        const char* path = nullptr;
        const unsigned char* buffer = nullptr;
        size_t buf_len = 0;
    };

    enum class TextureWrapType {
        REPEAT = GL_REPEAT,
        REPEAT_MIRRORED = GL_MIRRORED_REPEAT,
        CLAMP_TO_EDGE = GL_CLAMP_TO_EDGE,
        CLAMP_TO_BORDER = GL_CLAMP_TO_BORDER
    };

    enum class TextureType {
        TEXTURE_2D = GL_TEXTURE_2D,
        TEXTURE_3D = GL_TEXTURE_3D,
    };

    enum class FilterType {
        LINEAR = GL_LINEAR,
        NEAREST = GL_NEAREST,
        MIP_MAP_LINEAR = GL_LINEAR_MIPMAP_LINEAR,
        MIP_MAP_NEAREST = GL_NEAREST_MIPMAP_NEAREST,
    };

    enum class TextureColor {
        RGB = GL_RGB,
        RGBA = GL_RGBA
    };

    struct TextureCreationInfo {
        TextureSource source{};

        bool flip_vertically = true;

        TextureWrapType wrapX = TextureWrapType::REPEAT; // s
        TextureWrapType wrapY = TextureWrapType::REPEAT; // t
        TextureWrapType wrapZ = TextureWrapType::REPEAT; // r

        float borderColor[4] = {1.0f, 1.0f, 1.0f, 1.0f};

        FilterType minFilter = FilterType::LINEAR;
        FilterType magFilter = FilterType::LINEAR;

        TextureColor color = TextureColor::RGB;
        TextureType type = TextureType::TEXTURE_2D;
    };

    class Texture {

    public:
        Texture() {};
        ~Texture();

        void init(TextureCreationInfo& creationInfo);

        void bind(int slot = 0x84C1);

        Vector2 getSize() { return Vector2{(float) width, (float) height}; };
        int getNrChannels() { return nrChannels; };


    private:
        unsigned int textureGPUId = -1;

        int width, height, nrChannels = 0;
        TextureType _type;

    };

}