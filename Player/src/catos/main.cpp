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

#include <fstream>

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

struct LightRenderLogic: RenderPassLogic {

    glm::vec3* cameraPos;

    void onMeshPrepare(RenderPass& pass, Mesh& mesh) override{

        Shader& passShader = pass.getShader();

        passShader.setVector3("lightColor", {1, 1, 1});
        passShader.setVector3("lightPos", {0, 5, 3});
        passShader.setVector3("viewPos", {cameraPos->x, cameraPos->y, cameraPos->z});
    }
};

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
        .path = "../../../Assets/images.jpg"
    };

    Mesh triangle{};
    Texture tex{};


    glm::vec3 cameraPos{0.0f, 0.0f, 0.0f};
    glm::vec3 cameraFront{0.0f, 0.0f, -1.0f};
    glm::vec3 cameraUp{0.0f, 1.0f, 0.0f};


    glm::mat4 mat{1.0f};

    mat = glm::translate(mat, {0.2, 0.2, -2});
    mat = glm::rotate(mat, glm::radians(30.0f), glm::vec3(0, 1, 0));

    tex.init(texinfo);

    triangle.init(triangleInfo);
    triangle._texture = &tex;
    triangle.transform = glm::value_ptr(mat);

    // Shaders.
    ShaderCreateInfo shaderInfo {
        vertexShaderSource.c_str(),
        fragmentShaderSource.c_str()
    };

    ShaderCreateInfo shadowShaderInfo {
        shadowVertex.c_str(),
        shadowFragment.c_str()
    };


    LightRenderLogic* lightLogic = new LightRenderLogic;

    lightLogic->cameraPos = &cameraPos;

    RenderPassCreationInfo colorPassInfo{
            .willBeVisible = true,
            .size = {800, 600},

            .passLogic = lightLogic
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


    proj = glm::perspective(glm::radians(90.0f), (float) 800 / (float) 600, 0.01f, 1000.0f);
    view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

    cam = proj * view;


    while (!window.should_window_close()) {
        window.update();

        defaultPipeline.draw(glm::value_ptr(cam));
    }

    triangle.destroy();

}

