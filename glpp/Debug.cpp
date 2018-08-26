#include "Debug.hpp"

#include <iostream>

#ifndef GLPP_DECL
	#define GLPP_DECL
#endif

namespace gl {

GLPP_DECL
std::ostream& operator<<(std::ostream& stream, DebugMessage const& msg) noexcept {
	std::string_view severity;
	switch(msg.severity) {
		default: [[fallthrough]];
		case SEVERITY_LOW:    severity = "i"; break;
		case SEVERITY_MEDIUM: severity = "w"; break;
		case SEVERITY_HIGH:   severity = "e"; break;
	}

	std::string_view source;
	switch(msg.source) {
		case DEBUG_SOURCE_API: source = "[api]"; break;
		case DEBUG_SOURCE_WINDOW_SYSTEM: source = "[window system]"; break;
		case DEBUG_SOURCE_SHADER_COMPILER: source = "[shader compiler]"; break;
		case DEBUG_SOURCE_THIRD_PARTY: source = "[third party]"; break;
		case DEBUG_SOURCE_APPLICATION: source = "[application]"; break;
		default: source = ""; break;
	}

	std::string_view type;
	switch (msg.type) {
		case DEBUG_TYPE_ERROR:               type = "<error>"; break;
		case DEBUG_TYPE_DEPRECATED_BEHAVIOR: type = "<deprecated behavior>"; break;
		case DEBUG_TYPE_UNDEFINED_BEHAVIOR:  type = "<undefined behavior>"; break;
		case DEBUG_TYPE_PORTABILITY:         type = "<portability>"; break;
		case DEBUG_TYPE_PERFORMANCE:         type = "<performance>"; break;
		case DEBUG_TYPE_MARKER:              type = "<marker>"; break;
		case DEBUG_TYPE_PUSH_GROUP:          type = "<push group>"; break;
		case DEBUG_TYPE_POP_GROUP:           type = "<pop group>"; break;
		default: type = ""; break;
	}

	stream << "[GL]" << source << type << "	(" << msg.id << ") " << msg.message;
	return stream;
}

GLPP_DECL
void debugFilter(bool allow, DebugSource source, DebugType type, DebugSeverity severity, uint32_t* ids, uint32_t numIds) noexcept {
	glDebugMessageControl(
		source, type, severity, numIds, ids,
		allow ? GL_TRUE : GL_FALSE
	);
}

// Enable type
void debugFilter(bool allow, DebugType type, DebugSource source) noexcept {
	debugFilter(allow, source, type, SEVERITY_DONT_CARE, nullptr, 0);
}
// Enable severity
void debugFilter(bool allow, DebugSeverity severity, DebugSource source, DebugType type) noexcept {
	debugFilter(allow, source, type, severity, nullptr, 0);
}

GLPP_DECL
void debugCallback(GLDEBUGPROC callback, void* userParam) noexcept {
	glDebugMessageCallback(callback, userParam);
}

GLPP_DECL
void debugCallback(std::ostream& stream) noexcept {
	glDebugMessageCallback(GLPP_MAKE_DEBUGPROC([](DebugMessage const& msg) {
		msg.userdata<std::ostream>() << msg << std::endl;
	}), &stream);
}

GLPP_DECL
void debugCallbackSetDefault() noexcept {
	debugCallback(GLPP_MAKE_DEBUGPROC([](DebugMessage const& msg) {
		switch(msg.severity) {
			default: [[fallthrough]];
			case SEVERITY_LOW:          std::cout << msg << std::endl; break;
			case SEVERITY_MEDIUM:       std::cout << msg << std::endl; break;
			case SEVERITY_HIGH:         std::cerr << msg << std::endl; break;
			case SEVERITY_NOTIFICATION: std::cout << msg << std::endl; break;
		}
	}));
}
GLPP_DECL
void debugCallbackSetNone() noexcept {
	debugCallback(nullptr);
}

GLPP_DECL
void debugSendMessage(
	std::string_view msg,
	DebugSeverity severity, DebugType type, DebugSource source, unsigned id) noexcept
{
	glDebugMessageInsert(source, type, id, severity, msg.size(), msg.data());
}

GLPP_DECL
DebugGroup::DebugGroup(std::string_view message, unsigned id, DebugSource source) noexcept {
	glPushDebugGroup(source, id, message.size(), message.data());
}

GLPP_DECL
DebugGroup::~DebugGroup() noexcept {
	glPopDebugGroup();
}

} // namespace gl
