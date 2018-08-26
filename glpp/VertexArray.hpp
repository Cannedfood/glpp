#pragma once

#include <GL/glew.h>
#include <cstddef>

#include "Enums.hpp"

namespace gl {

class VertexArray {
	unsigned mHandle;
public:
	VertexArray() noexcept;
	~VertexArray() noexcept;

	VertexArray(VertexArray&& other) noexcept                 = delete;
	VertexArray& operator=(VertexArray&& other) noexcept      = delete;
	VertexArray(VertexArray const& other) noexcept            = delete;
	VertexArray& operator=(VertexArray const& other) noexcept = delete;

	void bind() noexcept;
	static void unbind() noexcept;

	void enableAttrib(GLuint index) noexcept;
	void disableAttrib(GLuint index) noexcept;

	/// Binds an index buffer
	void bindElements(unsigned buffer) noexcept;

	/// Binds a buffer to attribIndex, including format. Can be split into calls to vertexFormat and vertexBuffer
	void bindAttribute(
		GLuint bufferBindingIndex,
		GLuint attribIndex,
		BasicType type, GLint componentCount,
		GLuint relativeOffset = 0,
		bool normalize = false) noexcept;
	void bindBuffer(
		GLuint bufferBindingIndex,
		unsigned buffer,
		size_t stride = 0, size_t offset = 0) noexcept;
};

} // namespace gl
