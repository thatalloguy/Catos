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

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace catos;


const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "layout (location = 1) in vec3 aColor;\n"
                                 "layout (location = 2) in vec2 aTexCoord;\n"
                                 "\n"
                                 "out vec3 ourColor;\n"
                                 "out vec2 TexCoord;\n"
                                 "\n"
                                 "uniform mat4 cameraMat;\n"
                                 "uniform mat4 transform;\n"
                                 "\n"
                                 "void main()\n"
                                 "{\n"
                                 "\tgl_Position = cameraMat * transform * vec4(aPos, 1.0);\n"
                                 "\tourColor = aColor;\n"
                                 "\tTexCoord = vec2(aTexCoord.x, aTexCoord.y);\n"
                                 "}";

const char* fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "\n"
                                   "in vec3 ourColor;\n"
                                   "in vec2 TexCoord;\n"
                                   "\n"
                                   "uniform sampler2D shadowPass;\n"
                                   "uniform sampler2D albedo;\n"
                                   "\n"
                                   "void main()\n"
                                   "{\n"
                                   "\t// linearly interpolate between both textures (80% container, 20% awesomeface)\n"
                                   "\tFragColor = texture(albedo, TexCoord);\n"
                                   "}";


const char *shadowVertex = "#version 420 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "\n"
                                 "uniform mat4 cameraMat;\n"
                                 "uniform mat4 transform;\n"
                                 "\n"
                                 "void main()\n"
                                 "{\n"
                                 "\tgl_Position = cameraMat * transform * vec4(aPos, 1.0);\n"
                                 "}\0";

const char* shadowFragment = "#version 420 core\n"
                                   "out vec4 outColor;\n"
                                   "void main() {\n"
                                   "\toutColor = vec4(0.5f, 0.5f, 1.0f, 1.0f); \n"
                                   "}\n";


int main() {

    WindowCreationInfo windowCreationInfo{};

    Window window(windowCreationInfo);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        spdlog::error("Could not load GLAD");
        return -1;
    }



    float vertices[] = {
        //x    y      z      r     g     b     uv    uv
        -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
         0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
         0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
         0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
         0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
         0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
         0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

         0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
         0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
         0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
         0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
         0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
         0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
         0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
         0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
         0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
         0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
         0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
         0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f
    };


    MeshCreationInfo triangleInfo {
        .vertices = vertices,

        .sizeOfVertices = sizeof(vertices),

        .verticesAmount = 36,
        .indicesAmount = 6
    };

    TextureCreationInfo texinfo {
        .path = "../../../Assets/images.jpg"
    };

    Mesh triangle{};
    Texture tex{};


    glm::mat4 mat{1.0f};

    mat = glm::translate(mat, {0.2, 0.2, -0.4});
    mat = glm::rotate(mat, glm::radians(30.0f), glm::vec3(0, 1, 0));

    tex.init(texinfo);

    triangle.init(triangleInfo);
    triangle._texture = &tex;
    triangle.transform = glm::value_ptr(mat);

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


    //calc camera

    glm::mat4 proj{1.0f};
    glm::mat4 view{1.0f};
    glm::mat4 cam{1.0f};

    glm::vec3 cameraPos{0.0f, 0.0f, 3.0f};
    glm::vec3 cameraFront{0.0f, 0.0f, -1.0f};
    glm::vec3 cameraUp{0.0f, 1.0f, 0.0f};


    while (!window.should_window_close()) {
        window.update();

        if (glfwGetKey(window.get_glfw_window(), GLFW_KEY_S) == GLFW_PRESS)
        {
            cameraPos.z += 0.1f;
        }

        proj = glm::perspective(glm::radians(90.0f), (float) 800 / (float) 600, 0.01f, 1000.0f);
        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

        cam = proj * view;


        defaultPipeline.draw(glm::value_ptr(cam));
    }

    triangle.destroy();

}

