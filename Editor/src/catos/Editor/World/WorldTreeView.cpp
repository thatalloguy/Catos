//
// Created by allos on 5/17/2024.
//

#include "WorldTreeView.h"
#include "../Editor.h"
#include <imgui.h>

using namespace catos::Editor;

namespace WorldTreeView {


    void init_tab() {

    }

    void render_tab() {
        ImGui::Begin("World Tree");

        ImGui::Text("hello world");

        ImGui::End();
    }

    void destroy() {

    }


    void init() {
        EditorTab* tab = new EditorTab{
            .title = "World Tree",
            .init = &init_tab,
            .render = &render_tab,
            .destroy = &destroy
        };
        catos::Editor::register_tab( tab);
    }



}