//
// Created by allos on 07/07/2025.
//

#include "treeviewWindow.h"
#include "../Editor/utils.h"

using namespace catos;

namespace {

    void renderNode(Node* node) {

        ImGuiTreeNodeFlags flags{};

        bool open = false;

        if (node->num_children() > 0) {
            flags = ImGuiTreeNodeFlags_OpenOnArrow |
            ImGuiTreeNodeFlags_OpenOnDoubleClick |
            ImGuiTreeNodeFlags_SpanAvailWidth |
            ImGuiTreeNodeFlags_SpanFullWidth |
            ImGuiTreeNodeFlags_FramePadding;


        } else {
            flags = ImGuiTreeNodeFlags_OpenOnArrow |
                    ImGuiTreeNodeFlags_OpenOnDoubleClick |
                    ImGuiTreeNodeFlags_SpanAvailWidth |
                    ImGuiTreeNodeFlags_SpanFullWidth |
                    ImGuiTreeNodeFlags_FramePadding |
                    ImGuiTreeNodeFlags_Leaf;
        }


        open = ImGui::TreeNodeEx(node->name().c_str(), flags);


        if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceNoHoldToOpenOthers)) {

            ImGui::SetDragDropPayload(CATOS_NODE_PAYLOAD, nullptr, 0);
            ImGui::Text(node->name().c_str());
            ImGui::EndDragDropSource();
        }

        if (ImGui::BeginDragDropTarget()) {

            if (const auto* payload = ImGui::AcceptDragDropPayload(CATOS_NODE_PAYLOAD)) {
                spdlog::info("DROPPEDDDDD: ");
            }

            ImGui::EndDragDropTarget();
        }

        if (open) {
            for (auto* child:  node->children()) {
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
