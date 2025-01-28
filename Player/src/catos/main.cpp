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
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "renderer/loaders.h"

using namespace catos;


std::string vertexShaderSource;
std::string fragmentShaderSource;


std::string shadowVertex;
std::string shadowFragment;
std::string shadowGeometry;

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
    shadowGeometry       = loadTxtFromFile("../../../Assets/Shaders/shadow.geom");



    WindowCreationInfo windowCreationInfo{};

    Window window(windowCreationInfo);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        spdlog::error("Could not load GLAD");
        return -1;
    }

    IMGUI_CHECKVERSION();

    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window.get_glfw_window(), true);
    ImGui_ImplOpenGL3_Init("#version 420");

    ImGui::GetIO().IniFilename = nullptr;

    TextureCreationInfo texinfo {
        .path = "../../../Assets/Logo.jpeg"
    };

    LoadedMesh triangle{};

    loaders::loadGLTF("../../../Assets/Models/helmet/DamagedHelmet.gltf", &triangle);
    Texture tex{};


    Vector3 cameraPos{-21, 12, -4};
    Vector3 cameraFront{0.0f, 0.0f, -1.0f};
    Vector3 cameraRight{1.0f, 0.0f, 0.0f};
    Vector3 cameraUp{0.0f, 1.0f, 0.0f};


    Matrix4 mat{};

    mat.translate({0.2, 2, -2});
    mat.rotate(math::toRadians(30.0f), {0, 1, 0});
    tex.init(texinfo);

    triangle._texture = &tex;
    triangle.transform = mat.value_ptr();

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
    shadowPassLogic->setDirection({0.6, 1.0f, 0.0f});

    RenderPassCreationInfo shadowPassInfo {
            .willBeVisible = false,
            .size = {1024, 1024},
            .passType =  PassType::DEPTH,
            .colorType = ColorType::DEPTH_IMG,
            .imageType = ImageType::IMG_2D,
            .next = &defaultPass,
            .name = "shadowPass",
            .passLogic = shadowPassLogic
    };



    RenderPass shadowPass{shadowPassInfo, shadowShader};

    Renderer& renderer = Renderer::getInstance();
    renderer.init(rendererInfo);

    RenderPipeline defaultPipeline{};

    defaultPipeline.setBeginPass(shadowPass);

    defaultPipeline.addMesh(triangle);


    //calc camera

    Matrix4 proj{};
    Matrix4 view{};
    Matrix4 cam{};

    float pitch = 0.0f;
    float yaw = 0.0f;
    float roll = 0.0f;

    float distance = 20.0f;

    shadowPassLogic->setDirection({0.7f, 1.0f, 0});
    shadowPassLogic->setDistance(20.0f);
    shadowPassLogic->setOrigin({0, 0, 0});

    while (!window.should_window_close()) {
        window.update();

        auto winSize = window.getSize();

        proj = math::perspective(math::toRadians(90.0f), winSize.x / winSize.y, 0.01f, 100000.0f);


        Matrix4 rot{};
        rot.rotate(toRadians(pitch), {1.0f, 0.0f, 0.0f});
        rot.rotate(toRadians(yaw),  {0.0f, 1.0f, 0.0f});
        rot.rotate(toRadians(roll), {0.0f, 0.0f, 1.0f});

        cameraFront.x = cos(toRadians(yaw)) * cos(toRadians(pitch));
        cameraFront.y = sin(toRadians(pitch));
        cameraFront.z = sin(toRadians(yaw)) * cos(toRadians(pitch));

        cameraFront = normalize(cameraFront);

        cameraRight = normalize(cross(cameraFront, {0, 1, 0}));
        cameraUp = normalize(cross(cameraRight, cameraFront));


        view = math::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);


        view = view * rot;

        cam = proj * view;


        defaultPipeline.draw(cam);

        if (window.is_resized()) {
            defaultPipeline.resize(winSize.x, winSize.y);
            window.set_resized();
        }

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();


        if (ImGui::Begin("Debug Info")) {

            ImGui::DragFloat3("Camera Pos", cameraPos.value_ptr());

            cameraPos.x = cameraPos._[0];
            cameraPos.y = cameraPos._[1];
            cameraPos.z = cameraPos._[2];

            ImGui::DragFloat("Size", &distance);

            shadowPassLogic->setDistance(distance);
            shadowPassLogic->setOrigin(cameraPos);

            if (ImGui::TreeNode("ShadowMap")) {

                ImGui::Image(reinterpret_cast<ImTextureID>(shadowPass.getPassTexture()), {250, 250});


                ImGui::TreePop();
            }


        }

        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }


    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

