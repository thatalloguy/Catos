//
// Created by allos on 20/06/2025.
//

#include "dummyWindow.h"

#include "imgui.h"
#include "../Editor/actionManager.h"
#include "../Editor/utils.h"
#include "spdlog/spdlog.h"
using namespace catos;


void testEvent(void* listener, const EventCallback& callback) {
    spdlog::info("HELLOOO!!!!");
}

void DummyWindow::init(App &app, int id) {
    _id = id;

    Editor::get_current_instance()->add_event_listener("test", this, testEvent);
}




void DummyWindow::render() {

    std::string name = "DevWindow##" + std::to_string(_id);

    ImGui::Begin(name.c_str());

    ImGui::Text("Current FPS: %i", (int) ImGui::GetIO().Framerate);

    if (ImGui::Button("Undo")) ActionManager::undo();



    if (ImGui::Button("Redo")) ActionManager::redo();


    ImGui::End();
}

void DummyWindow::clean_up() {

}
