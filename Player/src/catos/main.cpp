// engine includes
#pragma once
//
#include <core/window.h>
#include <renderer/renderPass.h>
#include <renderer/renderer.h>
#include <renderer/renderPipeline.h>

//Rml
#define RMLUI_SDL_VERSION_MAJOR 3

#include <RmlUi/core.h>
#include <RmlUi/Debugger.h>
#include <ui/Backend.h>
#include <fstream>

#include "spdlog/spdlog.h"

std::string vertexShaderSource;
std::string fragmentShaderSource;

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
    //
    catos::Window window{catos::WindowCreationInfo{
        {1280, 720},
        {0.0f, 0.0f},
        "My Catos App",

    }};

    vertexShaderSource   = loadTxtFromFile("../../../Assets/Shaders/default.vert");
    fragmentShaderSource = loadTxtFromFile("../../../Assets/Shaders/default.frag");


    catos::Shader defaultShader{};
    defaultShader.init({
        .vertexSRC = vertexShaderSource.c_str(),
        .fragmentSRC = fragmentShaderSource.c_str()
    });

    catos::RenderPassCreationInfo info {
            .willBeVisible = true,
            .size = {1280, 720},
            .passType = catos::PassType::COLOR,
            .imageType = catos::ImageType::IMG_2D,
            .name = "default"
    };

    catos::RenderPass defaultPass{info, defaultShader};

    catos::Renderer& renderer = catos::Renderer::getInstance();
    renderer.init({

    });

    catos::RenderPipeline defaultPipeline{};
    defaultPipeline.setBeginPass(defaultPass);

    Matrix4 cam{};


    if (!Backend::Initialize(window)) {
        spdlog::error("Failed to initialize backend!");
        return -5;
    }

    Rml::SetSystemInterface(Backend::GetSystemInterface());
    Rml::SetRenderInterface(Backend::GetRenderInterface());

    Rml::Initialise();

    Rml::Context* context = Rml::CreateContext("Hello SDL CATOS!", Rml::Vector2i(1280, 720));

    if (!context) {
        spdlog::error("Failed to create context!");
        return -2;
    }

    Rml::Debugger::Initialise(context);


    if (!Rml::LoadFontFace("../../../Assets/Roboto-Regular.ttf")) {
        spdlog::error("Failed to load font!");
    }

    Rml::ElementDocument* document = context->LoadDocument("../../../test.rml");

    if (!document) {
        spdlog::error("Failed to load document!");
        return -3;
    }
    document->Show();
    Rml::Debugger::SetVisible(false);

    bool running = true;
    while (running) {
        running = Backend::ProcessEvents(context);
        //window.update();
        //
        defaultPipeline.draw(cam);


        context->Update();

        Backend::BeginFrame();
        context->Render();
        Backend::PresentFrame();

    }

    Rml::Shutdown();

    Backend::Shutdown();

    return 0;
}

