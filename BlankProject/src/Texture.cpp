#include "Texture.h"

#include "GlfwAndDebugIncludes.h"

namespace Scene
{
	struct Texture::TextureImpl
	{
		//Deleted constructors
		TextureImpl() = delete;
		TextureImpl(const TextureImpl& other) = delete;
		TextureImpl& operator=(const TextureImpl& other) = delete;
		TextureImpl(TextureImpl&& other) = delete;
		TextureImpl& operator=(const TextureImpl&& other) = delete;

		//Custom constructors

		//Default constructors/destructor
		TextureImpl(const int& width, const int& height);
		~TextureImpl();

		//Member methods
		void SetupFramebufferAndTexture(const int& width, const int& height);

		//Member variables
		int width;
		int height;
		GLuint frame_buffer;
		GLuint texture;
	};

	Texture::TextureImpl::TextureImpl(const int& width, const int& height)
	{
		SetupFramebufferAndTexture(this->width, this->height);
	}

	Texture::TextureImpl::~TextureImpl()
	{
		glDeleteFramebuffers(1, &frame_buffer);
		glDeleteTextures(1, &texture);
	}

	void Texture::TextureImpl::SetupFramebufferAndTexture(const int& width, const int& height)
	{
		this->width = width;
		this->height = height;

		glDeleteFramebuffers(1, &frame_buffer);
		glDeleteTextures(1, &texture);

		glGenFramebuffers(1, &frame_buffer);
		glBindFramebuffer(GL_FRAMEBUFFER, frame_buffer);

		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			DebugMessage("Framebuffer is not complete!", __func__);
		}

		GLenum err = glGetError();
		if (err != GL_NO_ERROR) DebugMessage("Framebuffer and texture creation failed: " + std::to_string(err), __func__);
	}

	Texture::Texture() = default;
	Texture::~Texture() = default;

	Texture::Texture(const int& width, const int& height) :
		_impl(std::make_unique<TextureImpl>(width, height))
	{}

	GLuint& Texture::GetTextureId()
	{
		return _impl->texture;
	}

	void Texture::Render(GLuint& shader, GLuint& vert_array)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, _impl->frame_buffer);
		glViewport(0, 0, _impl->width, _impl->height);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shader);
		glBindVertexArray(vert_array);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		GLenum err = glGetError();
		if (err != GL_NO_ERROR) DebugMessage("Texture failed to render: " + std::to_string(err), __func__);
	}

	void Texture::SetupFramebufferAndTexture(const int& width, const int& height)
	{
		_impl->SetupFramebufferAndTexture(width, height);
	}

	float Texture::GetAspectRatio() const
	{
		return static_cast<float>(_impl->width) / static_cast<float>(_impl->height);
	}
}