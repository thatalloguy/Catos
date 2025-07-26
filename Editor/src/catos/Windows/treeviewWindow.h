//
// Created by allos on 07/07/2025.
//
#pragma once

#ifndef PLAYLOAD_TYPES
#define CATOS_NODE_PAYLOAD "catos_node"
#endif

#ifndef NODE_CREATION_NAME
#define NODE_CREATION_WINDOW_ID 256
#define NODE_CREATION_NAME "Create a new Node"
#endif

#include "../Editor/editor.h"

namespace catos {

    class TreeViewWindow : EditorWindow {
    public:
        TreeViewWindow() = default;
        ~TreeViewWindow() override = default;

        void init(App& app, int id) override;
        void render() override;
        void clean_up() override;

        DockPosition get_dock_pos() override { return DockPosition::Right; };
    private:
        Editor* editor{nullptr};
        string current_search{""};
    };

}
