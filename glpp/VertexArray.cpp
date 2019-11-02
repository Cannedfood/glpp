#include "VertexArray.hpp"

#ifndef GLPP_DECL
	#define GLPP_DECL
#endif

#include <utility>

namespace gl {

GLPP_DECL
VertexArray::VertexArray() noexcept :
	mHandle(0)
{
	gen();
}

GLPP_DECL
VertexArray::~VertexArray() noexcept {
	destroy();
}

GLPP_DECL
void VertexArray::gen() noexcept {
	destroy();
	glGenVertexArrays(1, &mHandle);
	bind();
	unbind();
}
GLPP_DECL
void VertexArray::destroy() noexcept {
	if(mHandle) {
		glDeleteVertexArrays(1, &mHandle);
		mHandle = 0;
	}
}

GLPP_DECL
VertexArray::VertexArray(VertexArray&& other) noexcept :
	mHandle(std::exchange(other.mHandle, 0))
{}
GLPP_DECL
VertexArray& VertexArray::operator=(VertexArray&& other) noexcept {
	destroy();
	mHandle = std::exchange(other.mHandle, 0);
	return *this;
}

GLPP_DECL
void VertexArray::bind() noexcept {
	glBindVertexArray(mHandle);
}

GLPP_DECL
void VertexArray::unbind() noexcept {
	glBindVertexArray(0);
}

GLPP_DECL
void VertexArray::enableAttrib(GLuint index) noexcept {
	glEnableVertexArrayAttrib(mHandle, index);
}
GLPP_DECL
void VertexArray::disableAttrib(GLuint index) noexcept {
	glDisableVertexArrayAttrib(mHandle, index);
}

GLPP_DECL
void VertexArray::bindElements(unsigned buffer) noexcept {
	glVertexArrayElementBuffer(mHandle, buffer);
}

GLPP_DECL
void VertexArray::bindAttribute(
	GLuint bufferBindingIndex,
	GLuint attribIndex,
	BasicType type, GLint componentCount,
	GLuint relativeOffset,
	bool normalize) noexcept
{
	switch(type) {
		case INT8: case INT16: case INT32: case UINT8: case UINT16: case UINT32:
			if(normalize) [[fallthrough]];
			else {
				glVertexArrayAttribIFormat(mHandle, attribIndex, componentCount, type, relativeOffset);
				break;
			}
		case FLOAT16: case FLOAT32:
			glVertexArrayAttribFormat(mHandle, attribIndex, componentCount, type, normalize ? GL_TRUE : GL_FALSE, relativeOffset);
			break;
		case FLOAT64:
			glVertexArrayAttribLFormat(mHandle, attribIndex, componentCount, type, relativeOffset);
			break;
	}
	glVertexArrayAttribBinding(mHandle, attribIndex, bufferBindingIndex);
	enableAttrib(attribIndex);
}
GLPP_DECL
void VertexArray::bindBuffer(
	GLuint bufferBindingIndex,
	unsigned buffer,
	size_t stride, size_t offset) noexcept
{
	glVertexArrayVertexBuffer(mHandle, bufferBindingIndex, buffer, offset, stride);
}

GLPP_DECL
void VertexArray::debugLabel(std::string_view name) noexcept {
	glObjectLabel(GL_VERTEX_ARRAY, mHandle, name.size(), name.data());
}

} // namespace gl
