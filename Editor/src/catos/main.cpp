//
// Created by allos on 5/15/2024.
//
#pragma once
#include "core/application.h"
#include "Editor/editor.h"
#include "Windows/dummyWindow.h"
#include "Windows/inspectorWindow.h"


int main() {
    //


    catos::App app{};

    catos::Editor editor(app);

    editor.registerEditorWindow<catos::DummyWindow>("DummyWindow");
    editor.registerEditorWindow<catos::InspectorWindow>("Inspector");

    editor.new_editor("DummyWindow");
    editor.new_editor("Inspector");

    editor.run();

    editor.clean_up();


    return 0;
}
