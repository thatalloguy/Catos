//
// Created by allos on 10/16/2024.
//

#include "renderer.h"
#include "glad/glad.h"

// Some util variables
float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
        // positions   // texCoords
        -1.0f,  1.0f,  0.0f, 1.0f,
        -1.0f, -1.0f,  0.0f, 0.0f,
        1.0f, -1.0f,  1.0f, 0.0f,

        -1.0f,  1.0f,  0.0f, 1.0f,
        1.0f, -1.0f,  1.0f, 0.0f,
        1.0f,  1.0f,  1.0f, 1.0f
};

const char *screenVertexSource = "#version 420 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "layout (location = 1) in vec2 aTexCoords;\n"
                                 "out vec2 TexCoords; \n"
                                 "void main()\n"
                                 "{\n"
                                 "   TexCoords = aTexCoords;\n"
                                 "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                 "}\0";

const char* screenFragmentSource = "#version 420 core\n"
                                   "uniform sampler2D outTexture;\n"
                                   "in vec2 TexCoords;"
                                   "out vec4 outColor;\n"
                                   "void main() {\n"
                                   " vec3 col = texture(outTexture, TexCoords).rgb;\n"
                                   " outColor = vec4(col, 1.0);\n"
                                   "}\n";




catos::Renderer &catos::Renderer::getInstance() {
    static Renderer _instance{};

    return _instance;
}

catos::Renderer::~Renderer() {

    glDeleteVertexArrays(1, &renderVAO);
    glDeleteBuffers(1, &renderVBO);

}

catos::RenderStatus catos::Renderer::init(const catos::RendererCreateInfo &createInfo) {

    if (initialized) {
        return RenderStatus::RENDERER_ALREADY_INITIALIZED;
    }


    // do init stuff

    ShaderCreateInfo screenInfo {
        screenVertexSource,
        screenFragmentSource
    };

    screenShader.init(screenInfo);

    screenShader.bind();
    screenShader.setInt("outTexture", 0);

    setupFinalRenderPlane();

    return RenderStatus::SUCCESSFUL;
}




catos::RenderStatus catos::Renderer::renderObjects(const catos::RenderPipeline &pipeline, void *data, unsigned int objectAmount) {

    //do stuff.

    return RenderStatus::SUCCESSFUL;
}


catos::RenderStatus catos::Renderer::renderPassToScreen(catos::RenderPass &pass) {

    glBindVertexArray(renderVAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, pass.getPassTexture());
    screenShader.bind();
    glDrawArrays(GL_TRIANGLES, 0, 6);

    return RenderStatus::SUCCESSFUL;
}

void catos::Renderer::setupFinalRenderPlane() {

    glGenVertexArrays(1, &renderVAO);
    glGenBuffers(1, &renderVBO);

    glBindVertexArray(renderVAO);
    glBindBuffer(GL_ARRAY_BUFFER, renderVBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
}
