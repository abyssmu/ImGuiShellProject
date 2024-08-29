#include "Application.h"

#include "GlfwAndDebugIncludes.h"
#include "ImGuiManager.h"
#include "Scene.h"

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"

namespace App
{
	struct Application::ApplicationImpl
	{
		//Deleted constructors
		ApplicationImpl(const ApplicationImpl& other) = delete;
		ApplicationImpl& operator=(const ApplicationImpl& other) = delete;
		ApplicationImpl(const ApplicationImpl&& other) = delete;
		ApplicationImpl& operator=(const ApplicationImpl&& other) = delete;

		//Custom constructors

		//Default constructors/destructor
		ApplicationImpl() = default;
		~ApplicationImpl() = default;

		//Member methods
		bool Init(const std::string& name, const int& width, const int& height);
		void Run(bool demo);

		//Member variables
		std::unique_ptr<ImGuiManager> imgui;
		std::unique_ptr<Scene::Scene> scene;
	};

	bool Application::ApplicationImpl::Init(const std::string& name, const int& width, const int& height)
	{
		scene = std::make_unique<Scene::Scene>(name, width, height);

		//If the scene creation failed, return false to exit program
		if (scene->GetWindow() == nullptr) return false;

		imgui = std::make_unique<ImGuiManager>(ImVec4(0.45f, 0.55f, 0.60f, 1.00f), scene->GetWindow(), scene->GetGlslVersion());

		return true;
	}

	void Application::ApplicationImpl::Run(bool demo)
	{
		//Check each frame if the window should close
		while (!scene->WindowShouldClose())
		{
			//Poll GLFW events for input processing
			glfwPollEvents();

			//If the window is minimized, prevent rendering
			if (glfwGetWindowAttrib(scene->GetWindow(), GLFW_ICONIFIED) != 0)
			{
				ImGui_ImplGlfw_Sleep(10);
				continue;
			}

			//Create new ImGui frame
			imgui->NewFrame();

			//Render either the demo or the actual application window
			if (demo) imgui->SetupDemoWindow();
			else
			{
				//Render the texture for the ImGui render window
				scene->RenderTexture();

				//Build the ImGui UI dockspace and framework for rendering
				imgui->SetupWindow(scene->GetTexture(), scene->GetTextureAspectRatio());
			}
			
			ImGui::Render();

			//Get ImGui background color and render scene
			ImVec4& cc = imgui->GetClearColor();
			scene->Render(cc.x * cc.w, cc.y * cc.w, cc.z * cc.w, cc.w);

			//Draw ImGui to OpenGL window and swap buffers to present frame to screen
			imgui->RenderDrawData();
			scene->SwapBuffers();
		}
	}

	Application::Application() :
		_impl(std::make_unique<ApplicationImpl>())
	{}

	Application::~Application() = default;

	/*
	* Initialization function used to capture a boolean to capture member variable failures
	* and prevent compilation or execution failures and leaking memory.
	*/
	bool Application::Init(const std::string& name, const int& width, const int& height)
	{
		return _impl->Init(name, width, height);
	}

	void Application::Run(bool demo)
	{
		_impl->Run(demo);
	}
}