#include "Shader.h"
#include "GlfwAndDebugIncludes.h"

#include <fstream>
#include <sstream>

namespace Scene
{
	struct Shader::ShaderImpl
	{
		//Deleted constructors
		ShaderImpl() = delete;
		ShaderImpl(const ShaderImpl& other) = delete;
		ShaderImpl& operator=(const ShaderImpl& other) = delete;
		ShaderImpl(const ShaderImpl&& other) = delete;
		ShaderImpl& operator=(const ShaderImpl&& other) = delete;

		//Custom constructors
		ShaderImpl(const std::string& vs_file, const std::string& fs_file);

		//Default constructors/destructor
		~ShaderImpl();

		//Member methods
		void CheckCompileErrors(unsigned int shader, std::string type) const;

		//Member variables
		GLuint shader;
	};

	Shader::ShaderImpl::~ShaderImpl()
	{
		glDeleteProgram(shader);
	}

	Shader::ShaderImpl::ShaderImpl(const std::string& vs_file, const std::string& fs_file)
	{
		std::string vertex_code;
		std::string fragment_code;
		std::ifstream vertex_shader_file;
		std::ifstream fragment_shader_file;
		std::stringstream vertex_shader_stream;
		std::stringstream fragment_shader_stream;

		vertex_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fragment_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try
		{
			vertex_shader_file.open(vs_file);
			fragment_shader_file.open(fs_file);

			vertex_shader_stream << vertex_shader_file.rdbuf();
			fragment_shader_stream << fragment_shader_file.rdbuf();

			vertex_shader_file.close();
			fragment_shader_file.close();

			vertex_code = vertex_shader_stream.str();
			fragment_code = fragment_shader_stream.str();
		}
		catch (std::ifstream::failure& e)
		{
			DebugMessage("ERROR::SHADER::FILE_NOT_READ: " + std::string(e.what()), __func__);
			return;
		}

		vertex_code = vertex_shader_stream.str();
		fragment_code = fragment_shader_stream.str();

		const char* vertex_shader_code = vertex_code.c_str();
		const char* fragment_shader_code = fragment_code.c_str();

		unsigned int vertex, fragment;

		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vertex_shader_code, nullptr);
		glCompileShader(vertex);
		CheckCompileErrors(vertex, "VERTEX");

		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fragment_shader_code, nullptr);
		glCompileShader(fragment);
		CheckCompileErrors(fragment, "FRAGMENT");

		shader = glCreateProgram();
		glAttachShader(shader, vertex);
		glAttachShader(shader, fragment);
		glLinkProgram(shader);
		CheckCompileErrors(shader, "PROGRAM");

		glDeleteShader(vertex);
		glDeleteShader(fragment);

		GLenum err = glGetError();
		if (err != GL_NO_ERROR) DebugMessage("Shader failed to compile: " + std::to_string(err), __func__);
	}

	void Shader::ShaderImpl::CheckCompileErrors(unsigned int shader, std::string type) const
	{
		int success;
		char infoLog[1024];
		if (type != "PROGRAM")
		{
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
				DebugMessage("ERROR::SHADER_COMPILATION_ERROR of type: " + type, __func__);
			}
		}
		else
		{
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
				DebugMessage("ERROR::PROGRAM_LINKING_ERROR of type: " + type, __func__);
			}
		}
	}

	Shader::Shader() = default;
	Shader::~Shader() = default;

	Shader::Shader(const std::string& vs_file, const std::string& fs_file) :
		_impl(make_unique<ShaderImpl>(vs_file, fs_file))
	{}

	GLuint& Shader::GetShader()
	{
		return _impl->shader;
	}
}