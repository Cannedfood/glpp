#pragma once

#include <GL/glew.h>

#include <string_view>
#include <iosfwd>

namespace gl {

enum DebugSource : GLenum {
	DEBUG_SOURCE_API             = GL_DEBUG_SOURCE_API,
	DEBUG_SOURCE_WINDOW_SYSTEM   = GL_DEBUG_SOURCE_WINDOW_SYSTEM,
	DEBUG_SOURCE_SHADER_COMPILER = GL_DEBUG_SOURCE_SHADER_COMPILER,
	DEBUG_SOURCE_THIRD_PARTY     = GL_DEBUG_SOURCE_THIRD_PARTY,
	DEBUG_SOURCE_APPLICATION     = GL_DEBUG_SOURCE_APPLICATION,
	DEBUG_SOURCE_OTHER           = GL_DEBUG_SOURCE_OTHER,
	DEBUG_SOURCE_DONT_CARE       = GL_DONT_CARE
};

enum DebugType : GLenum {
	DEBUG_TYPE_ERROR               = GL_DEBUG_TYPE_ERROR,
	DEBUG_TYPE_DEPRECATED_BEHAVIOR = GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR,
	DEBUG_TYPE_UNDEFINED_BEHAVIOR  = GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR,
	DEBUG_TYPE_PORTABILITY         = GL_DEBUG_TYPE_PORTABILITY,
	DEBUG_TYPE_PERFORMANCE         = GL_DEBUG_TYPE_PERFORMANCE,
	DEBUG_TYPE_OTHER               = GL_DEBUG_TYPE_OTHER,
	DEBUG_TYPE_MARKER              = GL_DEBUG_TYPE_MARKER,
	DEBUG_TYPE_PUSH_GROUP          = GL_DEBUG_TYPE_PUSH_GROUP,
	DEBUG_TYPE_POP_GROUP           = GL_DEBUG_TYPE_POP_GROUP,
	DEBUG_TYPE_DONT_CARE           = GL_DONT_CARE
};

enum DebugSeverity : GLenum {
	SEVERITY_LOW          = GL_DEBUG_SEVERITY_LOW,
	SEVERITY_MEDIUM       = GL_DEBUG_SEVERITY_MEDIUM,
	SEVERITY_HIGH         = GL_DEBUG_SEVERITY_HIGH,
	SEVERITY_NOTIFICATION = GL_DEBUG_SEVERITY_NOTIFICATION,
	SEVERITY_DONT_CARE    = GL_DONT_CARE
};

struct DebugMessage {
	DebugSource      source;
	DebugType        type;
	unsigned         id;
	DebugSeverity    severity;
	std::string_view message;
	void const*      puserdata;

	template<class T>
	T* userptr() const noexcept { return reinterpret_cast<T*>(const_cast<void*>(puserdata)); }
	template<class T>
	T& userdata() const noexcept { return *userptr<T>(); }
};
std::ostream& operator<<(std::ostream& stream, DebugMessage const& msg) noexcept;

void debugFilter(bool allow, DebugSource source, DebugType type, DebugSeverity severity, uint32_t* ids, uint32_t numIds) noexcept;

// Enable type
void debugFilter(bool allow, DebugType type, DebugSource source = DEBUG_SOURCE_DONT_CARE) noexcept;
// Enable severity
void debugFilter(bool allow, DebugSeverity severity, DebugSource source = DEBUG_SOURCE_DONT_CARE, DebugType type = DEBUG_TYPE_DONT_CARE) noexcept;

template<size_t N>
void debugFilter(bool allow, DebugSource source, DebugType type, uint32_t const (&ids)[N]) noexcept;

void debugCallback(GLDEBUGPROC callback, void* userParam = nullptr) noexcept;
void debugCallback(std::ostream& stream) noexcept;
void debugCallbackSetDefault() noexcept;
void debugCallbackSetNone() noexcept;

void debugSendMessage(
	std::string_view msg,
	DebugSeverity severity = SEVERITY_NOTIFICATION,
	DebugType type = DEBUG_TYPE_OTHER,
	DebugSource source = DEBUG_SOURCE_APPLICATION,
	unsigned id = 0) noexcept;

struct DebugGroup {
	DebugGroup(std::string_view message, unsigned id = 0, DebugSource source = DEBUG_SOURCE_APPLICATION) noexcept;
	~DebugGroup() noexcept;
};

} // namespace gl

// Adapter from GLDEBUGPROC to void(*)(::gl::DebugMessage const&)
#define GLPP_MAKE_DEBUGPROC(FN) \
(GLDEBUGPROC) ([]( \
	GLenum _glpp_param_source, \
	GLenum _glpp_param_type, \
	GLuint _glpp_param_id, \
	GLenum _glpp_param_severity, \
	GLsizei _glpp_param_length, GLchar const* _glpp_param_message, \
	void const* _glpp_param_userParam \
) { \
	FN(::gl::DebugMessage{ \
		static_cast<::gl::DebugSource>(_glpp_param_source), \
		static_cast<::gl::DebugType>(_glpp_param_type), \
		_glpp_param_id, \
		static_cast<::gl::DebugSeverity>(_glpp_param_severity), \
		{ _glpp_param_message, static_cast<size_t>(_glpp_param_length) }, \
		_glpp_param_userParam \
	}); \
})


// =============================================================
// == Inline implementations =============================================
// =============================================================

namespace gl {

template<size_t N>
void debugFilter(
	bool allow,
	DebugSource source, DebugType type,
	uint32_t const (&ids)[N]) noexcept
{
	debugFilter(allow, source, type, gl::SEVERITY_DONT_CARE, const_cast<uint32_t*>(ids), std::size(ids));
}

} // namespace gl

#ifndef NDEBUG
#define GLPP_DEBUG_SCOPE() ::gl::DebugGroup _glpp_debug_group(__PRETTY_FUNCTION__)
#define GLPP_DEBUG_GROUP(MSG) ::gl::DebugGroup _glpp_debug_group(MSG)
#else
#define GLPP_DEBUG_SCOPE()
#define GLPP_DEBUG_GROUP(MSG)
#endif