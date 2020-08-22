#pragma once

#include <GL/glew.h>
#include <cstddef>
#include <string_view>

#include "Enums.hpp"

namespace gl {

/// Combines vertex and index buffers as well as the attribute layout in them into an easily bindable thing
class VertexArray {
	unsigned mHandle;
public:
	VertexArray() noexcept;
	~VertexArray() noexcept;

	VertexArray(std::nullptr_t) noexcept;

	void init() noexcept;
	void destroy() noexcept;

	VertexArray(VertexArray&& other) noexcept;
	VertexArray& operator=(VertexArray&& other) noexcept;
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
		size_t stride, size_t offset = 0) noexcept;

	void debugLabel(std::string_view name) noexcept;

	operator unsigned() noexcept { return mHandle; }
};

} // namespace gl
