// engine includes
#pragma once

#include <glad/glad.h>
#include <core/window.h>

#include "renderer/mesh.h"
#include "spdlog/spdlog.h"
#include "renderer/shader.h"
#include "renderer/renderPass.h"
#include "renderer/renderer.h"

using namespace catos;

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


    catos::TriangleMesh triangle;


    // Shaders.
    const char *vertexShaderSource = "#version 420 core\n"
                                     "layout (location = 0) in vec3 aPos;\n"
                                     "void main()\n"
                                     "{\n"
                                     "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                     "}\0";

    const char* fragmentShaderSource = "#version 420 core\n"
                                       "out vec4 outColor;\n"
                                       "void main() {\n"
                                       " outColor = vec4(1.0f, 0.5f, 0.4f, 1.0f); \n"
                                       "}\n";


    ShaderCreateInfo shaderInfo {
        vertexShaderSource,
        fragmentShaderSource
    };


    RenderPassCreationInfo passInfo{
            .willBeVisible = true,
            .size = {800, 600}
    };

    RendererCreateInfo rendererInfo {};

    Shader triangleShader;

    triangleShader.init(shaderInfo);


    RenderPass defaultPass{passInfo, triangleShader};

    Renderer& renderer = Renderer::getInstance();
    renderer.init(rendererInfo);


    while (!window.should_window_close()) {
        window.update();

        defaultPass.bindPass();


        triangle.draw();

        defaultPass.unbindPass();


        renderer.renderPassToScreen(defaultPass);

    }


}

