#pragma once

#include <GL/glew.h>

#include <string_view>


namespace gl {

enum ShaderType : GLenum {
	VERTEX_SHADER          = GL_VERTEX_SHADER,
	FRAGMENT_SHADER        = GL_FRAGMENT_SHADER,
	GEOMETRY_SHADER        = GL_GEOMETRY_SHADER,
	TESS_CONTROL_SHADER    = GL_TESS_CONTROL_SHADER,
	TESS_EVALUATION_SHADER = GL_TESS_EVALUATION_SHADER,
	COMPUTE_SHADER         = GL_COMPUTE_SHADER
};

std::string_view to_string(ShaderType type) noexcept;

/// A single stage of a shader Program.
/// Needs to be linked into a Program, after which it can be destroyed.
class Shader {
	unsigned mHandle;
public:
	Shader(std::nullptr_t) noexcept;
	Shader(ShaderType type) noexcept;
	~Shader() noexcept;

	Shader(Shader&& other) noexcept;
	Shader& operator=(Shader&& other) noexcept;
	Shader(Shader const& other) = delete;
	Shader& operator=(Shader const& other) = delete;

	void init(ShaderType type) noexcept;
	void reset() noexcept;

	// GLSL
	Shader(ShaderType type, unsigned sourceCount, char const* const* sources, int const* lengths = nullptr);
	Shader(ShaderType type, char const* source, int len = -1);
	Shader(ShaderType type, std::string_view source);
	Shader(ShaderType type, std::initializer_list<std::string_view> sources);
	[[nodiscard]] bool compileGLSL(unsigned sourceCount, char const* const* sources, int const* lengths = nullptr) noexcept;

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

namespace shader_detail {

template<ShaderType kShaderType>
class TypedShader : public Shader {
public:
	inline TypedShader() noexcept : Shader(kShaderType) {}
	// GLSL
	explicit inline TypedShader(char    const* source, int len = -1) : Shader(kShaderType, source, len) {}
	explicit inline TypedShader(std::string_view source) : Shader(kShaderType, source) {}
	explicit inline TypedShader(std::initializer_list<std::string_view> sources) : Shader(kShaderType, sources) {}
	// Spirv
	explicit inline TypedShader(uint8_t const* source, int len) noexcept : Shader(kShaderType, source, len) {}
};

} // namespace detail

using VertexShader       = shader_detail::TypedShader<VERTEX_SHADER>;
using FragmentShader     = shader_detail::TypedShader<FRAGMENT_SHADER>;
using GeometryShader     = shader_detail::TypedShader<GEOMETRY_SHADER>;
using TessControllShader = shader_detail::TypedShader<TESS_CONTROL_SHADER>;
using TessEvalShader     = shader_detail::TypedShader<TESS_EVALUATION_SHADER>;

} // inline namespace shaders

} // namespace gl
