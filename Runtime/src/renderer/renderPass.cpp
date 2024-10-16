//
// Created by allos on 10/16/2024.
//

#include "renderPass.h"
#include "spdlog/spdlog.h"
#include <glad/glad.h>

catos::RenderPass::RenderPass(const catos::RenderPassCreationInfo &info, catos::Shader &shaderToUse) : shader(shaderToUse) {

    _isFinal = info.willBeVisible;

    _shouldResize = info.resizeToRenderSize;

    generateFrameBuffer(info.size);

    generateColorBuffer(info.size, info.passType);

    generateRenderBuffer(info.size);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        spdlog::error("Error creating RenderPass");
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

catos::RenderPass::~RenderPass() {
    glDeleteRenderbuffers(1, &renderBuffer);
    glDeleteFramebuffers(1, &frameBuffer);
}


void catos::RenderPass::generateFrameBuffer(const Vector2 &size) {
    glGenFramebuffers(1, &frameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
}

void catos::RenderPass::generateColorBuffer(const Vector2 &size, PassType type) {
    glGenTextures(1, &colorBuffer);

    glBindTexture(GL_TEXTURE_2D, colorBuffer);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, size.x, size.y, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glFramebufferTexture2D(GL_FRAMEBUFFER, type, GL_TEXTURE_2D, colorBuffer, 0);
}

void catos::RenderPass::generateRenderBuffer(const Vector2 &size) {
    glGenRenderbuffers(1, &renderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer);

    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, size.x, size.y);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderBuffer);
}


void catos::RenderPass::bindPass() {
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
    glEnable(GL_DEPTH_TEST);



    glClearColor(1, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    shader.bind();
}

void catos::RenderPass::unbindPass() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDisable(GL_DEPTH_TEST);

    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);

}

