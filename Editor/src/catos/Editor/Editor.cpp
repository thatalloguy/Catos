//
// Created by allos on 5/16/2024.
//
#pragma once
#include "Editor.h"
#include "imgui.h"
#include <../../Runtime/include/core/application.h>

#include "../../Runtime/include/core/window.h"
#include "../../Runtime/Renderer/VkEngine.h"
#include "imgui_internal.h"

#include "World/WorldTreeView.h"
#include "extensions/imgui_dock.h"

namespace catos::Editor {


    // DO NOT TOUCH >:(
    bool _initialized;

    Window* _window;
    App* _app;

    VulkanEngine _renderer;
    ImGuiID dockspaceID;

    void init_tabs();
    void init_style();


    std::vector<EditorTab*> tabs;

}

void catos::Editor::init() {

    AppCreationInfo appCreationInfo{
            .version = 1,
        .applicationTitle = "Catos Editor"
    };

    _app = new App(&appCreationInfo);

    WindowCreationInfo windowCreationInfo{
        .size = {1280, 720},
        .title = "Catos Editor",
    };

    _window = new Window(windowCreationInfo);


    _renderer.Init(_window->get_glfw_window(), false);

    init_tabs();


    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    ImGui::GetIO().IniFilename = nullptr; /// todo add this

    init_style();

    _initialized = true;

    ImGui::InitDock();


}

void catos::Editor::run() {


    while (!_window->should_window_close()) {

        _window->update();

        _renderer.Run();

        _renderer.start_imgui_frame();

        static bool first = true;
        static ImGuiID dockspace_id;
        if (first) {
            dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::DockBuilderRemoveNode(dockspace_id); // Clear any previous layout
            ImGui::DockBuilderAddNode(dockspace_id, ImGuiDockNodeFlags_DockSpace); // Add empty node
            ImGui::DockBuilderSetNodeSize(dockspace_id, ImGui::GetMainViewport()->Size);
            ImGuiID dock_main_id = dockspace_id;
            ImGuiID dock_id_left = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Left, 0.25f, nullptr, &dock_main_id);
            ImGuiID dock_id_right = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Right, 0.25f, nullptr, &dock_main_id);
            // Dock windows into the nodes
            ImGui::DockBuilderDockWindow("World Tree", dock_id_right);
            ImGui::DockBuilderFinish(dock_main_id);
            first = false;
        }

        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(ImGui::GetMainViewport()->Size);
        ImGui::Begin("MAIN", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar| ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);


        ImGui::DockSpace(dockspace_id, ImGui::GetMainViewport()->Size);

        for (auto& tab : tabs) {
            tab->render();
        }

        ImGui::End();

        _renderer.end_imgui_frame();

        _renderer.Draw();

    }

}

void catos::Editor::cleanUp() {

    for (auto& tab : tabs) {
        tab->destroy();
        delete tab;
    }

    _renderer.CleanUp();

    delete _app;
    delete _window;
}


void catos::Editor::init_tabs() {


    WorldTreeView::init();

}


void catos::Editor::register_tab(EditorTab* tab) {
    tabs.push_back(tab);
}

void catos::Editor::init_style() {
    // ~~Nyx~~ catos Engine style
    ImGuiStyle& style = ImGui::GetStyle();

    style.Alpha = 1.0f;
    style.DisabledAlpha = 0.300000011920929f;
    style.WindowPadding = ImVec2(7.5f, 3.0f);
    style.WindowRounding = 0.0f;
    style.WindowBorderSize = 0.0f;
    style.WindowMinSize = ImVec2(20.0f, 20.0f);
    style.WindowTitleAlign = ImVec2(0.009999999776482582f, 0.5f);
    style.WindowMenuButtonPosition = ImGuiDir_Right;
    style.ChildRounding = 1.200000047683716f;
    style.ChildBorderSize = 0.0f;
    style.PopupRounding = 2.0f;
    style.PopupBorderSize = 1.0f;
    style.FramePadding = ImVec2(3.900000095367432f, 2.700000047683716f);
    style.FrameRounding = 1.799999952316284f;
    style.FrameBorderSize = 0.0f;
    style.ItemSpacing = ImVec2(5.599999904632568f, 7.599999904632568f);
    style.ItemInnerSpacing = ImVec2(6.699999809265137f, 3.0f);
    style.CellPadding = ImVec2(6.599999904632568f, 12.0f);
    style.IndentSpacing = 20.0f;
    style.ColumnsMinSpacing = 5.300000190734863f;
    style.ScrollbarSize = 16.20000076293945f;
    style.ScrollbarRounding = 3.299999952316284f;
    style.GrabMinSize = 8.600000381469727f;
    style.GrabRounding = 3.299999952316284f;
    style.TabRounding = 1.600000023841858f;
    style.TabBorderSize = 0.0f;
    style.TabMinWidthForCloseButton = 0.0f;
    style.ColorButtonPosition = ImGuiDir_Right;
    style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
    style.SelectableTextAlign = ImVec2(0.009999999776482582f, 0.0f);

    style.Colors[ImGuiCol_Text] = ImVec4(0.7843137383460999f, 0.7843137383460999f, 0.7843137383460999f, 1.0f);
    style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.3921568691730499f, 0.3921568691730499f, 0.3921568691730499f, 1.0f);
    style.Colors[ImGuiCol_WindowBg] = ImVec4(0.0784313753247261f, 0.0784313753247261f, 0.09019608050584793f, 1.0f);
    style.Colors[ImGuiCol_ChildBg] = ImVec4(0.0470588244497776f, 0.0470588244497776f, 0.0470588244497776f, 1.0f);
    style.Colors[ImGuiCol_PopupBg] = ImVec4(0.0784313753247261f, 0.08627451211214066f, 0.1019607856869698f, 1.0f);
    style.Colors[ImGuiCol_Border] = ImVec4(0.1568627506494522f, 0.168627455830574f, 0.1921568661928177f, 1.0f);
    style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.0784313753247261f, 0.08627451211214066f, 0.1019607856869698f, 0.0f);
    style.Colors[ImGuiCol_FrameBg] = ImVec4(0.03921568766236305f, 0.03921568766236305f, 0.03921568766236305f, 1.0f);
    style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.105882354080677f, 0.105882354080677f, 0.105882354080677f, 1.0f);
    style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.1568627506494522f, 0.1568627506494522f, 0.1568627506494522f, 1.0f);
    style.Colors[ImGuiCol_TitleBg] = ImVec4(0.02745098061859608f, 0.02745098061859608f, 0.02745098061859608f, 1.0f);
    style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.02745098061859608f, 0.02745098061859608f, 0.02745098061859608f, 1.0f);
    style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.03921568766236305f, 0.03921568766236305f, 0.03921568766236305f, 1.0f);
    style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.05882352963089943f, 0.05882352963089943f, 0.07058823853731155f, 1.0f);
    style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.003921568859368563f, 0.003921568859368563f, 0.003921568859368563f, 1.0f);
    style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.1176470592617989f, 0.1333333402872086f, 0.1490196138620377f, 1.0f);
    style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.1568627506494522f, 0.168627455830574f, 0.1921568661928177f, 1.0f);
    style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.1176470592617989f, 0.1333333402872086f, 0.1490196138620377f, 1.0f);
    style.Colors[ImGuiCol_CheckMark] = ImVec4(0.2588235437870026f, 0.4705882370471954f, 1.0f, 1.0f);
    style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.2588235437870026f, 0.4705882370471954f, 1.0f, 1.0f);
    style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.2588235437870026f, 0.5882353186607361f, 1.0f, 1.0f);
    style.Colors[ImGuiCol_Button] = ImVec4(0.1176470592617989f, 0.1176470592617989f, 0.1372549086809158f, 1.0f);
    style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.196078434586525f, 0.196078434586525f, 0.196078434586525f, 1.0f);
    style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.2588235437870026f, 0.4705882370471954f, 1.0f, 1.0f);
    style.Colors[ImGuiCol_Header] = ImVec4(0.02745098061859608f, 0.02745098061859608f, 0.02745098061859608f, 1.0f);
    style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.03529411926865578f, 0.03529411926865578f, 0.03529411926865578f, 1.0f);
    style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.03529411926865578f, 0.03529411926865578f, 0.03529411926865578f, 1.0f);
    style.Colors[ImGuiCol_Separator] = ImVec4(0.1176470592617989f, 0.1176470592617989f, 0.1372549086809158f, 1.0f);
    style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.1176470592617989f, 0.1176470592617989f, 0.1372549086809158f, 1.0f);
    style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.1176470592617989f, 0.1176470592617989f, 0.1372549086809158f, 1.0f);
    style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.3921568691730499f, 0.3921568691730499f, 0.3921568691730499f, 0.6549019813537598f);
    style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.5882353186607361f, 0.5882353186607361f, 0.5882353186607361f, 0.6745098233222961f);
    style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.2588235437870026f, 0.4705882370471954f, 1.0f, 0.800000011920929f);
    style.Colors[ImGuiCol_Tab] = ImVec4(0.01960784383118153f, 0.01960784383118153f, 0.01960784383118153f, 1.0f);
    style.Colors[ImGuiCol_TabHovered] = ImVec4(0.03921568766236305f, 0.03921568766236305f, 0.03921568766236305f, 1.0f);
    style.Colors[ImGuiCol_TabActive] = ImVec4(0.196078434586525f, 0.196078434586525f, 0.196078434586525f, 1.0f);
    style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.03921568766236305f, 0.03921568766236305f, 0.03921568766236305f, 1.0f);
    style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.0784313753247261f, 0.08627451211214066f, 0.1019607856869698f, 1.0f);
    style.Colors[ImGuiCol_PlotLines] = ImVec4(0.0f, 0.6000000238418579f, 0.7019608020782471f, 1.0f);
    style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.07450980693101883f, 0.9803921580314636f, 0.9803921580314636f, 1.0f);
    style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.2588235437870026f, 0.4705882370471954f, 0.686274528503418f, 1.0f);
    style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.2588235437870026f, 0.4705882370471954f, 1.0f, 1.0f);
    style.Colors[ImGuiCol_TableHeaderBg] = ImVec4(0.0470588244497776f, 0.05490196123719215f, 0.07058823853731155f, 1.0f);
    style.Colors[ImGuiCol_TableBorderStrong] = ImVec4(0.0470588244497776f, 0.05490196123719215f, 0.07058823853731155f, 1.0f);
    style.Colors[ImGuiCol_TableBorderLight] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
    style.Colors[ImGuiCol_TableRowBg] = ImVec4(0.1176470592617989f, 0.1333333402872086f, 0.1490196138620377f, 1.0f);
    style.Colors[ImGuiCol_TableRowBgAlt] = ImVec4(0.09803921729326248f, 0.105882354080677f, 0.1215686276555061f, 1.0f);
    style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.2588235437870026f, 0.4705882370471954f, 1.0f, 1.0f);
    style.Colors[ImGuiCol_DragDropTarget] = ImVec4(0.2588235437870026f, 0.4705882370471954f, 1.0f, 1.0f);
    style.Colors[ImGuiCol_NavHighlight] = ImVec4(0.2588235437870026f, 0.4705882370471954f, 1.0f, 1.0f);
    style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(0.2588235437870026f, 0.4705882370471954f, 1.0f, 1.0f);
    style.Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.2588235437870026f, 0.4705882370471954f, 1.0f, 0.4901960790157318f);
    style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.3921568691730499f, 0.3921568691730499f, 0.3921568691730499f, 0.06666667014360428f);

}