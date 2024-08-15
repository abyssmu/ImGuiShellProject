#pragma once

#include "imgui_helper.h"

void SetupBasicWindow(bool& show_demo_window, bool& show_another_window, ImVec4& clear_color, ImGuiIO& io)
{
	static float f = 0.0f;
	static int counter = 0;

	ImGui::Begin("Hello, world!");

	ImGui::Text("This is some useful text.");
	ImGui::Checkbox("Demo Window", &show_demo_window);
	ImGui::Checkbox("Another Window", &show_another_window);

	ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
	ImGui::ColorEdit3("clear color", (float*)&clear_color);

	if (ImGui::Button("Button")) counter++;

	ImGui::SameLine();
	ImGui::Text("counter = %d", counter);

	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
	ImGui::End();

	if (show_another_window)
	{
		ImGui::Begin("Another Window", &show_another_window);
		ImGui::Text("Hello from another window!");

		if (ImGui::Button("Close Me")) show_another_window = false;

		ImGui::End();
	}
}

void RenderImGui(int& width, int& height, ImVec4& clear_color, ImGuiIO& io)
{
	ImGui::Render();
	glViewport(0, 0, width, height);
	glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
	glClear(GL_COLOR_BUFFER_BIT);
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}