#include "Buffer.hpp"

#ifndef GLPP_DECL
	#define GLPP_DECL
#endif

namespace gl {

template<BufferType type> GLPP_DECL
Buffer<type>::Buffer() noexcept {
	glGenBuffers(1, &mHandle);
	bind(); unbind(); // Let the driver know what kind of buffer we want by binding it once
}

template<BufferType type> GLPP_DECL
Buffer<type>::~Buffer() noexcept {
	if(mHandle)
		glDeleteBuffers(1, &mHandle);
}

template<BufferType type> GLPP_DECL
Buffer<type>::Buffer(std::nullptr_t) noexcept :
	mHandle(0)
{}

// -- Move -------------------------------------------------------

template<BufferType type> GLPP_DECL
Buffer<type>::Buffer(Buffer&& other) noexcept :
	mHandle(other.mHandle)
{
	other.mHandle = 0;
}

template<BufferType type> GLPP_DECL
Buffer<type>& Buffer<type>::operator=(Buffer&& other) noexcept {
	if(mHandle)
		glDeleteBuffers(1, &mHandle);
	mHandle = other.mHandle;
	other.mHandle = 0;
	return *this;
}

// -- Functionality -----------------------------------------------------

template<BufferType type> GLPP_DECL
void Buffer<type>::bind(BufferType as) noexcept {
	glBindBuffer(as, mHandle);
}

template<BufferType type> GLPP_DECL
void Buffer<type>::unbind(BufferType from) noexcept {
	glBindBuffer(from, 0);
}

template<BufferType type> GLPP_DECL
void Buffer<type>::bindBase(GLuint index, BufferType as) const noexcept {
	glBindBufferBase(as, index, mHandle);
}
template<BufferType type> GLPP_DECL
void Buffer<type>::bindRange(GLuint index, size_t offset_bytes, size_t size_bytes, BufferType as) const noexcept {
	glBindBufferRange(as, index, mHandle, offset_bytes, size_bytes);
}

template<BufferType type> GLPP_DECL
void Buffer<type>::storage(BufferStorageBits flags, size_t bytes, void const* data) noexcept {
	glNamedBufferStorage(mHandle, bytes, data, flags);
}

template<BufferType type> GLPP_DECL
void Buffer<type>::data(BufferUsage usage, size_t bytes, void const* data) noexcept {
	// TODO: glBufferData fallback
	glNamedBufferData(mHandle, bytes, data, usage);
}

template<BufferType type> GLPP_DECL
void Buffer<type>::subdata(size_t offset, size_t bytes, void const* data) noexcept {
	// TODO: glBufferData fallback
	glNamedBufferSubData(mHandle, offset, bytes, data);
}

template<BufferType type> GLPP_DECL
void* Buffer<type>::getPointer() noexcept {
	// glFlushMappedNamedBufferRange(mHandle, offset, size);
	void* result;
	glGetNamedBufferPointerv(mHandle, GL_BUFFER_MAP_POINTER, &result);
	return result;
}

template<BufferType type> GLPP_DECL
void Buffer<type>::invalidate() noexcept {
	glInvalidateBufferData(mHandle);
}

template<BufferType type> GLPP_DECL
void Buffer<type>::invalidate(size_t offset, size_t length) noexcept {
	glInvalidateBufferData(mHandle);
}

template<BufferType type> GLPP_DECL
void Buffer<type>::getData(size_t offset, size_t size, void* to) noexcept {
	glGetNamedBufferSubData(mHandle, offset, size, to);
}

template<BufferType type> GLPP_DECL
void* Buffer<type>::map(BufferAccess access) noexcept {
	return glMapNamedBuffer(mHandle, access);
}

template<BufferType type> GLPP_DECL
void* Buffer<type>::map(size_t offset, size_t length, BufferMappingBits access) noexcept {
	return glMapNamedBufferRange(mHandle, offset, length, access);
}

template<BufferType type> GLPP_DECL
bool Buffer<type>::unmap() noexcept {
	return glUnmapNamedBuffer(mHandle) == GL_TRUE;
}

template<BufferType type> GLPP_DECL
void Buffer<type>::flushMappedRange(size_t offset, size_t length) noexcept {
	glFlushMappedNamedBufferRange(mHandle, offset, length);
}

template<BufferType type> GLPP_DECL
BufferAccess      Buffer<type>::access() noexcept {
	GLint result;
	glGetNamedBufferParameteriv(mHandle, GL_BUFFER_ACCESS, &result);
	return static_cast<BufferAccess>(result);
}
template<BufferType type> GLPP_DECL
BufferMappingBits Buffer<type>::accessFlags() noexcept {
	GLbitfield result;
	glGetNamedBufferParameteriv(mHandle, GL_BUFFER_ACCESS_FLAGS, (GLint*)&result);
	return static_cast<BufferMappingBits>(result);
}
template<BufferType type> GLPP_DECL
bool              Buffer<type>::immutable() noexcept {
	GLint result;
	glGetNamedBufferParameteriv(mHandle, GL_BUFFER_IMMUTABLE_STORAGE, &result);
	return result == GL_TRUE;
}
template<BufferType type> GLPP_DECL
bool              Buffer<type>::mapped() noexcept {
	GLint result;
	glGetNamedBufferParameteriv(mHandle, GL_BUFFER_MAPPED, &result);
	return result == GL_TRUE;
}
template<BufferType type> GLPP_DECL
size_t            Buffer<type>::mapLength() noexcept {
	GLint64 result;
	glGetNamedBufferParameteri64v(mHandle, GL_BUFFER_MAP_LENGTH, &result);
	return result;
}
template<BufferType type> GLPP_DECL
size_t            Buffer<type>::mapOffset() noexcept {
	GLint64 result;
	glGetNamedBufferParameteri64v(mHandle, GL_BUFFER_MAP_OFFSET, &result);
	return result;
}
template<BufferType type> GLPP_DECL
size_t            Buffer<type>::size() noexcept {
	GLint64 result;
	glGetNamedBufferParameteri64v(mHandle, GL_BUFFER_SIZE, &result);
	return result;
}
template<BufferType type> GLPP_DECL
BufferStorageBits Buffer<type>::storageFlags() noexcept {
	GLbitfield result;
	glGetNamedBufferParameteriv(mHandle, GL_BUFFER_ACCESS_FLAGS, reinterpret_cast<GLint*>(&result));
	return static_cast<BufferStorageBits>(result);
}
template<BufferType type> GLPP_DECL
BufferUsage       Buffer<type>::usage() noexcept {
	int result;
	glGetBufferParameteriv(mHandle, GL_BUFFER_USAGE, &result);
	return static_cast<BufferUsage>(result);
}

template<BufferType type> GLPP_DECL
void Buffer<type>::debugLabel(std::string_view name) noexcept {
	glObjectLabel(GL_BUFFER, mHandle, name.size(), name.data());
}

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
