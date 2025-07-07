//
// Created by allos on 07/07/2025.
//

#include "treeviewWindow.h"
#include "../Editor/utils.h"

using namespace catos;

namespace {

    void renderNode(Node* node) {

        if (ImGui::TreeNode(node->name().c_str())) {


            for (auto child : node->children()) {
                renderNode(child);
            }

            ImGui::TreePop();
        }

    }
}

void TreeViewWindow::init(App &app, int id) {
    _id = id;

    editor = Editor::get_current_instance();
}




void TreeViewWindow::render() {

    std::string name =  "TreeViewWindow##" + std::to_string(_id);

    ImGui::Begin(name.c_str());

    ImGui::Button(ICON_FA_PLUS);
    ImGui::SameLine();
    ImGui::InputTextWithHint(ICON_FA_MAGNIFYING_GLASS, "Search for a node", &current_search);
    ImGui::Separator();
    Node* root = editor->get_current_scene_root();

    renderNode(root);
    ImGui::End();
}

void TreeViewWindow::clean_up() {

}
