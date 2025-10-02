//
// Created by allos on 5/15/2024.
//
#pragma once
#include "core/application.h"
#include "Editor/editor.h"
#include "Windows/dummyWindow.h"
#include "Windows/inspectorWindow.h"
#include "Windows/treeviewWindow.h"
#include "core/console.h"
#include "Editor/actionManager.h"
#include "Windows/consoleWindow.h"

template<typename T>
class TestAction: public catos::Action {
public:

    TestAction(int id, T n,  T* instance) {
        this->id = id;
        this->_old = *instance;
        this->_new = n;

        this->ptr = instance;
        *instance = n;
    }
    void execute() override {
        spdlog::info("Executed, {}", id);
        *ptr = _new;
    }

    void revoke() override {
        *ptr = _old;
        spdlog::info("Revoked, {}", id);
    }
private:
    int id = 0;
    T _old;
    T _new;
    T* ptr;
};

int main() {

    catos::Console::initialize();

    spdlog::set_level(spdlog::level::debug);
    catos::App app{};

    auto registry = &catos::Registry::get();

    registry->register_class<catos::Node>("Node").property("name", &catos::Node::name, "...");
    registry->register_class<catos::DummyNode>("DummyNode").inherits("Node").property("data", &catos::DummyNode::_data, "...");
    registry->register_class<catos::DummyNode2>("DummyNode2").inherits("DummyNode");
    registry->register_class<catos::DummyNode3>("DummyNode3").inherits("Node");

    catos::Editor editor(app);

    catos::Node root{false};
    catos::Node parent{false};
    catos::DummyNode child{false};

    root.initialize("root");
    parent.initialize("parent");
    child.initialize("child");

    child.set_parent(&parent);
    parent.set_parent(&root);

    editor.register_editor_window<catos::DummyWindow>("DummyWindow");
    editor.register_editor_window<catos::InspectorWindow>("Inspector");
    editor.register_editor_window<catos::TreeViewWindow>("TreeView");
    editor.register_editor_window<catos::ConsoleWindow>("Console");

    editor.new_editor("DummyWindow");
    editor.new_editor("Inspector");
    editor.new_editor("TreeView");
    editor.new_editor("Console");

    spdlog::info("Here is some info!");
    spdlog::warn("Here is a warning!");
    spdlog::error("Here is a error!");
    spdlog::critical("Here is something critical!");

    editor.set_current_root(&root);

    editor.run();

    editor.clean_up();

    return 0;
}
