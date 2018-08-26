#pragma once

#include <GL/glew.h>

#define __GLPP_ENUM_BITFIELD_OPERATORS(ENUM) \
	constexpr inline \
	ENUM operator|(ENUM a, ENUM b) noexcept { \
		using underlying = std::underlying_type_t<ENUM>; \
		return static_cast<ENUM>(static_cast<underlying>(a) | static_cast<underlying>(b)); \
	} \
	constexpr inline \
	ENUM operator&(ENUM a, ENUM b) noexcept { \
		using underlying = std::underlying_type_t<ENUM>; \
		return static_cast<ENUM>(static_cast<underlying>(a) & static_cast<underlying>(b)); \
	} \
	constexpr inline \
	ENUM operator^(ENUM a, ENUM b) noexcept { \
		using underlying = std::underlying_type_t<ENUM>; \
		return static_cast<ENUM>(static_cast<underlying>(a) ^ static_cast<underlying>(b)); \
	} \
	constexpr inline \
	ENUM operator~(ENUM a) noexcept { \
		using underlying = std::underlying_type_t<ENUM>; \
		return static_cast<ENUM>(~static_cast<underlying>(a)); \
	} \
	constexpr inline \
	ENUM& operator|=(ENUM& a, ENUM b) noexcept { return a = (a | b); } \
	constexpr inline \
	ENUM& operator&=(ENUM& a, ENUM b) noexcept { return a = (a & b); } \
	constexpr inline \
	ENUM& operator^=(ENUM& a, ENUM b) noexcept { return a = (a ^ b); }

namespace gl {

enum BasicType {
	// Explicit types
	INT8    = GL_BYTE,
	UINT8   = GL_UNSIGNED_BYTE,
	FLOAT16 = GL_HALF_FLOAT,
	INT16   = GL_SHORT,
	UINT16  = GL_UNSIGNED_SHORT,
	FLOAT32 = GL_FLOAT,
	INT32   = GL_INT,
	UINT32  = GL_UNSIGNED_INT,
	FLOAT64 = GL_DOUBLE,

	// Shorthands
	I8  = INT8,
	U8  = UINT8,
	F16 = FLOAT16,
	I16 = INT16,
	U16 = UINT16,
	F32 = FLOAT32,
	I32 = INT32,
	U32 = UINT32,
	F64 = FLOAT64,

	// "Names"
	BYTE  = INT8,
	SHORT = INT16,
	INT   = INT32,

	UNSIGNED_BYTE  = INT8,
	UNSIGNED_SHORT = INT16,
	UNSIGNED_INT   = INT32,

	HALF_FLOAT = FLOAT16,
	FLOAT      = FLOAT32,
	DOUBLE     = FLOAT64,
};

} // namespace gl