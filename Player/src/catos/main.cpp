// engine includes
#pragma once

#include <glad/glad.h>
#include <core/window.h>

#include "renderer/mesh.h"
#include "spdlog/spdlog.h"
#include "renderer/shader.h"
#include "renderer/renderPass.h"
#include "renderer/renderer.h"
#include "renderer/renderPipeline.h"

using namespace catos;


const char *vertexShaderSource = "#version 420 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "out vec3 pos;\n"
                                 "void main()\n"
                                 "{\n"
                                 "   pos = aPos;\n"
                                 "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                 "}\0";

const char* fragmentShaderSource = "#version 420 core\n"
                                   "out vec4 outColor;\n"
                                   "in vec3 pos;\n"
                                   "uniform sampler2D shadowPass;\n"
                                   "void main() {\n"
                                    " vec3 col = texture(shadowPass, vec2(pos.x, pos.y)).rgb;\n"
                                   " outColor = vec4(1.0f, 0.5f, 0.4f, 1.0f); \n"
                                   "}\n";

const char *shadowVertex = "#version 420 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "void main()\n"
                                 "{\n"
                                 "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                 "}\0";

const char* shadowFragment = "#version 420 core\n"
                                   "out vec4 outColor;\n"
                                   "void main() {\n"
                                   " outColor = vec4(0.5f, 0.5f, 1.0f, 1.0f); \n"
                                   "}\n";


int main() {

    WindowCreationInfo windowCreationInfo{};

    Window window(windowCreationInfo);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        spdlog::error("Could not load GLAD");
        return -1;
    }


    glViewport(0, 0, 800, 600);

    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
};

    unsigned int VBO;

    glGenBuffers(1, &VBO);

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);
    // load the vertices into the VAO and VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    Mesh triangle{VAO, VBO, 3};

    // Shaders.



    ShaderCreateInfo shaderInfo {
        vertexShaderSource,
        fragmentShaderSource
    };


    ShaderCreateInfo shadowShaderInfo {
        shadowVertex,
        shadowFragment
    };



    RenderPassCreationInfo colorPassInfo{
            .willBeVisible = true,
            .size = {800, 600}
    };



    RendererCreateInfo rendererInfo {};

    Shader triangleShader;
    Shader shadowShader;

    triangleShader.init(shaderInfo);
    shadowShader.init(shadowShaderInfo);


    RenderPass defaultPass{colorPassInfo, triangleShader};

    RenderPassCreationInfo shadowPassInfo{
        .willBeVisible = false,
        .size = {800, 600},
        .passType =  PassType::DEPTH,
        .imageType = ImageType::DEPTH_IMG,
        .next = &defaultPass,
        .name = "shadowPass"
    };


    RenderPass shadowPass{shadowPassInfo, shadowShader};

    Renderer& renderer = Renderer::getInstance();
    renderer.init(rendererInfo);

    RenderPipeline defaultPipeline{};

    defaultPipeline.setBeginPass(shadowPass);

    defaultPipeline.addMesh(triangle);

    while (!window.should_window_close()) {
        window.update();


        defaultPipeline.draw();

    }


}

