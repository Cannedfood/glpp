#pragma once

#include "Enums.hpp"

#include <GL/glew.h>

#include <type_traits>
#include <string_view>

namespace gl {

enum BufferType : GLenum {
	ARRAY_BUFFER              = GL_ARRAY_BUFFER,
	ATOMIC_COUNTER_BUFFER     = GL_ATOMIC_COUNTER_BUFFER,
	COPY_READ_BUFFER          = GL_COPY_READ_BUFFER,
	COPY_WRITE_BUFFER         = GL_COPY_WRITE_BUFFER,
	DRAW_INDIRECT_BUFFER      = GL_DRAW_INDIRECT_BUFFER,
	DISPATCH_INDIRECT_BUFFER  = GL_DISPATCH_INDIRECT_BUFFER,
	ELEMENT_ARRAY_BUFFER      = GL_ELEMENT_ARRAY_BUFFER,
	PIXEL_PACK_BUFFER         = GL_PIXEL_PACK_BUFFER,
	PIXEL_UNPACK_BUFFER       = GL_PIXEL_UNPACK_BUFFER,
	QUERY_BUFFER              = GL_QUERY_BUFFER,
	SHADER_STORAGE_BUFFER     = GL_SHADER_STORAGE_BUFFER,
	TRANSFORM_FEEDBACK_BUFFER = GL_TRANSFORM_FEEDBACK_BUFFER,
	UNIFORM_BUFFER            = GL_UNIFORM_BUFFER
};

enum BufferUsage : GLenum {
	STREAM_DRAW  = GL_STREAM_DRAW,
	STREAM_READ  = GL_STREAM_READ,
	STREAM_COPY  = GL_STREAM_COPY,
	STATIC_DRAW  = GL_STATIC_DRAW,
	STATIC_READ  = GL_STATIC_READ,
	STATIC_COPY  = GL_STATIC_COPY,
	DYNAMIC_DRAW = GL_DYNAMIC_DRAW,
	DYNAMIC_READ = GL_DYNAMIC_READ,
	DYNAMIC_COPY = GL_DYNAMIC_COPY
};

enum BufferStorageBits : GLbitfield {
	STORAGE_DEFAULT            = 0,
	// Allow Buffer::subData calls
	STORAGE_DYNAMIC_BIT        = GL_DYNAMIC_STORAGE_BIT,
	// Allow read operations on mapped data
	STORAGE_MAP_READ_BIT       = GL_MAP_READ_BIT,
	// Allow write operations on mapped data
	STORAGE_MAP_WRITE_BIT      = GL_MAP_WRITE_BIT,
	// Allow to keep the mapped pointer indefinately (synchronize writes with flushMapped(start,size))
	STORAGE_MAP_PERSISTENT_BIT = GL_MAP_PERSISTENT_BIT,
	// Make changes instantly visible to the implementation
	STORAGE_MAP_COHERENT_BIT   = GL_MAP_COHERENT_BIT,
	// Hint to store the buffer client-side
	STORAGE_CLIENT_STORAGE_BIT = GL_CLIENT_STORAGE_BIT
};
__GLPP_ENUM_BITFIELD_OPERATORS(BufferStorageBits)

enum BufferAccess {
	READ_ONLY  = GL_READ_ONLY,
	WRITE_ONLY = GL_WRITE_ONLY,
	READ_WRITE = GL_READ_WRITE
};

enum BufferMappingBits : GLbitfield {
	MAP_READ_BIT              = GL_MAP_READ_BIT,
	MAP_WRITE_BIT             = GL_MAP_WRITE_BIT,
	MAP_PERSISTENT_BIT        = GL_MAP_PERSISTENT_BIT,
	MAP_COHERENT_BIT          = GL_MAP_COHERENT_BIT,
	MAP_INVALIDATE_RANGE_BIT  = GL_MAP_INVALIDATE_RANGE_BIT,
	MAP_INVALIDATE_BUFFER_BIT = GL_MAP_INVALIDATE_BUFFER_BIT,
	MAP_FLUSH_EXPLICIT_BIT    = GL_MAP_FLUSH_EXPLICIT_BIT,
	MAP_UNSYNCHRONIZED_BIT    = GL_MAP_UNSYNCHRONIZED_BIT
};
__GLPP_ENUM_BITFIELD_OPERATORS(BufferMappingBits);

template<BufferType kBufferType>
class Buffer {
	unsigned mHandle;
public:
	Buffer() noexcept;
	~Buffer() noexcept;

	Buffer(std::nullptr_t) noexcept;

	Buffer(Buffer&& other) noexcept;
	Buffer& operator=(Buffer&& other) noexcept;
	Buffer(Buffer const& other) noexcept = delete;
	Buffer& operator=(Buffer const& other) noexcept = delete;

	void bind(BufferType as = kBufferType) noexcept;
	void unbind(BufferType as = kBufferType) noexcept;

	void bindBase(GLuint index, BufferType as = kBufferType) const noexcept;
	void bindRange(GLuint index, size_t offset_bytes, size_t size_bytes, BufferType as = kBufferType) const noexcept;

	void storage(BufferStorageBits flags, size_t bytes, void const* data = nullptr) noexcept;

	void data   (BufferUsage usage, size_t bytes, void const* data) noexcept;
	void subdata(size_t offset,     size_t bytes, void const* data) noexcept;

	template<class T> void data(BufferUsage usage, size_t count, T const* pData) noexcept { data(usage, count * sizeof(T), (void const*)pData); }
	template<class T> void subdata(size_t offset_index, size_t count, T const* pData) noexcept { data(offset_index * sizeof(T), count * sizeof(T), (void const*)pData); }

	template<class ContainerT> void data(BufferUsage usage, ContainerT const& c) noexcept { data(usage, c.size(), c.data()); }
	template<class ContainerT> void subdata(size_t offset_index, ContainerT const& c) noexcept { data(offset_index, c.size(), c.data()); }

	// TODO:
	// glClearBuffer
	// glClearBufferSubData
	// glCopyBufferSubData

	void* getPointer() noexcept;

	void invalidate() noexcept;
	void invalidate(size_t offset, size_t length) noexcept;

	void getData(size_t offset, size_t size, void* to) noexcept;

	void* map(BufferAccess access) noexcept;
	void* map(size_t offset, size_t length, BufferMappingBits access) noexcept;
	bool  unmap() noexcept;

	void flushMappedRange(size_t offset, size_t length) noexcept;

	// Getters
	BufferAccess      access()       noexcept;
	BufferMappingBits accessFlags()  noexcept;
	bool              immutable()    noexcept;
	bool              mapped()       noexcept;
	size_t            mapLength()    noexcept;
	size_t            mapOffset()    noexcept;
	size_t            size()         noexcept;
	BufferStorageBits storageFlags() noexcept;
	BufferUsage       usage()        noexcept;

	operator unsigned() noexcept { return mHandle; }

	void debugLabel(std::string_view name) noexcept;
};

inline namespace buffer_types {
	using ArrayBuffer             = Buffer<ARRAY_BUFFER>;
	using AtomicCounterBuffer     = Buffer<ATOMIC_COUNTER_BUFFER>;
	using CopyReadBuffer          = Buffer<COPY_READ_BUFFER>;
	using CopyWriteBuffer         = Buffer<COPY_WRITE_BUFFER>;
	using DrawIndirectBuffer      = Buffer<DRAW_INDIRECT_BUFFER>;
	using DispatchIndirectBuffer  = Buffer<DISPATCH_INDIRECT_BUFFER>;
	using ElementArrayBuffer      = Buffer<ELEMENT_ARRAY_BUFFER>;
	using PixelPackBuffer         = Buffer<PIXEL_PACK_BUFFER>;
	using PixelUnpackBuffer       = Buffer<PIXEL_UNPACK_BUFFER>;
	using QueryBuffer             = Buffer<QUERY_BUFFER>;
	using ShaderStorageBuffer     = Buffer<SHADER_STORAGE_BUFFER>;
	using TransformFeedbackBuffer = Buffer<TRANSFORM_FEEDBACK_BUFFER>;
	using UniformBuffer           = Buffer<UNIFORM_BUFFER>;
}

} // namespace gl
