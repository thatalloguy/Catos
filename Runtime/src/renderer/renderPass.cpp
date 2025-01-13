//
// Created by allos on 10/16/2024.
//

#include "renderPass.h"
#include "spdlog/spdlog.h"
#include <glad/glad.h>

catos::RenderPass::RenderPass(const catos::RenderPassCreationInfo &info, catos::Shader &shaderToUse) : shader(shaderToUse) {

    _isFinal = info.willBeVisible;

    _render_logic = info.passLogic;

    _shouldResize = info.resizeToRenderSize;

    _passType = info.passType;
    _colorType = info.colorType;
    _imageType = info.imageType;
    _tex_amount = info.textureAmount;

    _size = info.size;

    generateFrameBuffer(info.size);

    generateColorBuffer(info.size, info.passType, info.colorType, info.imageType, info.textureAmount);

    if (info.passType != PassType::DEPTH) {
        generateRenderBuffer(info.size);
    }

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        spdlog::error("Error creating RenderPass");
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    next = info.next;
    name = info.name;

}

catos::RenderPass::~RenderPass() {
    glDeleteRenderbuffers(1, &renderBuffer);
    glDeleteFramebuffers(1, &frameBuffer);

    delete _render_logic;
}


void catos::RenderPass::destroyTextures(){
    glDeleteRenderbuffers(1, &renderBuffer);
    glDeleteFramebuffers(1, &frameBuffer);
}

void catos::RenderPass::setSize(const Vector2& newSize) {
    _size = newSize;
}

void catos::RenderPass::generateFrameBuffer(const Vector2 &size) {
    glGenFramebuffers(1, &frameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
}

void catos::RenderPass::generateColorBuffer(const Vector2 &size, PassType type, ColorType colorType, ImageType imageType, int tex_amount) {
    glGenTextures(1, &colorBuffer);

    glBindTexture(imageType, colorBuffer);
    if (imageType == IMG_ARRAY) {
        glTexImage3D(
                imageType, 0, GL_DEPTH_COMPONENT32F, size.x, size.y,  tex_amount,
                0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, nullptr
            );
    } else {
        glTexImage2D(imageType, 0, colorType, size.x, size.y, 0, colorType, GL_UNSIGNED_BYTE, NULL);
    }

    glTexParameteri(imageType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(imageType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(imageType, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(imageType, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);


    glFramebufferTexture(GL_FRAMEBUFFER, type, colorBuffer, 0);

    if (type == PassType::DEPTH)
    {
        glDrawBuffer(GL_NONE);
        glReadBuffer(GL_NONE);
    }
}

void catos::RenderPass::generateRenderBuffer(const Vector2 &size) {
    glGenRenderbuffers(1, &renderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer);

    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, size.x, size.y);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderBuffer);
}


void catos::RenderPass::bindPass() {
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

    glClearColor(0.0f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

void catos::RenderPass::unbindPass() {

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glUseProgram(0);


    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

