#pragma once

#ifndef _WINDOWMANAGER_
#define _WINDOWMANAGER_

#include <memory>
#include <string>

//External forward declarations
struct GLFWwindow;

//Internal declarations
namespace Scene
{
	//External forward declarations

	//Internal declarations
	class WindowManager
	{
	public:
		//Deleted constructors
		WindowManager(const WindowManager& other) = delete;
		WindowManager& operator=(const WindowManager& other) = delete;
		WindowManager(WindowManager&& other) = delete;
		WindowManager& operator=(const WindowManager&& other) = delete;

		//Custom constructors
		WindowManager(const std::string& name, const int& width, const int& height);

		//Default constructors/destructor
		WindowManager();
		~WindowManager();

		//Member methods
		GLFWwindow* GetWindow() const;
		const char* GetGlslVersion() const;
		bool ShouldClose() const;
		void SwapBuffers();
		static void GLFWFramebufferSizeCallback(GLFWwindow* window, int width, int height);
		static void GLFWErrorCallback(int error, const char* description);

		//PIMPL idiom
	private:
		struct WindowManagerImpl;
		std::unique_ptr<WindowManagerImpl> _impl;
	};
}

#endif