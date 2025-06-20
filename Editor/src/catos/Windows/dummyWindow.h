#pragma once

#include "../Editor/editor.h"

using namespace catos;

class DummyWindow : EditorWindow {
    public:
    DummyWindow() = default;
    ~DummyWindow() override = default;

    void init(const App& app, int id) override;
    void render() override;
    void clean_up() override;

};