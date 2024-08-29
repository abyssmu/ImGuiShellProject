// Shader and scene classes draw from the Learn OpenGL tutorial
// https://learnopengl.com/Getting-started/OpenGL

#pragma once

#ifndef _SCENE_
#define _SCENE_

#include <memory>
#include <string>

//External forward declarations
struct GLFWwindow;

//Internal declarations
namespace Scene
{
	//External forward declarations
	class Texture;

	//Internal declarations
	class Scene
	{
	public:
		//Deleted constructors
		Scene(const Scene& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene&& other) = delete;

		//Custom constructors
		Scene(const std::string& name, const int& width, const int& height);

		//Default constructors/destructor
		Scene();
		~Scene();

		//Member methods
		void RenderTexture();
		void Render(const float& r, const float& g, const float& b, const float& a);
		const char* GetGlslVersion() const;
		GLFWwindow* GetWindow() const;
		std::shared_ptr<Texture> GetTexture() const;
		float GetTextureAspectRatio() const;
		bool WindowShouldClose() const;
		void SwapBuffers() const;

		//PIMPL idiom
	private:
		struct SceneImpl;
		std::unique_ptr<SceneImpl> _impl;
	};
}

#endif