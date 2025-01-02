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
    _imageType = info.imageType;

    _size = info.size;

    generateFrameBuffer(info.size);

    generateColorBuffer(info.size, info.passType, info.imageType);

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

void catos::RenderPass::generateColorBuffer(const Vector2 &size, PassType type, ImageType imageType) {
    glGenTextures(1, &colorBuffer);

    glBindTexture(GL_TEXTURE_2D, colorBuffer);

    glTexImage2D(GL_TEXTURE_2D, 0, imageType, size.x(), size.y(), 0, imageType, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glFramebufferTexture2D(GL_FRAMEBUFFER, type, GL_TEXTURE_2D, colorBuffer, 0);

    if (type == PassType::DEPTH)
    {
        glDrawBuffer(GL_NONE);
        glReadBuffer(GL_NONE);
    }
}

void catos::RenderPass::generateRenderBuffer(const Vector2 &size) {
    glGenRenderbuffers(1, &renderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer);

    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, size.x(), size.y());
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderBuffer);
}


void catos::RenderPass::bindPass() {
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);




    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (_render_logic != nullptr){
        _render_logic->onPassPrepare(*this);
    }
}

void catos::RenderPass::unbindPass() {

    if (_render_logic != nullptr){
        _render_logic->onPassEnd(*this);
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glUseProgram(0);


    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

