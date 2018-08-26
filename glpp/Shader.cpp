#include "Shader.hpp"

#include <string>
#include <stdexcept>

#ifndef GLPP_DECL
	#define GLPP_DECL
#endif

namespace gl {

GLPP_DECL
Shader::Shader(ShaderType type) noexcept :
	mHandle(glCreateShader(type))
{
	// assert(mHandle);
}

GLPP_DECL
Shader::~Shader() noexcept {
	glDeleteShader(mHandle);
}

GLPP_DECL
Shader::Shader(ShaderType type, char const* source, int len) :
	Shader(type)
{
	compileGLSL(source, len);
	if(!compileStatus()) {
		throw std::runtime_error("Failed compiling shader:\n" + infoLog());
	}
}
GLPP_DECL
Shader::Shader(ShaderType type, std::string_view source) :
	Shader(type, source.data(), source.size())
{}
GLPP_DECL
void Shader::compileGLSL(char const* data, int size) noexcept {
	glShaderSource(mHandle, 1, &data, size >= 0 ? &size : nullptr);
	glCompileShader(mHandle);

	// TODO: check status
}

GLPP_DECL
Shader::Shader(ShaderType type, uint8_t const* source, int len) :
	Shader(type)
{
	loadSpirv(source, len);
	// TODO: specialize
	if(!compileStatus()) {
		throw std::runtime_error("Failed loading spirv:\n" + infoLog());
	}
}
GLPP_DECL
void Shader::loadSpirv(uint8_t const* data, int size) noexcept {
	glShaderBinary(1, &mHandle, GL_SPIR_V_BINARY, data, size);
}
GLPP_DECL
void Shader::specialize(const char* entry_point) noexcept {
	glSpecializeShader(mHandle, entry_point, 0, nullptr, nullptr);
	// TODO: check status
}

GLPP_DECL
ShaderType Shader::shaderType() noexcept {
	GLint result;
	glGetShaderiv(mHandle, GL_SHADER_TYPE, &result);
	return static_cast<ShaderType>(result);
}
GLPP_DECL
bool   Shader::deletionStatus() noexcept {
	GLint result;
	glGetShaderiv(mHandle, GL_DELETE_STATUS, &result);
	return result == GL_TRUE;
}
GLPP_DECL
size_t Shader::infoLogLength() noexcept {
	GLint result;
	glGetShaderiv(mHandle, GL_INFO_LOG_LENGTH, &result);
	return result;
}
GLPP_DECL
std::string Shader::infoLog() noexcept {
	std::string result(infoLogLength(), ' ');
	GLint len;
	glGetShaderInfoLog(mHandle, result.size(), &len, result.data());
	result.resize(len);
	return result;
}
GLPP_DECL
size_t Shader::sourceLength() noexcept {
	GLint result;
	glGetShaderiv(mHandle, GL_SHADER_SOURCE_LENGTH, &result);
	return result;
}
GLPP_DECL
std::string Shader::source() noexcept {
	std::string result(infoLogLength(), ' ');
	GLint len;
	glGetShaderSource(mHandle, result.size(), &len, result.data());
	result.resize(len);
	return result;
}
GLPP_DECL
bool   Shader::compileStatus() noexcept {
	GLint result;
	glGetShaderiv(mHandle, GL_COMPILE_STATUS, &result);
	return result == GL_TRUE;
}

GLPP_DECL
void Shader::debugLabel(std::string_view name) {
	glObjectLabel(GL_SHADER, mHandle, name.length(), name.data());
}

} // namespace gl