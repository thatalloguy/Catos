#pragma once

#include <imgui.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_sdl3.h>

#include "imgui_internal.h"

#include <stl/string.h>

namespace utils {



    static void initialize_imgui(void* window, void* context) {

        ImGui::CreateContext();
        ImGui_ImplSDL3_InitForOpenGL((SDL_Window*) window, context);
        ImGui_ImplOpenGL3_Init("#version 440");
    	ImGui::StyleColorsDark();
    	ImGuiIO& io = ImGui::GetIO();

    	// io.IniFilename = nullptr;
    	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    	io.ConfigViewportsNoTaskBarIcon = true;
    }

    static void new_imGui_frame() {
        ImGui_ImplSDL3_NewFrame();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();
    }

	static void create_dockspace(ImGuiID dockspaceId) {
    	static ImGuiDockNodeFlags dockNodeFlags = ImGuiDockNodeFlags_None;

    	ImGuiWindowFlags windowFlags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    	auto             viewport = ImGui::GetMainViewport();
    	ImGui::SetNextWindowPos(viewport->WorkPos);
    	ImGui::SetNextWindowSize(viewport->WorkSize);
    	ImGui::SetNextWindowViewport(viewport->ID);
    	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    	ImGui::PushStyleColor(ImGuiCol_WindowBg, IM_COL32(20, 20, 23, 255));
    	windowFlags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
    	windowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

    	dockNodeFlags |= ImGuiDockNodeFlags_NoWindowMenuButton;
    	ImGui::Begin("DockSpace", 0, windowFlags);
    	ImGui::PopStyleVar(3);
    	ImGui::PopStyleColor(1);

    	ImGuiStyle& style = ImGui::GetStyle();
    	ImGui::DockSpace(dockspaceId, ImVec2(0.0f, viewport->WorkSize.y - 40), dockNodeFlags);

    }

	static void reset_dockspace(ImGuiID dockspaceId) {
    	auto viewport = ImGui::GetMainViewport();
    	ImGui::DockBuilderRemoveNode(dockspaceId);
    	ImGui::DockBuilderAddNode(dockspaceId, ImGuiDockNodeFlags_DockSpace);
    	ImGui::DockBuilderSetNodeSize(dockspaceId, viewport->WorkSize);
    }

    static void render_imGui() {
         ImGui::Render();

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }


    static void destroy_imGui() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplSDL3_Shutdown();

        ImGui::DestroyContext();
    }

    static void load_style() {
		// Catos style from ImThemes
		ImGuiStyle& style = ImGui::GetStyle();

		style.Alpha = 1.0f;
		style.DisabledAlpha = 0.4000000059604645f;
		style.WindowPadding = ImVec2(18.39999961853027f, 20.0f);
		style.WindowRounding = 0.0f;
		style.WindowBorderSize = 1.0f;
		style.WindowMinSize = ImVec2(32.0f, 32.0f);
		style.WindowTitleAlign = ImVec2(0.5f, 0.0f);
		style.WindowMenuButtonPosition = ImGuiDir_None;
		style.ChildRounding = 0.0f;
		style.ChildBorderSize = 1.0f;
		style.PopupRounding = 0.0f;
		style.PopupBorderSize = 0.0f;
		style.FramePadding = ImVec2(20.0f, 4.099999904632568f);
		style.FrameRounding = 0.0f;
		style.FrameBorderSize = 1.0f;
		style.ItemSpacing = ImVec2(6.300000190734863f, 5.099999904632568f);
		style.ItemInnerSpacing = ImVec2(6.0f, 4.099999904632568f);
		style.CellPadding = ImVec2(8.100000381469727f, 5.5f);
		style.IndentSpacing = 5.800000190734863f;
		style.ColumnsMinSpacing = 6.0f;
		style.ScrollbarSize = 18.70000076293945f;
		style.ScrollbarRounding = 0.0f;
		style.GrabMinSize = 10.0f;
		style.GrabRounding = 3.200000047683716f;
		style.TabRounding = 0.0f;
		style.TabBorderSize = 1.0f;
		style.ColorButtonPosition = ImGuiDir_Left;
		style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
		style.SelectableTextAlign = ImVec2(0.0f, 0.0f);

		style.Colors[ImGuiCol_Text] = ImVec4(0.5882353186607361f, 0.5882353186607361f, 0.5882353186607361f, 1.0f);
		style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.3921568691730499f, 0.3921568691730499f, 0.3921568691730499f, 1.0f);
		style.Colors[ImGuiCol_WindowBg] = ImVec4(0.1176470592617989f, 0.1176470592617989f, 0.1176470592617989f, 1.0f);
		style.Colors[ImGuiCol_ChildBg] = ImVec4(0.1843137294054031f, 0.1843137294054031f, 0.1843137294054031f, 0.0f);
		style.Colors[ImGuiCol_PopupBg] = ImVec4(0.0784313753247261f, 0.0784313753247261f, 0.0784313753247261f, 0.9399999976158142f);
		style.Colors[ImGuiCol_Border] = ImVec4(0.03921568766236305f, 0.03921568766236305f, 0.03921568766236305f, 1.0f);
		style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
		style.Colors[ImGuiCol_FrameBg] = ImVec4(0.062745101749897f, 0.062745101749897f, 0.062745101749897f, 1.0f);
		style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.09803921729326248f, 0.09803921729326248f, 0.09803921729326248f, 1.0f);
		style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.1568627506494522f, 0.1568627506494522f, 0.1568627506494522f, 1.0f);
		style.Colors[ImGuiCol_TitleBg] = ImVec4(0.03921568766236305f, 0.03921568766236305f, 0.03921568766236305f, 1.0f);
		style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.03921568766236305f, 0.03921568766236305f, 0.03921568766236305f, 1.0f);
		style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.0f, 0.0f, 0.0f, 0.5099999904632568f);
		style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.1372549086809158f, 0.1372549086809158f, 0.1372549086809158f, 1.0f);
		style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.01960784383118153f, 0.01960784383118153f, 0.01960784383118153f, 0.5299999713897705f);
		style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.3568627536296844f, 0.3411764800548553f, 0.3450980484485626f, 1.0f);
		style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.3960784375667572f, 0.3764705955982208f, 0.3843137323856354f, 1.0f);
		style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.5098039507865906f, 0.5098039507865906f, 0.5098039507865906f, 1.0f);
		style.Colors[ImGuiCol_CheckMark] = ImVec4(0.3921568691730499f, 0.4274509847164154f, 0.8627451062202454f, 1.0f);
		style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.3568627536296844f, 0.3411764800548553f, 0.3450980484485626f, 1.0f);
		style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.3960784375667572f, 0.3803921639919281f, 0.8627451062202454f, 1.0f);
		style.Colors[ImGuiCol_Button] = ImVec4(0.1843137294054031f, 0.1843137294054031f, 0.1843137294054031f, 1.0f);
		style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.196078434586525f, 0.196078434586525f, 0.196078434586525f, 1.0f);
		style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.3921568691730499f, 0.4274509847164154f, 0.8627451062202454f, 1.0f);
		style.Colors[ImGuiCol_Header] = ImVec4(0.1843137294054031f, 0.1843137294054031f, 0.1843137294054031f, 1.0f);
		style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.196078434586525f, 0.196078434586525f, 0.196078434586525f, 1.0f);
		style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.3921568691730499f, 0.4274509847164154f, 0.8627451062202454f, 1.0f);
		style.Colors[ImGuiCol_Separator] = ImVec4(0.4274509847164154f, 0.4274509847164154f, 0.4980392158031464f, 1.0f);
		style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.3921568691730499f, 0.4000000059604645f, 0.7490196228027344f, 0.7803921699523926f);
		style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.47843137383461f, 0.4862745106220245f, 0.7490196228027344f, 1.0f);
		style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.5254902243614197f, 0.5882353186607361f, 0.9764705896377563f, 0.2000000029802322f);
		style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.3921568691730499f, 0.3921568691730499f, 0.9764705896377563f, 0.6705882549285889f);
		style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.3921568691730499f, 0.3921568691730499f, 0.8392156958580017f, 0.9490196108818054f);
		style.Colors[ImGuiCol_Tab] = ImVec4(0.1176470592617989f, 0.1176470592617989f, 0.1176470592617989f, 1.0f);
		style.Colors[ImGuiCol_TabHovered] = ImVec4(0.2156862765550613f, 0.2156862765550613f, 0.2156862765550613f, 1.0f);
		style.Colors[ImGuiCol_TabActive] = ImVec4(0.1843137294054031f, 0.1843137294054031f, 0.1843137294054031f, 1.0f);
		style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.06666667014360428f, 0.1019607856869698f, 0.1450980454683304f, 0.9724000096321106f);
		style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.1333333402872086f, 0.2588235437870026f, 0.4235294163227081f, 1.0f);
		style.Colors[ImGuiCol_PlotLines] = ImVec4(0.6078431606292725f, 0.6078431606292725f, 0.6078431606292725f, 1.0f);
		style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.0f, 0.4274509847164154f, 0.3490196168422699f, 1.0f);
		style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.8980392217636108f, 0.6980392336845398f, 0.0f, 1.0f);
		style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.0f, 0.6000000238418579f, 0.0f, 1.0f);
		style.Colors[ImGuiCol_TableHeaderBg] = ImVec4(0.1882352977991104f, 0.1882352977991104f, 0.2000000029802322f, 1.0f);
		style.Colors[ImGuiCol_TableBorderStrong] = ImVec4(0.196078434586525f, 0.196078434586525f, 0.196078434586525f, 1.0f);
		style.Colors[ImGuiCol_TableBorderLight] = ImVec4(0.2274509817361832f, 0.2274509817361832f, 0.2470588237047195f, 1.0f);
		style.Colors[ImGuiCol_TableRowBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
		style.Colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.0f, 1.0f, 1.0f, 0.05999999865889549f);
		style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.3921568691730499f, 0.3921568691730499f, 0.9764705896377563f, 0.2588235437870026f);
		style.Colors[ImGuiCol_DragDropTarget] = ImVec4(1.0f, 1.0f, 0.0f, 0.8999999761581421f);
		style.Colors[ImGuiCol_NavHighlight] = ImVec4(0.2588235437870026f, 0.5882353186607361f, 0.9764705896377563f, 1.0f);
		style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.0f, 1.0f, 1.0f, 0.699999988079071f);
		style.Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.800000011920929f, 0.800000011920929f, 0.800000011920929f, 0.2000000029802322f);
		style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.800000011920929f, 0.800000011920929f, 0.800000011920929f, 0.3499999940395355f);

    }


}


namespace ImGui {

	IMGUI_API bool  InputText(const char* label, catos::string* str, ImGuiInputTextFlags flags = 0, ImGuiInputTextCallback callback = nullptr, void* user_data = nullptr);
	IMGUI_API bool  InputTextMultiline(const char* label, catos::string* str, const ImVec2& size = ImVec2(0, 0), ImGuiInputTextFlags flags = 0, ImGuiInputTextCallback callback = nullptr, void* user_data = nullptr);
	IMGUI_API bool  InputTextWithHint(const char* label, const char* hint, catos::string* str, ImGuiInputTextFlags flags = 0, ImGuiInputTextCallback callback = nullptr, void* user_data = nullptr);
}