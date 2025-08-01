//
// Created by allos on 20/06/2025.
//

#include "inspectorWindow.h"

#include "imgui.h"
#include "../Editor/utils.h"
#include "spdlog/spdlog.h"
using namespace catos;

inline size_t string_hash = typeid(catos::string).hash_code();
inline size_t vec3_hash = typeid(catos::math::Vector3).hash_code();

namespace {
    void renderValue(size_t hash, void* value, const char* name) {

        if (hash == float_hash) {
            ImGui::InputFloat(name, (float*)value);
        } else if (int_hash == hash) {
            ImGui::InputInt(name, (int*)value);
        } else if (hash == string_hash) {
            ImGui::InputText(name, (catos::string*)value);
        } else if (hash== vec3_hash) {
            ImGui::DragFloat3(name, ((math::Vector3*)value)->value_ptr());
            ((math::Vector3*)value)->x = ((math::Vector3*)value)->_[0];
            ((math::Vector3*)value)->y = ((math::Vector3*)value)->_[1];
            ((math::Vector3*)value)->z = ((math::Vector3*)value)->_[2];
        } else {
            ImGui::Text("%s : Unknown Type", name);
        }
    }

    void renderObject(Registry* registry, size_t hash, void* instance, const char* name) {
        auto info = registry->get_type(hash);

        ImGui::Indent();
        if (ImGui::TreeNodeEx(name, ImGuiTreeNodeFlags_Framed)) {
            for (auto pair : info.properties) {
                if (_registry->is_type_registered(pair.second->get_type_hash())) {
                    void* sub_obj = pair.second->get_value(instance);
                    renderObject(registry, pair.second->get_type_hash(), sub_obj, pair.second->get_name());
                } else {
                    renderValue(pair.second->get_type_hash(), pair.second->get_value(instance), pair.second->get_name());
                }
            }
            ImGui::TreePop();
        }
        ImGui::Unindent();
    }
}


void InspectorWindow::init(App &app, int id) {
    _id = id;
    registerType(Registry::get());
}




void InspectorWindow::render() {

    std::string name = "Inspector##" + std::to_string(_id);

    ImGui::Begin(name.c_str());

    renderObject(_registry, typeid(Dummy).hash_code(), &instance, "Dummy");

    ImGui::End();
}

void InspectorWindow::clean_up() {

}
