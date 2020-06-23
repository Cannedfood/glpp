#pragma once

#include <GL/glew.h>

#include "Enums.hpp"

#include <cstdio>
#include <exception>

namespace gl {

enum Topography {
	POINTS         = GL_POINTS,
	LINES          = GL_LINES,
	TRIANGLES      = GL_TRIANGLES,
	TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
	QUADS          = GL_QUADS,
};

enum ClearFlags {
	COLOR_BUFFER   = GL_COLOR_BUFFER_BIT,
	DEPTH_BUFFER   = GL_DEPTH_BUFFER_BIT,
	STENCIL_BUFFER = GL_STENCIL_BUFFER_BIT
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
void drawElements(Topography topo, BasicType indexType, size_t firstIndex, GLsizei count) noexcept {

	switch(indexType) {
		case BYTE:  case UNSIGNED_BYTE: break;
		case SHORT: case UNSIGNED_SHORT: firstIndex *= sizeof(short); break;
		case INT:   case UNSIGNED_INT: firstIndex *= sizeof(int); break;
		default: fprintf(stderr, "Unsupported index type"); std::terminate(); break;
	}
	glDrawElements(topo, count, indexType, (void*)firstIndex);
}

inline
void drawElements(Topography topo, BasicType indexType, GLsizei count) noexcept {
	drawElements(topo, indexType, 0, count);
}

inline
void drawArrays(Topography topo, int count, int first = 0) noexcept {
	glDrawArrays(topo, first, count);
}

} // namespace gl
