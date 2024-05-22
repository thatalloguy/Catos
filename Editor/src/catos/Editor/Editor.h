//
// Created by allos on 5/16/2024.
//
#pragma once
#include <vector>
#include "imgui.h"

namespace catos::Editor {

        void init();

        void run();

        void cleanUp();

        struct DockInfo {
            ImGuiID left;
            ImGuiID right;
            ImGuiID up;
            ImGuiID down;
        };


        struct EditorTab {
            const char* title;
            void(*init)() = nullptr;
            void(*render)() = nullptr;
            void(*destroy)() = nullptr;
            void(*setup_docking)(ImGuiID dockspace, DockInfo& info) = nullptr;

        };

        void register_tab(EditorTab* tab);
}
