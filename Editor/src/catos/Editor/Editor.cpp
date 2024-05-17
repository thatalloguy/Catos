//
// Created by allos on 5/16/2024.
//
#pragma once
#include "Editor.h"
#include "imgui.h"
#include <../../Runtime/include/core/application.h>

#include "../../Runtime/include/core/window.h"
#include "../../Runtime/Renderer/VkEngine.h"
#include "imgui_internal.h"

#include "World/WorldTreeView.h"

namespace catos::Editor {


    // DO NOT TOUCH >:(
    bool _initialized;

    Window* _window;
    App* _app;

    VulkanEngine _renderer;

    void init_tabs();

    std::vector<EditorTab*> tabs;
    std::vector<EditorTab*> current_tabs;
    unsigned int cur_id = 0;

}

void catos::Editor::init() {

    AppCreationInfo appCreationInfo{
            .version = 1,
        .applicationTitle = "Catos Editor"
    };

    _app = new App(&appCreationInfo);

    WindowCreationInfo windowCreationInfo{
        .size = {1280, 720},
        .title = "Catos Editor",
    };

    _window = new Window(windowCreationInfo);


    _renderer.Init(_window->get_glfw_window(), false);

    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    ImGui::GetIO().IniFilename = "../../Assets/Editor.layout"; /// todo add this in a config of some sort


    init_tabs();

    _initialized = true;


}

void catos::Editor::run() {


    while (!_window->should_window_close()) {

        _window->update();

        _renderer.Run();

        _renderer.start_imgui_frame();

        ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

        for (auto& tab : tabs) {
            tab->render();
        }

        _renderer.end_imgui_frame();

        _renderer.Draw();

    }

}

void catos::Editor::cleanUp() {

    for (auto& tab : tabs) {
        tab->destroy();
        delete tab;
    }

    _renderer.CleanUp();

    delete _app;
    delete _window;
}


void catos::Editor::init_tabs() {


    WorldTreeView::init();

}


void catos::Editor::register_tab(EditorTab* tab) {
    tabs.push_back(tab);
}