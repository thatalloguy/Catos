//
// Created by allos on 20/06/2025.
//

#include "dummyWindow.h"

#include "imgui.h"
#include "../Editor/utils.h"
#include "spdlog/spdlog.h"
using namespace catos;

inline size_t string_hash = typeid(catos::string).hash_code();

namespace {
    void renderValue(size_t hash, void* value, const char* name) {

        if (hash == float_hash) {
            ImGui::InputFloat(name, (float*)value);
        } else if (int_hash == hash) {
            ImGui::InputInt(name, (int*)value);
        } else if (hash == string_hash) {
            ImGui::InputText(name, (catos::string*)value);
        }else {
            ImGui::Text("%s : Unknown", name);
        }
    }
}


void DummyWindow::init(App &app, int id) {
    _id = id;
    registerType(*app.get<Registry>());
}




void DummyWindow::render() {

    std::string name = "DummyWindow##" + std::to_string(_id);

    ImGui::Begin(name.c_str());

    for (auto pair: dummyTypeInfo.properties) {
        renderValue(pair.second->get_type_hash(), pair.second->get_value(&instance), pair.second->get_name());
    }
    ImGui::End();
}

void DummyWindow::clean_up() {

}
