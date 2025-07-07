//
// Created by allos on 20/06/2025.
//

#include "dummyWindow.h"

#include "imgui.h"
#include "../Editor/utils.h"
#include "spdlog/spdlog.h"
using namespace catos;



void DummyWindow::init(App &app, int id) {
    _id = id;
}




void DummyWindow::render() {

    std::string name = "DummyWindow##" + std::to_string(_id);

    ImGui::Begin(name.c_str());

    ImGui::End();
}

void DummyWindow::clean_up() {

}
