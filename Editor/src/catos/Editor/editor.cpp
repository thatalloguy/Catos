#include "editor.h"
#include "utils.h"
#include "backends/imgui_impl_opengl3_loader.h"
#include "spdlog/spdlog.h"

using namespace catos;

namespace {


    ///Credits to Skore for the Docking implementation :D
    ImGuiID dockspace_id{10000};

    ImGuiID centerSpaceId{10000};
    ImGuiID leftSpaceId{};
    ImGuiID rightSpaceId{};
    ImGuiID rightTopSpaceId{};
    ImGuiID rightBottomSpaceId{};
    ImGuiID bottomLeftSpaceId{};
    ImGuiID bottomRightSpaceId{};

    unsigned int GetDockId(DockPosition dock_position) {
        switch (dock_position) {
            case DockPosition::None: return UINT_MAX;
            case DockPosition::Center: return centerSpaceId;
            case DockPosition::Left: return leftSpaceId;
            case DockPosition::Right: return rightSpaceId;
            case DockPosition::RightTop: return rightTopSpaceId;
            case DockPosition::RightBottom: return rightBottomSpaceId;
            case DockPosition::BottomLeft: return bottomLeftSpaceId;
            case DockPosition::BottomRight: return bottomRightSpaceId;
        }

        return UINT_MAX;
    }

    bool dock_initialized = false;

    void init_dock_space() {
        if (!dock_initialized) {
            dock_initialized = true;

            utils::reset_dockspace(dockspace_id);

            centerSpaceId = dockspace_id;
            rightTopSpaceId = ImGui::DockBuilderSplitNode(centerSpaceId, ImGuiDir_Right, 0.15f, nullptr, &centerSpaceId);
            rightBottomSpaceId = ImGui::DockBuilderSplitNode(rightTopSpaceId, ImGuiDir_Down, 0.50f, nullptr, &rightTopSpaceId);

            bottomLeftSpaceId = ImGui::DockBuilderSplitNode(centerSpaceId, ImGuiDir_Down, 0.20f, nullptr, &centerSpaceId);
            bottomRightSpaceId = ImGui::DockBuilderSplitNode(bottomLeftSpaceId, ImGuiDir_Right, 0.30f, nullptr, &bottomLeftSpaceId);

            leftSpaceId = ImGui::DockBuilderSplitNode(centerSpaceId, ImGuiDir_Left, 0.12f, nullptr, &centerSpaceId);
            rightSpaceId = ImGui::DockBuilderSplitNode(centerSpaceId, ImGuiDir_Right, 0.12f, nullptr, &centerSpaceId);



        }
    }

    Editor* instance = nullptr;
}

Editor * Editor::get_current_instance() {
    return instance;
}

Editor::Editor(App &app, Window *window): _app(app), _window(window) {
    if (instance != nullptr) {
        spdlog::error("A editor instance is already running");
        return;
    } else {
        instance = this;
    }
    if (!_window) {
        // create our own window.


        string title{"Catos Editor - "};
        title += CATOS_VERSION;

        WindowCreationInfo editorDefaultCreationInfo{
            {1280, 720},
            {0, 0},
            title.c_str(),
            false,
            true
        };

        _window = new Window();
        _window->initialize(editorDefaultCreationInfo);
    }

    utils::initialize_imgui(_window->get_raw_window_ptr(), _window->get_gl_context());
    _window->add_callback(ImGui_ImplSDL3_ProcessEvent);


    utils::load_style();
}

void Editor::new_editor(const std::string& name) {

    if (_editors.find(name) == _editors.end()) {
        spdlog::info("could not find editor");
        return;
    }

    EditorWindow* new_window = _editors.at(name)();

    int id = get_new_id();
    new_window->init(_app, id);

    _windows.insert({id, new_window});

}

void Editor::set_current_root(Node *new_root) {
    _current_root = new_root;
}

int Editor::get_new_id() {
    return id_counter++;
}

catos::Window* Editor::get_window() {
    return _window;
}

void Editor::run() {

    while (!_window->should_window_close()) {
        _window->update();

        this->render();
    }

}

void Editor::render() {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(255, 255, 255, 255);

    utils::new_imGui_frame();

    utils::create_dockspace(dockspace_id);
    init_dock_space();

    for (auto pair : _windows) {
        pair.second->render();
    }

    ImGui::End();

    utils::render_imGui();
}

void Editor::clean_up() {

    for (auto pair : _windows) {
        pair.second->clean_up();
        delete pair.second;
    }


    utils::destroy_imGui();

    delete _window;
}
