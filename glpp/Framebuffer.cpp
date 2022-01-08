#include "Framebuffer.hpp"

#include <utility>
#include <stdexcept>

#ifndef GLPP_DECL
	#define GLPP_DECL
#endif

namespace gl {

// =============================================================
// == FramebufferState =========================================
// =============================================================

GLPP_DECL
std::string_view to_string(FramebufferStatus status) noexcept {
	switch (status)
	{
		case FRAMEBUFFER_COMPLETE:                      return "Complete";
		case FRAMEBUFFER_INCOMPLETE_ATTACHMENT:         return "Incomplete: attachment";
		case FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT: return "Incomplete: missing attachment";
		case FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:        return "Incomplete: draw buffer";
		case FRAMEBUFFER_INCOMPLETE_READ_BUFFER:        return "Incomplete: read buffer";
		case FRAMEBUFFER_UNSUPPORTED:                   return "Unsupported";
		case FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:        return "Incomplete: multisample";
		case FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:      return "Incomplete: layer targets";
	}
	return "Unkown enum ?????";
}

// =============================================================
// == Framebuffer ==============================================
// =============================================================

GLPP_DECL
Framebuffer::Framebuffer(std::nullptr_t) noexcept {}
GLPP_DECL
Framebuffer::Framebuffer() noexcept { init(); }
GLPP_DECL
Framebuffer::~Framebuffer() noexcept { destroy(); }

GLPP_DECL
Framebuffer::Framebuffer(Framebuffer&& other) noexcept :
	FramebufferView(std::exchange(other.mHandle, 0))
{}
GLPP_DECL
Framebuffer& Framebuffer::operator=(Framebuffer&& other) noexcept {
	destroy();
	mHandle = std::exchange(other.mHandle, 0);
	return *this;
}

GLPP_DECL
void Framebuffer::init() noexcept {
	destroy();
	glGenFramebuffers(1, &mHandle);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, mHandle);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}
GLPP_DECL
void Framebuffer::destroy() noexcept {
	if(mHandle) {
		glDeleteFramebuffers(1, &mHandle);
		mHandle = 0;
	}
}

GLPP_DECL
void FramebufferView::texture(AttachmentType type, unsigned tex, unsigned level) noexcept {
	glNamedFramebufferTexture(mHandle, type, tex, level);
}
GLPP_DECL
void FramebufferView::texture(AttachmentType type, unsigned tex, CubemapFaceIndex face, unsigned level) noexcept {
	glNamedFramebufferTextureLayer(mHandle, type, tex, level, face);
}
GLPP_DECL
void FramebufferView::renderbuffer(AttachmentType type, unsigned renderbuffer) noexcept {
	glNamedFramebufferRenderbuffer(mHandle, type, GL_RENDERBUFFER, renderbuffer);
}

GLPP_DECL
void FramebufferView::drawBuffers(gl::AttachmentType const* attachments, unsigned n) noexcept {
	glNamedFramebufferDrawBuffers(mHandle, n, (GLenum const*)attachments);
}

GLPP_DECL
void FramebufferView::bind(FramebufferMode mode) const noexcept {
	glBindFramebuffer(mode, mHandle);
}

GLPP_DECL
void FramebufferView::unbind(FramebufferMode mode) const noexcept {
	glBindFramebuffer(mode, 0);
}

GLPP_DECL
FramebufferStatus FramebufferView::checkStatus() const noexcept {
	return (FramebufferStatus) glCheckNamedFramebufferStatus(mHandle, GL_FRAMEBUFFER);
}

GLPP_DECL
void FramebufferView::assertStatus() const {
	switch (checkStatus()) {
	case FRAMEBUFFER_COMPLETE: return;
	case FRAMEBUFFER_INCOMPLETE_ATTACHMENT:         throw std::runtime_error("FRAMEBUFFER_INCOMPLETE_ATTACHMENT");
	case FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT: throw std::runtime_error("FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT");
	case FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:        throw std::runtime_error("FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER");
	case FRAMEBUFFER_INCOMPLETE_READ_BUFFER:        throw std::runtime_error("FRAMEBUFFER_INCOMPLETE_READ_BUFFER");
	case FRAMEBUFFER_UNSUPPORTED:                   throw std::runtime_error("FRAMEBUFFER_UNSUPPORTED");
	case FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:        throw std::runtime_error("FRAMEBUFFER_INCOMPLETE_MULTISAMPLE");
	case FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:      throw std::runtime_error("FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS");
	}
}

GLPP_DECL
void FramebufferView::debugLabel(std::string_view s) noexcept {
	glObjectLabel(GL_FRAMEBUFFER, mHandle, s.size(), s.data());
}

// =============================================================
// == Renderbuffer =============================================
// =============================================================

GLPP_DECL
Renderbuffer::Renderbuffer() noexcept { init(); }
GLPP_DECL
Renderbuffer::~Renderbuffer() noexcept { free(); }

GLPP_DECL
Renderbuffer::Renderbuffer(std::nullptr_t) noexcept { /* NOT init(); */ }

GLPP_DECL
void Renderbuffer::init() noexcept {
	glGenRenderbuffers(1, &mHandle);
	glBindRenderbuffer(GL_RENDERBUFFER, mHandle);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
}
GLPP_DECL
void Renderbuffer::free() noexcept {
	if(mHandle) {
		glDeleteRenderbuffers(1, &mHandle);
	}
}


GLPP_DECL
Renderbuffer::Renderbuffer(SizedImageFormat fmt, unsigned width, unsigned height) noexcept :
	Renderbuffer()
{
	storage(fmt, width, height);
}
GLPP_DECL
Renderbuffer::Renderbuffer(unsigned samples, SizedImageFormat fmt, unsigned width, unsigned height) noexcept :
	Renderbuffer()
{
	storage(samples, fmt, width, height);
}

GLPP_DECL
Renderbuffer::Renderbuffer(Renderbuffer&& other) noexcept :
	mHandle(std::exchange(other.mHandle, 0))
{}

GLPP_DECL
Renderbuffer& Renderbuffer::operator=(Renderbuffer&& other) noexcept {
	if(mHandle) {
		glDeleteRenderbuffers(1, &mHandle);
	}
	mHandle = std::exchange(other.mHandle, 0);
	return *this;
}

GLPP_DECL
void Renderbuffer::storage(SizedImageFormat fmt, unsigned width, unsigned height) noexcept {
	glNamedRenderbufferStorage(mHandle, fmt, width, height);
}
GLPP_DECL
void Renderbuffer::storage(unsigned samples, SizedImageFormat fmt, unsigned width, unsigned height) noexcept {
	glNamedRenderbufferStorageMultisample(mHandle, samples, fmt, width, height);
}

GLPP_DECL
void Renderbuffer::debugLabel(std::string_view s) noexcept {
	glObjectLabel(GL_RENDERBUFFER, mHandle, s.size(), s.data());
}

} // namespace gl
