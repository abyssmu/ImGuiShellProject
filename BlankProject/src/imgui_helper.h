#pragma once

#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_win32.h"
#include <windows.h>
#include <GL/GL.h>
#include <tchar.h>

void SetupBasicWindow(bool& show_demo_window, bool& show_another_window, ImVec4& clear_color, ImGuiIO& io);
void RenderImGui(int& width, int& height, ImVec4& clear_color, ImGuiIO& io);

static void HelpMarker(const char* desc)
{
	ImGui::TextDisabled("(?)");
	if (ImGui::BeginItemTooltip())
	{
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted(desc);
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}