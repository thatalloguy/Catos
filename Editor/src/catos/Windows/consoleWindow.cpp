//
// Created by allos on 12/08/2025.
//

#include "consoleWindow.h"

#include "imgui.h"
#include "../Editor/IconsFontAwesome6.h"
#include "core/console.h"

namespace {


    void renderLogIcon(catos::LogLevel level) {
        switch (level) {
            case spdlog::level::debug:
                ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0, 100, 200, 255));
                ImGui::Text(ICON_FA_BUG);
                break;

            case spdlog::level::info:
                ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0, 100, 10, 255));
                ImGui::Text(ICON_FA_CIRCLE_INFO);
                break;

            case spdlog::level::warn:
                ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(150, 125, 0, 255));
                ImGui::Text(ICON_FA_TRIANGLE_EXCLAMATION);
                break;

            case spdlog::level::err:
                ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(200, 20, 0, 255));
                ImGui::Text(ICON_FA_CIRCLE_EXCLAMATION);
                break;

            case spdlog::level::critical:
                ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(100, 0, 0, 255));
                ImGui::Text(ICON_FA_BOMB);
                break;

            default:
                ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(100, 100, 100, 255));
                ImGui::Text(ICON_FA_QUESTION);
                break;
        }
        ImGui::PopStyleColor();
        ImGui::SameLine();
    }
}

void catos::ConsoleWindow::init(App &app, int id) {
    _id = id;

}

void catos::ConsoleWindow::render() {

    std::string name = "Console##" + std::to_string(_id);

    ImGui::Begin(name.c_str());

    for (int i=0; i<levels.length(); i++) {
        ImGui::Checkbox(levels[i].first, &levels[i].second);

        if (i<levels.length()-1)
            ImGui::SameLine();
    }
    ImGui::Separator();



    ImGui::BeginChild("console");



    for (const ConsoleLog& log : Console::get_logs()) {
        if (levels[log.level].second) {
            renderLogIcon(log.level);
            ImGui::Text(log.message.c_str());
        }
    }

    ImGui::EndChild();

    ImGui::End();

}

void catos::ConsoleWindow::clean_up() {

}
