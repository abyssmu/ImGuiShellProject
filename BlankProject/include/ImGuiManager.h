#pragma once

#ifndef _IMGUIMANAGER_
#define _IMGUIMANAGER_

#include <memory>
#include <string>

struct GLFWwindow;
struct ImVec2;
struct ImVec4;

//External forward declarations
namespace Scene
{
	class Texture;
}

//Internal declarations
namespace App
{
	//External forward declarations

	//Internal declarations
	class ImGuiManager
	{
	public:
		//Deleted constructors
		ImGuiManager(const ImGuiManager& other) = delete;
		ImGuiManager& operator=(const ImGuiManager& other) = delete;
		ImGuiManager(const ImGuiManager&& other) = delete;
		ImGuiManager& operator=(const ImGuiManager&& other) = delete;

		//Custom constructors
		ImGuiManager(ImVec4 clear_color, GLFWwindow* window, const char* glsl_version);
		
		//Default constructors/destructor
		ImGuiManager();
		~ImGuiManager();

		//Member methods
		void NewFrame();
		ImVec4& GetClearColor();
		ImVec2& GetRenderSize();
		void RenderDrawData();
		void SetupDemoWindow();

		//Application specific methods
		void SetupWindow(std::shared_ptr<Scene::Texture> texture, float aspect_ratio);

		//PIMPL idiom
	private:
		struct ImGuiManagerImpl;
		std::unique_ptr<ImGuiManagerImpl> _impl;
	};
}

#endif