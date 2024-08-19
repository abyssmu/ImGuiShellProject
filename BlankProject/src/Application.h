// Most of the ImGui portion is copied from ImGui opengl3+glfw example
// It has been reorginized a bit for better reading

#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#ifndef APPLICATION
#define APPLICATION

#include "imgui.h"
#include "imgui_internal.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_glfw.h"
#include <stdio.h>
#define GL_SILENCE_DEPRECATION
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h> // Will drag system OpenGL headers

#include <memory>
#include <string>

using std::string;
using std::unique_ptr;

namespace App
{
	class Application
	{
	public:
		Application() = delete;
		~Application();
		Application(const Application& other) = delete;
		Application(const int& width, const int height, const string win_name);

		void Run(bool demo);

	private:
		void SetupGLFW();
		void SetupImGuiIO();
		void Draw();

		void LoopImGuiDemo();

		void SetupDemoWindow();

		void CheckForWindowResize();

	private:
		const char* _glsl_version;
		GLFWwindow* _window;
		ImVec4 _clear_color;
		bool _show_demo_window;
		bool _show_another_window;
		int _win_width;
		int _win_height;
		string _win_name;
	};

	static void glfw_error_callback(int error, const char* description)
	{
		fprintf(stderr, "GLFW Error %d: %s\n", error, description);
	}

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
}

#endif