#pragma once

#include "../Editor/editor.h"

namespace catos {

    class DummyWindow : EditorWindow {
    public:
        DummyWindow() = default;
        ~DummyWindow() override = default;

        void init(App& app, int id) override;
        void render() override;
        void clean_up() override;

        DockPosition get_dock_pos() override { return DockPosition::Right; };

    };

}
