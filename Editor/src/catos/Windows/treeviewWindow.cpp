//
// Created by allos on 07/07/2025.
//

#include "treeviewWindow.h"
#include "../Editor/utils.h"
#include "../Editor/actions/reparentNodeAction.h"

using namespace catos;

namespace {

    vector<Node*> allocated_nodes{};

    Node* selected_node = nullptr;
    Node* payload_node = nullptr;
    Node* target_node = nullptr;
    Node* hovered_node = nullptr;

    TypeInfo* selected_type = nullptr;
    TypeInfo* node_info = nullptr;

    bool is_context_menu_open = false;

    Editor* editor = nullptr;

    unsigned int leaf_id_counter = 0;

    void delete_node(Node* node) {

        if (!node)
            return;

        if (node->is_root()) {
            spdlog::warn("Cannot delete the root node");
            return;
        }

        editor->emit_event("node-deletion", {
            nullptr,
            node
        });

        node->destroy();
    }


    void renderNode(Node* node, string& current_search, const ImVec2& parent_screen_pos) {

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

        bool pop_colors = false;

        if (node == selected_node) {
            ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(100, 100, 214, 255));
            pop_colors = true;
        }else if (!node->name.contains(current_search) && current_search != "") {
            ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(100, 100, 100, 255));
            pop_colors = true;
        }

        ImDrawList* drawlist = ImGui::GetWindowDrawList();

        ImVec2 current_screen_pos = ImGui::GetCursorScreenPos();

        //Draw the line to the parent
        if (!node->is_root()) {

            drawlist->AddRect(
                {ImGui::GetCursorScreenPos().x, ImGui::GetCursorScreenPos().y +ImGui::GetFrameHeight() / 2},
                {parent_screen_pos.x, ImGui::GetCursorScreenPos().y +ImGui::GetFrameHeight() / 2},
                IM_COL32(100, 100, 100, 255)
                );

            drawlist->AddRect(
                {parent_screen_pos.x, ImGui::GetCursorScreenPos().y +ImGui::GetFrameHeight() / 2},
                {parent_screen_pos.x, parent_screen_pos.y + ImGui::GetFrameHeight() / 2},
                IM_COL32(100, 100, 100, 255)
                );
        }
        open = ImGui::TreeNodeEx(reinterpret_cast<const void*>(leaf_id_counter), flags, node->name.c_str());

        leaf_id_counter++;

        if (pop_colors) {
            ImGui::PopStyleColor();
        }

        if (ImGui::IsItemHovered()) {

            //Only change the current hovered node if the context menu isnt being used
            if (!is_context_menu_open) {
                hovered_node = node;
            }

            //Node selection
            if (ImGui::IsMouseClicked(ImGuiMouseButton_Left) && selected_node != node) {
                selected_node = node;

                editor->emit_event("node-selected", {
                    nullptr,
                    node
                });
            } else if (ImGui::IsMouseClicked(ImGuiMouseButton_Left) && selected_node == node) {
                selected_node = nullptr;
            }
            if (ImGui::IsMouseClicked(ImGuiMouseButton_Right)) {
                ImGui::OpenPopupEx(TREE_CONTEXT_WINDOW_ID);
            }
        }

        //You should not be able to reparent the root.
        if (!node->is_root()) {
            if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceNoHoldToOpenOthers)) {

                ImGui::SetDragDropPayload(CATOS_NODE_PAYLOAD, nullptr, 0);
                ImGui::Text(node->name.c_str());

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
                renderNode(child, current_search, current_screen_pos);
            }


            ImGui::TreePop();
        }
    }
    void renderNodeType(TypeInfo* info) {
        ImGuiTreeNodeFlags flags{};
        bool open = false;

        if (info->children.length() > 0) {
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

        bool pop_colors = false;

        if (info == selected_type) {
            ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(100, 100, 214, 255));
            pop_colors = true;
        }

        open = ImGui::TreeNodeEx(info->name.c_str(), flags);

        if (pop_colors)
            ImGui::PopStyleColor();



        if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Left)) {
                selected_type = info;
        }


        if (open) {
            for (TypeInfo* child : info->children) {
                renderNodeType(child);
            }
            ImGui::TreePop();
        }


    }

    void createNewNode() {
        if (!selected_type) {
            spdlog::warn("No new nodetype is selected");
            return;
        }

        Node* new_node = instance_cast<Node>(selected_type->get_constructor().construct());

        // if we dont have a node selected add it to the root.
        Node* new_node_parent = selected_node != nullptr ? selected_node : editor->get_current_scene_root();
        new_node->name = selected_type->name.c_str();

        new_node->set_parent(new_node_parent);

        allocated_nodes.push_back(new_node);

        spdlog::debug("Created new Node of type: {}", selected_type->name.c_str());
        selected_type = nullptr;
    }

    void renderSearchBar(string& current_search) {

        if (ImGui::Button(ICON_FA_PLUS)) {
            ImGui::OpenPopupEx(NODE_CREATION_WINDOW_ID);
        }
        ImGui::SameLine();
        ImGui::InputTextWithHint(ICON_FA_MAGNIFYING_GLASS, "Search for a node", &current_search);
        ImGui::Separator();
    }

    void renderNodeCreationPopup() {

        if (ImGui::BeginPopupEx(NODE_CREATION_WINDOW_ID, ImGuiPopupFlags_None)) {
            renderNodeType(node_info);

            ImGui::Separator();
            if (ImGui::Button("Cancel")) {
                ImGui::CloseCurrentPopup();
            }
            ImGui::SameLine();
            if (ImGui::Button("Add")) {
                createNewNode();
                ImGui::CloseCurrentPopup();
            }
            ImGui::EndPopup();
        }
    }
    void renderTreeContextMenu() {
        is_context_menu_open = false;
        ImGuiWindowFlags flags = ImGuiWindowFlags_ChildMenu | ImGuiWindowFlags_NoDecoration |
                                 ImGuiWindowFlags_NoCollapse |  ImGuiWindowFlags_NoMove;

        if (ImGui::BeginPopupMenuEx(TREE_CONTEXT_WINDOW_ID, "Options", flags)) {
            is_context_menu_open = true;

            if (ImGui::MenuItem("Delete")) {
                delete_node(hovered_node);
                hovered_node = nullptr;
            }


            ImGui::EndPopup();
        }
    }

    void updateDragDrop() {

        if (payload_node && target_node) {
            Node* prev_parent = payload_node->get_parent();

            payload_node->set_parent(target_node);

            ActionManager::push_present_stack(new actions::ReparentNodeAction{
                    prev_parent,
                    payload_node->get_parent(),
                    payload_node
            });

            payload_node = nullptr;
            target_node = nullptr;
        }
    }
}

void TreeViewWindow::init(App &app, int id) {
    _id = id;

    registry = &Registry::get();
    editor = Editor::get_current_instance();

    node_info = &registry->get_type("Node");

}




void TreeViewWindow::render() {
    std::string name =  "TreeView##" + std::to_string(_id);

    ImGui::Begin(name.c_str());


    renderSearchBar(current_search);




    Node* root = editor->get_current_scene_root();
    leaf_id_counter = 0;
    if (!is_context_menu_open)
        hovered_node = nullptr;

    ImGui::PushStyleVar(ImGuiStyleVar_IndentSpacing, 18.0f);
    renderNode(root, current_search, {0, 0});
    ImGui::PopStyleVar();
    ImGui::End();

    updateDragDrop();

    //popups
    renderNodeCreationPopup();
    renderTreeContextMenu();

}

void TreeViewWindow::clean_up() {
    for (Node* node : allocated_nodes) {
        delete node;
        node = nullptr;
    }
    spdlog::debug("Destroyed node");

    allocated_nodes.clear();
}
