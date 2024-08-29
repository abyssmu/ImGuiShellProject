#pragma once

#ifndef _TEXTURE_
#define _TEXTURE_

#include <memory>

//External forward declarations
typedef unsigned int GLuint;

//Internal declarations
namespace Scene
{
	//External forward declarations

	//Internal declarations
	class Texture
	{
	public:
		//Deleted constructors
		Texture(const Texture& other) = delete;
		Texture& operator=(const Texture& other) = delete;
		Texture(Texture&& other) = delete;
		Texture& operator=(const Texture&& other) = delete;

		//Custom constructors
		Texture(const int& width, const int& height);

		//Default constructors/destructor
		Texture();
		~Texture();

		//Member methods
		GLuint& GetTextureId();
		void Render(GLuint& shader, GLuint& vert_array);
		void SetupFramebufferAndTexture(const int& width, const int& height);
		float GetAspectRatio() const;

		//PIMPL idiom
	private:
		struct TextureImpl;
		std::unique_ptr<TextureImpl> _impl;
	};
}

#endif