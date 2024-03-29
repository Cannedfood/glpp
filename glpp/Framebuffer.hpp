#pragma once

#include <GL/glew.h>

#include "Texture.hpp"

#include <string_view>

namespace gl {

enum FramebufferStatus : GLenum {
	FRAMEBUFFER_COMPLETE                      = GL_FRAMEBUFFER_COMPLETE,
	FRAMEBUFFER_INCOMPLETE_ATTACHMENT         = GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT,
	FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT = GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT,
	FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER        = GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER,
	FRAMEBUFFER_INCOMPLETE_READ_BUFFER        = GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER,
	FRAMEBUFFER_UNSUPPORTED                   = GL_FRAMEBUFFER_UNSUPPORTED,
	FRAMEBUFFER_INCOMPLETE_MULTISAMPLE        = GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE,
	FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS      = GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS
};

std::string_view to_string(FramebufferStatus status) noexcept;

enum FramebufferMode {
	READ_FRAMEBUFFER = GL_READ_FRAMEBUFFER,
	DRAW_FRAMEBUFFER = GL_DRAW_FRAMEBUFFER,
	READ_WRITE_FRAMEBUFFER = GL_FRAMEBUFFER
};

enum AttachmentType : GLenum {
	COLOR_ATTACHMENT0        = GL_COLOR_ATTACHMENT0,
	COLOR_ATTACHMENT1        = GL_COLOR_ATTACHMENT1,
	COLOR_ATTACHMENT2        = GL_COLOR_ATTACHMENT2,
	COLOR_ATTACHMENT3        = GL_COLOR_ATTACHMENT3,
	COLOR_ATTACHMENT4        = GL_COLOR_ATTACHMENT4,
	COLOR_ATTACHMENT5        = GL_COLOR_ATTACHMENT5,
	COLOR_ATTACHMENT6        = GL_COLOR_ATTACHMENT6,
	COLOR_ATTACHMENT7        = GL_COLOR_ATTACHMENT7,
	DEPTH_ATTACHMENT         = GL_DEPTH_ATTACHMENT,
	STENCIL_ATTACHMENT       = GL_STENCIL_ATTACHMENT,
	DEPTH_STENCIL_ATTACHMENT = GL_DEPTH_STENCIL_ATTACHMENT
};

class FramebufferView {
protected:
	unsigned mHandle = 0;
public:
	FramebufferView(unsigned handle = 0) : mHandle(handle) {}

	static FramebufferView DefaultFramebuffer() noexcept { return {}; }

	void texture(AttachmentType type, unsigned tex, unsigned level = 0) noexcept;
	void texture(AttachmentType type, unsigned tex, CubemapFaceIndex face, unsigned level = 0) noexcept;
	void renderbuffer(AttachmentType type, unsigned renderbuffer) noexcept;

	void drawBuffers(gl::AttachmentType const* attachments, unsigned n) noexcept;
	template<size_t N>
	void drawBuffers(AttachmentType const (& attachments)[N]) noexcept { drawBuffers(std::data(attachments), std::size(attachments)); }

	void bind(FramebufferMode mode = gl::READ_WRITE_FRAMEBUFFER) const noexcept;
	void unbind(FramebufferMode mode = gl::READ_WRITE_FRAMEBUFFER) const noexcept;

	FramebufferStatus checkStatus() const noexcept;
	void assertStatus() const;

	operator unsigned() const noexcept { return mHandle; }

	void debugLabel(std::string_view s) noexcept;
};

class Framebuffer : public FramebufferView {
public:
	Framebuffer(std::nullptr_t) noexcept;
	Framebuffer() noexcept;
	~Framebuffer() noexcept;

	void init() noexcept;
	void destroy() noexcept;

	Framebuffer(Framebuffer&& other) noexcept;
	Framebuffer& operator=(Framebuffer&& other) noexcept;
	Framebuffer(Framebuffer const& other) noexcept = delete;
	Framebuffer& operator=(Framebuffer const& other) = delete;
};

class Renderbuffer {
	unsigned mHandle = 0;
public:
	Renderbuffer() noexcept;
	~Renderbuffer() noexcept;

	Renderbuffer(std::nullptr_t) noexcept;

	Renderbuffer(SizedImageFormat fmt, unsigned width, unsigned height) noexcept;
	Renderbuffer(unsigned samples, SizedImageFormat fmt, unsigned width, unsigned height) noexcept;

	Renderbuffer(Renderbuffer&& other) noexcept;
	Renderbuffer& operator=(Renderbuffer&& other) noexcept;
	Renderbuffer(Renderbuffer const& other) = delete;
	Renderbuffer& operator=(Renderbuffer const& other) = delete;

	void init() noexcept;
	void free() noexcept;

	void storage(SizedImageFormat fmt, unsigned width, unsigned height) noexcept;
	void storage(unsigned samples, SizedImageFormat fmt, unsigned width, unsigned height) noexcept;

	operator unsigned() noexcept { return mHandle; }

	void debugLabel(std::string_view s) noexcept;
};

} // namespace gl
