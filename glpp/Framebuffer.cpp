#include "Framebuffer.hpp"

namespace gl {

// =============================================================
// == Framebuffer ==============================================
// =============================================================

GLPP_DECL
Framebuffer::Framebuffer() noexcept {
	glGenFramebuffers(1, &mHandle);
}
GLPP_DECL
Framebuffer::~Framebuffer() noexcept {
	if(mHandle)
		glDeleteFramebuffers(1, &mHandle);
}

GLPP_DECL
void Framebuffer::texture(AttachmentType type, unsigned tex, unsigned level) noexcept {
	glNamedFramebufferTexture(mHandle, type, tex, level);
}
GLPP_DECL
void Framebuffer::texture(AttachmentType type, unsigned tex, CubemapFace face, unsigned level) noexcept {
	glNamedFramebufferTexture2DEXT(mHandle, type, tex, face, level);
}
GLPP_DECL
void Framebuffer::renderbuffer(AttachmentType type, unsigned renderbuffer) noexcept {
	glNamedFramebufferRenderbuffer(mHandle, type, GL_RENDERBUFFER, renderbuffer);
}

GLPP_DECL
void Framebuffer::bind(FramebufferMode mode) noexcept {
	glBindFramebuffer(mode, mHandle);
}

GLPP_DECL
FramebufferStatus Framebuffer::checkStatus() const noexcept {
	return (FramebufferStatus) glCheckFramebufferStatus(mHandle);
}

// =============================================================
// == Renderbuffer =============================================
// =============================================================

GLPP_DECL
Renderbuffer::Renderbuffer() noexcept {
	glGenRenderbuffers(1, &mHandle);
}
GLPP_DECL
Renderbuffer::~Renderbuffer() noexcept {
	if(mHandle)
		glDeleteRenderbuffers(1, &mHandle);
}

GLPP_DECL
void Renderbuffer::storage(SizedImageFormat fmt, unsigned width, unsigned height) noexcept {
	glNamedRenderbufferStorage(mHandle, fmt, width, height);
}
GLPP_DECL
void Renderbuffer::storage(unsigned samples, SizedImageFormat fmt, unsigned width, unsigned height) noexcept {
	glNamedRenderbufferStorageMultisample(mHandle, samples, fmt, width, height);
}

} // namespace gl
