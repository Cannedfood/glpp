#pragma once

#include <GL/glew.h>

namespace gl {

inline
void enableDepthTest(bool b = true) noexcept {
	if(b) glEnable(GL_DEPTH_TEST);
	else  glDisable(GL_DEPTH_TEST);
}
inline
void enableDepthWrite(bool b = true) noexcept {
	if(b) glEnable(GL_DEPTH_WRITEMASK);
	else  glDisable(GL_DEPTH_WRITEMASK);
}

inline
void enableCullFace(bool b = true) noexcept {
	if(b) glEnable(GL_CULL_FACE);
	else  glDisable(GL_CULL_FACE);
}

enum Side {
	BACK           = GL_BACK,
	FRONT          = GL_FRONT,
	FRONT_AND_BACK = GL_FRONT_AND_BACK
};

inline
void cullFace(Side side) noexcept {
	glCullFace(side);
}

inline
void viewport(unsigned width, unsigned height) noexcept {
	glViewport(0, 0, width, height);
}
inline
void viewport(unsigned x, unsigned y, unsigned width, unsigned height) noexcept {
	glViewport(x, y, width, height);
}

inline
void scissor(unsigned width, unsigned height) noexcept {
	glScissor(0, 0, width, height);
}
inline
void scissor(unsigned x, unsigned y, unsigned width, unsigned height) noexcept {
	glScissor(x, y, width, height);
}

} // namespace gl
