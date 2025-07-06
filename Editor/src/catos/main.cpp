//
// Created by allos on 5/15/2024.
//
#pragma once
#include "core/application.h"
#include "Editor/editor.h"
#include "Windows/dummyWindow.h"


int main() {
    //


    catos::App app{};

    catos::Editor editor(app);

    editor.registerEditorWindow<catos::DummyWindow>("DummyWindow");

    // editor.new_editor("DummyWindow");
    editor.new_editor("DummyWindow");

    editor.run();

    editor.clean_up();


    return 0;
}
