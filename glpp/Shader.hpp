#pragma once

#include <GL/glew.h>

#include <string_view>


namespace gl {

enum ShaderType : GLenum {
	VERTEX_SHADER          = GL_VERTEX_SHADER,
	FRAGMENT_SHADER        = GL_FRAGMENT_SHADER,
	GEOMETRY_SHADER        = GL_GEOMETRY_SHADER,
	TESS_CONTROL_SHADER    = GL_TESS_CONTROL_SHADER,
	TESS_EVALUATION_SHADER = GL_TESS_EVALUATION_SHADER
};

class Shader {
	unsigned mHandle;
public:
	Shader(ShaderType type) noexcept;
	~Shader() noexcept;

	Shader(Shader&& other) = delete;
	Shader(Shader const& other) = delete;
	Shader& operator=(Shader&& other) = delete;
	Shader& operator=(Shader const& other) = delete;

	// GLSL
	Shader(ShaderType type, char    const* source, int len = -1);
	Shader(ShaderType type, std::string_view source);
	void compileGLSL(char const* data, int size = -1) noexcept;

	// Spirv
	Shader(ShaderType type, uint8_t const* source, int len);
	void loadSpirv(uint8_t const* data, int size) noexcept;
	void specialize(const char* entry_point) noexcept;

	// Parameters
	ShaderType  shaderType() noexcept;
	bool        deletionStatus() noexcept;
	size_t      infoLogLength() noexcept;
	std::string infoLog() noexcept;
	size_t      sourceLength() noexcept;
	std::string source() noexcept;
	bool        compileStatus() noexcept;

	operator unsigned() noexcept { return mHandle; }

	void debugLabel(std::string_view name);
};

inline namespace shaders {

namespace detail {

template<ShaderType kShaderType>
class SomeShader : public Shader {
public:
	inline SomeShader() noexcept : Shader(kShaderType) {}
	// GLSL
	explicit inline SomeShader(char    const* source, int len = -1) noexcept : Shader(kShaderType, source, len) {}
	explicit inline SomeShader(std::string_view source) noexcept : Shader(kShaderType, source) {}
	// Spirv
	explicit inline SomeShader(uint8_t const* source, int len) noexcept : Shader(kShaderType, source, len) {}
};

} // namespace detail

using VertexShader       = detail::SomeShader<VERTEX_SHADER>;
using FragmentShader     = detail::SomeShader<FRAGMENT_SHADER>;
using GeometryShader     = detail::SomeShader<GEOMETRY_SHADER>;
using TessControllShader = detail::SomeShader<TESS_CONTROL_SHADER>;
using TessEvalShader     = detail::SomeShader<TESS_EVALUATION_SHADER>;

} // inline namespace shaders

} // namespace gl
