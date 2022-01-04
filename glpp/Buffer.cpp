#include "Buffer.hpp"

#include <cassert>
#include <cmath>
#include <utility>

#ifndef GLPP_DECL
	#define GLPP_DECL
#endif

namespace gl {

/*____         __  __
 | __ ) _   _ / _|/ _| ___ _ __
 |  _ \| | | | |_| |_ / _ \ '__|
 | |_) | |_| |  _|  _|  __/ |
 |____/ \__,_|_| |_|  \___|*/

template<BufferType type> GLPP_DECL
Buffer<type>::Buffer() noexcept {
	init();
}

template<BufferType type> GLPP_DECL
Buffer<type>::~Buffer() noexcept {
	destroy();
}

template<BufferType type> GLPP_DECL
Buffer<type>::Buffer(std::nullptr_t) noexcept :
	BufferView<type>(0)
{}

template<BufferType type> GLPP_DECL
Buffer<type>::Buffer(BufferUsage usage, size_t bytes, void const* data) noexcept :
	Buffer()
{
	this->data(usage, bytes, data);
}

template<BufferType type> GLPP_DECL
void Buffer<type>::init() noexcept {
	destroy();

	glGenBuffers(1, &this->mHandle);

	// Let the driver know what kind of buffer we want by binding it once; Will cause bugs on some drivers otherwise
	this->bind();
	this->unbind();
}
template<BufferType type> GLPP_DECL
void Buffer<type>::destroy() noexcept {
	if(this->mHandle) {
		glDeleteBuffers(1, &this->mHandle);
		this->mHandle = 0;
	}
}

// -- Move -------------------------------------------------------

template<BufferType type> GLPP_DECL
Buffer<type>::Buffer(Buffer&& other) noexcept :
	BufferView<type>(std::exchange(other.mHandle, 0))
{}

template<BufferType type> GLPP_DECL
Buffer<type>& Buffer<type>::operator=(Buffer&& other) noexcept {
	destroy();
	this->mHandle = std::exchange(other.mHandle, 0);
	return *this;
}


/*____         __  __         __     ___
 | __ ) _   _ / _|/ _| ___ _ _\ \   / (_) _____      __
 |  _ \| | | | |_| |_ / _ \ '__\ \ / /| |/ _ \ \ /\ / /
 | |_) | |_| |  _|  _|  __/ |   \ V / | |  __/\ V  V /
 |____/ \__,_|_| |_|  \___|_|    \_/  |_|\___| \_/\*/

template<BufferType type> GLPP_DECL
void BufferView<type>::bind(BufferType as) noexcept {
	glBindBuffer(as, mHandle);
}

template<BufferType type> GLPP_DECL
void BufferView<type>::unbind(BufferType from) noexcept {
	glBindBuffer(from, 0);
}

template<BufferType type> GLPP_DECL
void BufferView<type>::bindBase(GLuint index, BufferType as) const noexcept {
	glBindBufferBase(as, index, mHandle);
}
template<BufferType type> GLPP_DECL
void BufferView<type>::bindRange(GLuint index, size_t offset_bytes, size_t size_bytes, BufferType as) const noexcept {
	glBindBufferRange(as, index, mHandle, offset_bytes, size_bytes);
}

template<BufferType type> GLPP_DECL
void BufferView<type>::storage(BufferStorageBits flags, size_t bytes, void const* data) noexcept {
	glNamedBufferStorage(mHandle, bytes, data, flags);
}

template<BufferType type> GLPP_DECL
void BufferView<type>::data(BufferUsage usage, size_t bytes, void const* data) noexcept {
	// TODO: glBufferData fallback
	glNamedBufferData(mHandle, bytes, data, usage);
}

template<BufferType type> GLPP_DECL
void BufferView<type>::subdata(size_t offset, size_t bytes, void const* data) noexcept {
	// TODO: glBufferData fallback
	glNamedBufferSubData(mHandle, offset, bytes, data);
}

template<BufferType type> GLPP_DECL
void* BufferView<type>::getPointer() noexcept {
	// glFlushMappedNamedBufferRange(mHandle, offset, size);
	void* result;
	glGetNamedBufferPointerv(mHandle, GL_BUFFER_MAP_POINTER, &result);
	return result;
}

template<BufferType type> GLPP_DECL
void BufferView<type>::invalidate() noexcept {
	glInvalidateBufferData(mHandle);
}

template<BufferType type> GLPP_DECL
void BufferView<type>::invalidate(size_t offset, size_t length) noexcept {
	glInvalidateBufferData(mHandle);
}

template<BufferType type> GLPP_DECL
void BufferView<type>::getData(size_t offset, size_t size, void* to) noexcept {
	glGetNamedBufferSubData(mHandle, offset, size, to);
}

template<BufferType type> GLPP_DECL
void* BufferView<type>::map(BufferAccess access) noexcept {
	return glMapNamedBuffer(mHandle, access);
}

template<BufferType type> GLPP_DECL
void* BufferView<type>::map(size_t offset, size_t length, BufferMappingBits access) noexcept {
	return glMapNamedBufferRange(mHandle, offset, length, access);
}

template<BufferType type> GLPP_DECL
bool BufferView<type>::unmap() noexcept {
	return glUnmapNamedBuffer(mHandle) == GL_TRUE;
}

template<BufferType type> GLPP_DECL
void BufferView<type>::flushMappedRange(size_t offset, size_t length) noexcept {
	glFlushMappedNamedBufferRange(mHandle, offset, length);
}

template<BufferType type> GLPP_DECL
BufferAccess      BufferView<type>::access() noexcept {
	GLint result;
	glGetNamedBufferParameteriv(mHandle, GL_BUFFER_ACCESS, &result);
	return static_cast<BufferAccess>(result);
}
template<BufferType type> GLPP_DECL
BufferMappingBits BufferView<type>::accessFlags() noexcept {
	GLbitfield result;
	glGetNamedBufferParameteriv(mHandle, GL_BUFFER_ACCESS_FLAGS, (GLint*)&result);
	return static_cast<BufferMappingBits>(result);
}
template<BufferType type> GLPP_DECL
bool              BufferView<type>::immutable() noexcept {
	GLint result;
	glGetNamedBufferParameteriv(mHandle, GL_BUFFER_IMMUTABLE_STORAGE, &result);
	return result == GL_TRUE;
}
template<BufferType type> GLPP_DECL
bool              BufferView<type>::mapped() noexcept {
	GLint result;
	glGetNamedBufferParameteriv(mHandle, GL_BUFFER_MAPPED, &result);
	return result == GL_TRUE;
}
template<BufferType type> GLPP_DECL
size_t            BufferView<type>::mapLength() noexcept {
	GLint64 result;
	glGetNamedBufferParameteri64v(mHandle, GL_BUFFER_MAP_LENGTH, &result);
	return result;
}
template<BufferType type> GLPP_DECL
size_t            BufferView<type>::mapOffset() noexcept {
	GLint64 result;
	glGetNamedBufferParameteri64v(mHandle, GL_BUFFER_MAP_OFFSET, &result);
	return result;
}
template<BufferType type> GLPP_DECL
size_t            BufferView<type>::size() noexcept {
	GLint64 result;
	glGetNamedBufferParameteri64v(mHandle, GL_BUFFER_SIZE, &result);
	return result;
}
template<BufferType type> GLPP_DECL
BufferStorageBits BufferView<type>::storageFlags() noexcept {
	GLbitfield result;
	glGetNamedBufferParameteriv(mHandle, GL_BUFFER_ACCESS_FLAGS, reinterpret_cast<GLint*>(&result));
	return static_cast<BufferStorageBits>(result);
}
template<BufferType type> GLPP_DECL
BufferUsage       BufferView<type>::usage() noexcept {
	int result;
	glGetBufferParameteriv(mHandle, GL_BUFFER_USAGE, &result);
	return static_cast<BufferUsage>(result);
}

template<BufferType type> GLPP_DECL
void BufferView<type>::debugLabel(std::string_view name) noexcept {
	glObjectLabel(GL_BUFFER, mHandle, name.size(), name.data());
}

GLPP_DECL
void copyBufferSubdata(
	GLuint srcBuffer, GLuint dstBuffer,
	GLintptr srcOffset, GLintptr dstOffset,
	GLsizeiptr size)
{
	assert((srcBuffer != dstBuffer || srcOffset >= dstOffset + size || dstOffset >= srcOffset) && "Overlapping ranges are not allowed for gl::copyBufferSubdata, use the helper function gl::copyBufferSubdataOverlapping instead.");
	glCopyNamedBufferSubData(srcBuffer, dstBuffer, srcOffset, dstOffset, size);
}

GLPP_DECL
void copyBufferSubdataOverlapping(
	GLuint buffer,
	GLintptr srcOffset, GLintptr dstOffset,
	GLsizeiptr size)
{
	if(srcOffset == dstOffset)
		return; // Nothing to do!
	else if(srcOffset >= dstOffset + size || dstOffset >= srcOffset + size) {
		// No overlap!
		copyBufferSubdata(buffer, buffer, srcOffset, dstOffset, size);
	}
	else if(dstOffset < srcOffset) {
		GLintptr copyStep  = std::abs(srcOffset - dstOffset);
		GLintptr remainder = size % copyStep;
		for(GLintptr i = 0; i < size / copyStep; i++)
			copyBufferSubdata(buffer, buffer, srcOffset + i * copyStep, dstOffset + i * copyStep, copyStep);
		copyBufferSubdata(buffer, buffer, srcOffset + size - remainder, dstOffset + size - remainder, remainder);
	}
	else /* if(dstOffset > srcOffset)  */ {
		GLintptr copyStep  = std::abs(srcOffset - dstOffset);
		GLintptr remainder = size % copyStep;
		copyBufferSubdata(buffer, buffer, srcOffset + size - remainder, dstOffset + size - remainder, remainder);
		for(GLintptr i = (size / copyStep) - 1; i >= 0; i--)
			copyBufferSubdata(buffer, buffer, srcOffset + i * copyStep, dstOffset + i * copyStep, copyStep);
	}

	// TODO: make more efficient for very small copySteps and large buffers (maybe use auxiliary buffers?)
}

/*_            __  __               _
 | |__  _   _ / _|/ _| ___ _ __    | |_ _   _ _ __   ___  ___
 | '_ \| | | | |_| |_ / _ \ '__|   | __| | | | '_ \ / _ \/ __|
 | |_) | |_| |  _|  _|  __/ | _____| |_| |_| | |_) |  __/\__ \
 |_.__/ \__,_|_| |_|  \___|_|/_____\\__|\__, | .__/ \___||___/
                                        |___/|*/

template class Buffer<ARRAY_BUFFER>;
template class Buffer<ATOMIC_COUNTER_BUFFER>;
template class Buffer<COPY_READ_BUFFER>;
template class Buffer<COPY_WRITE_BUFFER>;
template class Buffer<DRAW_INDIRECT_BUFFER>;
template class Buffer<DISPATCH_INDIRECT_BUFFER>;
template class Buffer<ELEMENT_ARRAY_BUFFER>;
template class Buffer<PIXEL_PACK_BUFFER>;
template class Buffer<PIXEL_UNPACK_BUFFER>;
template class Buffer<QUERY_BUFFER>;
template class Buffer<SHADER_STORAGE_BUFFER>;
template class Buffer<TRANSFORM_FEEDBACK_BUFFER>;
template class Buffer<UNIFORM_BUFFER>;

} // namespace gl
