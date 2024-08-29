#pragma once

#ifndef _SHADER_
#define _SHADER_

#include <memory>
#include <string>

//External forward declarations
typedef unsigned int GLuint;

//Internal declarations
namespace Scene
{
	//External fordward declarations

	//Internal declarations
	class Shader
	{
	public:
		//Deleted constructors
		Shader(const Shader& other) = delete;
		Shader& operator=(const Shader& other) = delete;
		Shader(Shader&& other) = delete;
		Shader& operator=(const Shader&& other) = delete;
		
		//Custom constructors
		Shader(const std::string& vs_file, const std::string& fs_file);

		//Default constructors/destructor
		Shader();
		~Shader();

		//Member methods
		GLuint& GetShader();

		//PIMPL idiom
	private:
		struct ShaderImpl;
		std::unique_ptr<ShaderImpl> _impl;
	};
}

#endif