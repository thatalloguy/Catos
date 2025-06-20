// engine includes
#pragma once
//
#include <core/window.h>
#include <renderer/renderPass.h>
#include <renderer/renderer.h>
#include <renderer/renderPipeline.h>

#include <fstream>

#include "spdlog/spdlog.h"

struct ContextData {
    float data = 2.3f;
    catos::string text = "This is a Catos String!";
};

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

    while (!window.should_window_close()) {
        window.update();
        //
        defaultPipeline.draw(cam);



    }

    return 0;
}

