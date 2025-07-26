//
// Created by allos on 07/07/2025.
//

#include "treeviewWindow.h"
#include "../Editor/utils.h"

using namespace catos;

namespace {

    Node* payload_node = nullptr;
    Node* target_node = nullptr;


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


        //You should not be able to reparent the root.
        if (!node->is_root()) {
            if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceNoHoldToOpenOthers)) {

                ImGui::SetDragDropPayload(CATOS_NODE_PAYLOAD, nullptr, 0);
                ImGui::Text(node->name().c_str());

                payload_node = node;

                ImGui::EndDragDropSource();
            }
        }


        if (ImGui::BeginDragDropTarget()) {

            if (ImGui::AcceptDragDropPayload(CATOS_NODE_PAYLOAD)) {
                target_node = node;
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


    void renderSearchBar(string& current_search) {

        if (ImGui::Button(ICON_FA_PLUS)) {
            ImGui::OpenPopupEx(NODE_CREATION_WINDOW_ID);
        }
        ImGui::SameLine();
        ImGui::InputTextWithHint(ICON_FA_MAGNIFYING_GLASS, "Search for a node", &current_search);
        ImGui::Separator();
    }

    void updateDragDrop() {

        if (payload_node && target_node) {
            payload_node->set_parent(target_node);

            payload_node = nullptr;
            target_node = nullptr;
        }
    }

    void renderNodeCreationPopup() {

        if (ImGui::BeginPopupEx(NODE_CREATION_WINDOW_ID, ImGuiPopupFlags_None)) {


            ImGui::Text("Hello world");

            ImGui::EndPopup();
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


    renderSearchBar(current_search);

    Node* root = editor->get_current_scene_root();

    renderNode(root);
    ImGui::End();

    updateDragDrop();

    renderNodeCreationPopup();

}

void TreeViewWindow::clean_up() {

}
