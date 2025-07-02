#include "editor.h"
#include "utils.h"
#include "backends/imgui_impl_opengl3_loader.h"
#include "spdlog/spdlog.h"

using namespace catos;

Editor::Editor(const App &app, Window *window): _app(app), _window(window) {
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

    for (auto pair : _windows) {
        pair.second->render();
    }

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
