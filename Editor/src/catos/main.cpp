//
// Created by allos on 5/15/2024.
//
#pragma once
#include "core/application.h"
#include "Editor/editor.h"
#include "Windows/dummyWindow.h"
#include "Windows/inspectorWindow.h"
#include "Windows/treeviewWindow.h"

struct Loo {
    void f() {

    }
};

int main() {
    //

    spdlog::set_level(spdlog::level::debug);

    catos::App app{};

    auto registry = &catos::Registry::get();

    registry->register_class<catos::Node>("Node").property("name", &catos::Node::_name, "...");
    registry->register_class<catos::DummyNode>("DummyNode").inherits("Node");
    registry->register_class<catos::DummyNode2>("DummyNode2").inherits("DummyNode");
    registry->register_class<catos::DummyNode3>("DummyNode3").inherits("Node");

    catos::Editor editor(app);

    catos::Node root{false};
    catos::Node parent{false};
    catos::Node child{false};

    root.initialize("root");
    parent.initialize("parent");
    child.initialize("child");

    child.set_parent(&parent);
    parent.set_parent(&root);

    editor.registerEditorWindow<catos::DummyWindow>("DummyWindow");
    editor.registerEditorWindow<catos::InspectorWindow>("Inspector");
    editor.registerEditorWindow<catos::TreeViewWindow>("TreeView");

    editor.new_editor("DummyWindow");
    editor.new_editor("Inspector");
    editor.new_editor("TreeView");

    editor.set_current_root(&root);

    editor.run();

    editor.clean_up();


    return 0;
}
