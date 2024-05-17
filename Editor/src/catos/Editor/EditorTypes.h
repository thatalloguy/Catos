#pragma once




namespace catos::Editor {

    typedef const char* cstr

    struct EditorTab {
        cstr title = nullptr;
        EditorTab* (*init)() = nullptr;
        void(*render)(bool& is_open) = nullptr;
        void(*destroy)() = nullptr;
        bool auto_instance = false;
    };

}