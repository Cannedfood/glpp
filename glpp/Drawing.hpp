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
void drawElements(Topography topo, BasicType indexType, size_t firstIndex, GLsizei count) noexcept {
	firstIndex *= sizeOf(indexType);
	glDrawElements(topo, count, indexType, (void*)firstIndex);
}

inline
void drawElements(Topography topo, BasicType indexType, GLsizei count) noexcept {
	drawElements(topo, indexType, 0, count);
}

inline
void drawElementsInstanced(uint32_t instanceCount, Topography topo, BasicType type, uint32_t firstIndex, uint32_t count) noexcept {
	glDrawElementsInstanced(topo, count, type, (void*)(firstIndex * sizeOf(type)), instanceCount);
}

inline
void drawElementsInstanced(uint32_t instanceCount, Topography topo, BasicType type, uint32_t count) noexcept {
	drawElementsInstanced(instanceCount, topo, type, 0, count);
}

inline
void drawArrays(Topography topo, int count, int first = 0) noexcept {
	glDrawArrays(topo, first, count);
}

} // namespace gl
