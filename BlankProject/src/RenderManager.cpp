#include "RenderManager.h"

#include "GlfwAndDebugIncludes.h"
#include "Shader.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

namespace Scene
{
	struct RenderManager::RenderManagerImpl
	{
		//Deleted constructors
		RenderManagerImpl() = delete;
		RenderManagerImpl(const RenderManagerImpl& other) = delete;
		RenderManagerImpl& operator=(const RenderManagerImpl& other) = delete;
		RenderManagerImpl(const RenderManagerImpl&& other) = delete;
		RenderManagerImpl& operator=(const RenderManagerImpl&& other) = delete;

		//Custom constructors
		RenderManagerImpl(const int& width, const int& height);
		
		//Default constructors/destructor
		~RenderManagerImpl();

		//Member methods

		//Member variables
		std::shared_ptr<Texture> texture;
		std::unique_ptr<Shader> shader;
		GLuint vertex_buffer = 0;
		GLuint vertex_array = 0;
	};

	RenderManager::RenderManagerImpl::RenderManagerImpl(const int& width, const int& height) :
		texture(std::make_shared<Texture>(width, height)),
		shader(std::make_unique<Shader>("shader/VertexShader.vs", "shader/FragmentShader.fs"))
	{
		float vertices[] =
		{
			// positions        // colors
			 0.0f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
			-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f
		};

		glGenVertexArrays(1, &vertex_array);
		glGenBuffers(1, &vertex_buffer);
		glBindVertexArray(vertex_array);
		glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		GLenum err = glGetError();
		if (err != GL_NO_ERROR) DebugMessage("Render Manager failed to create vertex data: " + std::to_string(err), __func__);

		glUseProgram(shader->GetShader());
	}

	RenderManager::RenderManagerImpl::~RenderManagerImpl()
	{
		glDeleteVertexArrays(1, &vertex_array);
		glDeleteBuffers(1, &vertex_buffer);
	}

	RenderManager::RenderManager() = default;
	RenderManager::~RenderManager() = default;

	RenderManager::RenderManager(const int& width, const int& height) :
		_impl(std::make_unique<RenderManagerImpl>(width, height)) {}

	void RenderManager::RenderTexture()
	{
		float aspect_ratio = _impl->texture->GetAspectRatio();
		float ortho_height = 1.0f;
		float ortho_width = ortho_height * aspect_ratio;

		glm::mat4 projection = glm::ortho(-ortho_width, ortho_width, -ortho_height, ortho_height, -1.0f, 1.0f);

		GLuint projection_loc = glGetUniformLocation(_impl->shader->GetShader(), "projection");
		glUniformMatrix4fv(projection_loc, 1, GL_FALSE, glm::value_ptr(projection));

		GLenum err = glGetError();
		if (err != GL_NO_ERROR) DebugMessage("OpenGL error in RenderTexture: " + std::to_string(err), __func__);

		_impl->texture->Render(_impl->shader->GetShader(), _impl->vertex_array);
	}

	std::shared_ptr<Texture> RenderManager::GetTexture()
	{
		return _impl->texture;
	}

	float RenderManager::GetTextureAspectRatio() const
	{
		return _impl->texture->GetAspectRatio();
	}
}