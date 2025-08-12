//
// Created by allos on 12/08/2025.
//
#pragma once

#include "../Editor/editor.h"

namespace catos {

    class ConsoleWindow : EditorWindow {
    public:
        ConsoleWindow() = default;
        ~ConsoleWindow() override = default;

        void init(App& app, int id) override;
        void render() override;
        void clean_up() override;

        DockPosition get_dock_pos() override { return DockPosition::BottomLeft; };

        catos::vector<Pair<const char*, bool>> levels{
            Pair{"unknown", false}, // unknown
            Pair{"debug", true}, // debug
            Pair{"info", true}, // info
            Pair{"warning", true}, // warning
            Pair{"error", true}, // errors
            Pair{"critical", true} // criticals
        };
    };

}
