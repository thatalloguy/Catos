//
// Created by allos on 5/16/2024.
//
#pragma once
#include <vector>

namespace catos::Editor {

        void init();

        void run();

        void cleanUp();


        struct EditorTab {
            const char* title;
            void(*init)() = nullptr;
            void(*render)() = nullptr;
            void(*destroy)() = nullptr;
        };

        void register_tab(EditorTab* tab);
}
