//
// Created by allos on 07/07/2025.
//

#include "treeviewWindow.h"
#include "../Editor/utils.h"

using namespace catos;

void TreeViewWindow::init(App &app, int id) {
    _id = id;

    editor = Editor::get_current_instance();
}




void TreeViewWindow::render() {

    std::string name = "TreeViewWindow##" + std::to_string(_id);

    ImGui::Begin(name.c_str());

    ImGui::Button("+");
    ImGui::SameLine();
    ImGui::InputTextWithHint(": ", "Search for a node", &current_search);
    ImGui::Separator();
    Node* root = editor->get_current_scene_root();

    if (ImGui::TreeNode(root->name().c_str())) {

        ImGui::Text("Hello World");

        ImGui::TreePop();
    }

    ImGui::End();
}

void TreeViewWindow::clean_up() {

}
