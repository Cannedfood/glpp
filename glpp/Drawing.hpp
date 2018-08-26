#pragma once

#include <GL/glew.h>

#include "Enums.hpp"

namespace gl {

enum Topography {
	POINTS         = GL_POINTS,
	LINES          = GL_LINES,
	TRIANGLES      = GL_TRIANGLES,
	TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
	QUADS          = GL_QUADS,
};

enum ClearFlags {
	COLOR   = GL_COLOR_BUFFER_BIT,
	DEPTH   = GL_DEPTH_BUFFER_BIT,
	STENCIL = GL_STENCIL_BUFFER_BIT
};
__GLPP_ENUM_BITFIELD_OPERATORS(ClearFlags)

inline
void clear(ClearFlags flags) {
	glClear(flags);
}

template<class... Args> inline
void clear(ClearFlags flag1, Args... args) {
	clear(flag1 | (args | ...));
}

inline
void drawBuffers(Topography topo) noexcept {
	// glDrawBuffer(topo);
}

inline
void drawElements(Topography topo, GLsizei count, BasicType indexType, size_t indexBufferOffset = 0) noexcept {
	glDrawElements(topo, count, indexType, (void*)indexBufferOffset);
}

} // namespace gl