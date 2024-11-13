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


const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "layout (location = 1) in vec3 aColor;\n"
                                 "layout (location = 2) in vec2 aTexCoord;\n"
                                 "\n"
                                 "out vec3 ourColor;\n"
                                 "out vec2 TexCoord;\n"
                                 "\n"
                                 "void main()\n"
                                 "{\n"
                                 "\tgl_Position = vec4(aPos, 1.0);\n"
                                 "\tourColor = aColor;\n"
                                 "\tTexCoord = vec2(aTexCoord.x, aTexCoord.y);\n"
                                 "}";

const char* fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "\n"
                                   "in vec3 ourColor;\n"
                                   "in vec2 TexCoord;\n"
                                   "\n"
                                   "// texture samplers\n"
                                   "uniform sampler2D shadowPass;\n"
                                   "uniform sampler2D albedo;\n"
                                   "\n"
                                   "void main()\n"
                                   "{\n"
                                   "\t// linearly interpolate between both textures (80% container, 20% awesomeface)\n"
                                   "\tvec4 shadow = texture(shadowPass, TexCoord);\n"
                                   "\tvec4 col = texture(albedo, TexCoord);\n"
                                   "\tFragColor = vec4(mix(col.rgb, shadow.rgb, 1.0), 0.5);\n"
                                   "}";

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



    float vertices[] = {
            // positions          // colors           // texture coords
            0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
            0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
            -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
            -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left
    };
    unsigned int indices[] = {
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
    };


    MeshCreationInfo triangleInfo {
        .vertices = vertices,
        .indices = indices,

        .sizeOfVertices = sizeof(vertices),
        .sizeOfIndices = sizeof(indices),

        .verticesAmount = 3,
        .indicesAmount = 6
    };

    TextureCreationInfo texinfo {
        .path = "../../../Assets/Logo.jpeg"
    };

    Mesh triangle{};
    Texture tex{};

    tex.init(texinfo);

    triangle.init(triangleInfo);
    triangle._texture = &tex;

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


//    triangleShader.setInt("texture1", 1);

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
    //triangleShader.setInt("texture1", 1);

    Renderer& renderer = Renderer::getInstance();
    renderer.init(rendererInfo);

    RenderPipeline defaultPipeline{};

    defaultPipeline.setBeginPass(shadowPass);

    defaultPipeline.addMesh(triangle);

    while (!window.should_window_close()) {
        window.update();


        defaultPipeline.draw();
    }

    triangle.destroy();

}

