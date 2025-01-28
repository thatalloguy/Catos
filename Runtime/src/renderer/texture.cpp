//
// Created by allos on 11/12/2024.
//

#include "texture.h"
#include "spdlog/spdlog.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>


void catos::Texture::init(catos::TextureCreationInfo &creationInfo) {

    glGenTextures(1, &textureGPUId);
    glBindTexture((GLenum) creationInfo.type, textureGPUId);

    glTexParameteri((GLenum) creationInfo.type, GL_TEXTURE_WRAP_S, (GLint) creationInfo.wrapX);
    glTexParameteri((GLenum) creationInfo.type, GL_TEXTURE_WRAP_T, (GLint) creationInfo.wrapY);
    if (creationInfo.type == TextureType::TEXTURE_3D) {
        glTexParameteri((GLenum) creationInfo.type, GL_TEXTURE_WRAP_R, (GLint) creationInfo.wrapZ);
    }


    glTexParameteri((GLenum) creationInfo.type, GL_TEXTURE_MIN_FILTER, (GLint) creationInfo.minFilter);
    glTexParameteri((GLenum) creationInfo.type, GL_TEXTURE_MAG_FILTER, (GLint) creationInfo.magFilter);

    stbi_set_flip_vertically_on_load(creationInfo.flip_vertically);

    _type = creationInfo.type;

    unsigned char* data = nullptr;

    if (creationInfo.source.path != nullptr) {
        data = stbi_load(creationInfo.source.path, &width, &height, &nrChannels, 0);
    } else if (creationInfo.source.buffer != nullptr) {
        data = stbi_load_from_memory(creationInfo.source.buffer, creationInfo.source.buf_len,
                                     &width, &height, &nrChannels, 0);
    } else {
        spdlog::warn("Invalid texture source");
    }
    if (data) {

        glTexImage2D((GLenum) creationInfo.type, 0, (GLint) creationInfo.color, width, height, 0, (GLenum) creationInfo.color, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap((GLenum) creationInfo.type);

    } else {
        // uh oh
        spdlog::error("Could not load Texture: {}", creationInfo.source.path);
        glDeleteTextures(1, &textureGPUId);
    }

    stbi_image_free(data);

    spdlog::info("TEX: {}", textureGPUId);
}

void catos::Texture::bind(int slot) {
    glActiveTexture(slot);
    glBindTexture((GLenum) _type, textureGPUId);
}

catos::Texture::~Texture() {
    glDeleteTextures(1, &textureGPUId);
}