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

#include <fstream>

#include "renderer/passes/MainPass.h"
#include "math/matrix4.h"
#include "renderer/passes/ShadowPass.h"

using namespace catos;


std::string vertexShaderSource;
std::string fragmentShaderSource;


std::string shadowVertex;
std::string shadowFragment;

std::string loadTxtFromFile(const char* path){
    std::ifstream in(path, std::ios::binary);
    if (in)
    {
        std::string contents;
        in.seekg(0, std::ios::end);
        contents.resize(in.tellg());

        in.seekg(0, std::ios::beg);
        in.read(&contents[0], contents.length());
        in.close();
        return contents;
    }
    spdlog::error("Couldn't load: ", path);
    throw(errno);
}

int main() {

    vertexShaderSource   = loadTxtFromFile("../../../Assets/Shaders/default.vert");
    fragmentShaderSource = loadTxtFromFile("../../../Assets/Shaders/default.frag");
    shadowVertex         = loadTxtFromFile("../../../Assets/Shaders/shadow.vert");
    shadowFragment       = loadTxtFromFile("../../../Assets/Shaders/shadow.frag");

    WindowCreationInfo windowCreationInfo{};

    Window window(windowCreationInfo);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        spdlog::error("Could not load GLAD");
        return -1;
    }



    float vertices[] = {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
    };


    MeshCreationInfo triangleInfo {
        .vertices = vertices,

        .sizeOfVertices = sizeof(vertices),

        .verticesAmount = 36,
        .indicesAmount = 6
    };

    TextureCreationInfo texinfo {
        .path = "../../../Assets/Logo.jpeg"
    };

    Mesh triangle{};
    Mesh floor{};
    Texture tex{};


    Vector3 cameraPos{0.0f, 10.0f, -10.0f};
    Vector3 cameraFront{0.0f, 0.0f, -1.0f};
    Vector3 cameraUp{0.0f, 1.0f, 0.0f};


    Matrix4 mat{};

    mat.translate({0.2, 0.2, -2});
    mat.rotate(math::toRadians(30.0f), {0, 1, 0});

    Matrix4 floorMat{};
    floorMat.translate({0, -1.0f, 0});
    floorMat.scale({100, 1.0f, 100});

    tex.init(texinfo);

    triangle.init(triangleInfo);
    triangle._texture = &tex;
    triangle.transform = mat.value_ptr();

    floor.init(triangleInfo);
    floor._texture = &tex;
    floor.transform = floorMat.value_ptr();

    // Shaders.
    ShaderCreateInfo shaderInfo {
        vertexShaderSource.c_str(),
        fragmentShaderSource.c_str()
    };

    ShaderCreateInfo shadowShaderInfo {
        shadowVertex.c_str(),
        shadowFragment.c_str()
    };


    auto* lightLogic = new renderPasses::MainRenderPassLogic;

    lightLogic->cameraPos = &cameraPos;

    RenderPassCreationInfo colorPassInfo {
            .willBeVisible = true,
            .size = {800, 600},
            .resizeToRenderSize = true,

            .passLogic = lightLogic
    };



    RendererCreateInfo rendererInfo {};

    Shader triangleShader;
    Shader shadowShader;

    triangleShader.init(shaderInfo);
    shadowShader.init(shadowShaderInfo);

    RenderPass defaultPass{colorPassInfo, triangleShader};

    renderPasses::ShadowPassLogic* shadowPassLogic = new renderPasses::ShadowPassLogic{};
    shadowPassLogic->setDirection({0.7f, 1.0f, 0});
    shadowPassLogic->setDistance(20.0f);
    shadowPassLogic->setOrigin({0, 0, 0});

    RenderPassCreationInfo shadowPassInfo {
        .willBeVisible = false,
        .size = {1024, 1024},
        .passType =  PassType::DEPTH,
        .colorType = ColorType::DEPTH_IMG,
        .next = &defaultPass,
        .name = "shadowPass",

        .passLogic = shadowPassLogic
    };

    RenderPass shadowPass{shadowPassInfo, shadowShader};

    Renderer& renderer = Renderer::getInstance();
    renderer.init(rendererInfo);

    RenderPipeline defaultPipeline{};

    defaultPipeline.setBeginPass(defaultPass);

    defaultPipeline.addMesh(triangle);
    defaultPipeline.addMesh(floor);


    //calc camera

    Matrix4 proj{};
    Matrix4 view{};
    Matrix4 cam{};



    while (!window.should_window_close()) {
        window.update();

        auto winSize = window.getSize();

        proj = math::perspective(math::toRadians(90.0f), winSize.x / winSize.y, 0.01f, 100000.0f);
        view = math::lookAt(cameraPos, {0.0f, 0.0f, 0.0f}, cameraUp);


        cam = proj * view;

        defaultPipeline.draw(cam.value_ptr());

        if (window.is_resized()) {
            defaultPipeline.resize(winSize.x, winSize.y);
            window.set_resized();
        }
    }

    triangle.destroy();

}

