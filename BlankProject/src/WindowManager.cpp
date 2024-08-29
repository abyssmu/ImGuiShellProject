#include "WindowManager.h"

#include "GlfwAndDebugIncludes.h"

namespace Scene
{
	struct WindowManager::WindowManagerImpl
	{
		//Deleted constructors
		WindowManagerImpl() = delete;
		WindowManagerImpl(const WindowManagerImpl& other) = delete;
		WindowManagerImpl& operator=(const WindowManagerImpl& other) = delete;
		WindowManagerImpl(const WindowManagerImpl&& other) = delete;
		WindowManagerImpl& operator=(const WindowManagerImpl&& other) = delete;

		//Custom constructors
		WindowManagerImpl(const std::string& name, const int& width, const int& height);

		//Default constructors/destructor
		~WindowManagerImpl();

		//Member methods

		//Member variables
		std::string name;
		const char* glsl_version = nullptr;
		GLFWwindow* window = nullptr;
		int width;
		int height;
	};

	WindowManager::WindowManagerImpl::WindowManagerImpl(const std::string& name, const int& width, const int& height) :
		name(name), width(width), height(height)
	{
		if (!glfwInit())
		{
			glfwTerminate();
			return;
		}

		glsl_version = "#version 130";
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

		window = glfwCreateWindow(this->width, this->height, this->name.c_str(), nullptr, nullptr);

		if (window == nullptr) return;

		glfwMakeContextCurrent(window);
		glfwSetFramebufferSizeCallback(window, GLFWFramebufferSizeCallback);
		glfwSetErrorCallback(GLFWErrorCallback);
		glfwSwapInterval(1);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			return;
		}
	}

	WindowManager::WindowManagerImpl::~WindowManagerImpl()
	{
		glfwDestroyWindow(window);

		window = nullptr;
		glsl_version = nullptr;
	}

	WindowManager::WindowManager() = default;
	WindowManager::~WindowManager() = default;

	WindowManager::WindowManager(const std::string& name, const int& width, const int& height) :
		_impl(std::make_unique<WindowManagerImpl>(name, width, height))
	{}

	GLFWwindow* WindowManager::GetWindow() const
	{
		return _impl->window;
	}

	const char* WindowManager::GetGlslVersion() const
	{
		return _impl->glsl_version;
	}

	bool WindowManager::ShouldClose() const
	{
		return glfwWindowShouldClose(_impl->window);
	}

	void WindowManager::SwapBuffers()
	{
		glfwSwapBuffers(_impl->window);
	}

	void WindowManager::GLFWFramebufferSizeCallback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	};

	void WindowManager::GLFWErrorCallback(int error, const char* description)
	{
		DebugMessage("GLFW Error " + std::to_string(error) + ": " + std::string(description), __func__);
	};
}