#pragma once

#include "./glpp/Shader.hpp"
#include "./glpp/Program.hpp"

#include <fstream>

namespace gl {

inline std::string LoadFile(std::string path) {
	std::ifstream file(path, std::ios::binary | std::ios::ate);
	if(!file)
		throw std::runtime_error("Failed opening file " + path);

	std::string result;
	result.resize(file.tellg());
	file.seekg(0, std::ios::beg);
	file.read(result.data(), result.size());
	return result;
}

inline gl::ShaderType GuessShaderType(std::string_view path) {
	if(path.ends_with(".fs") || path.ends_with(".frag") || path.ends_with(".frag.glsl"))
		return gl::FRAGMENT_SHADER;
	if(path.ends_with(".vs") || path.ends_with(".vert") || path.ends_with(".vert.glsl"))
		return gl::VERTEX_SHADER;
	if(path.ends_with(".gs") || path.ends_with(".geom") || path.ends_with(".geom.glsl"))
		return gl::GEOMETRY_SHADER;
	if(path.ends_with(".tc") || path.ends_with(".tessc") || path.ends_with(".tessc.glsl"))
		return gl::TESS_CONTROL_SHADER;
	if(path.ends_with(".te") || path.ends_with(".tesse") || path.ends_with(".tesse.glsl"))
		return gl::TESS_EVALUATION_SHADER;
	if(path.ends_with(".cs") || path.ends_with(".comp") || path.ends_with(".comp.glsl"))
		return gl::COMPUTE_SHADER;
	throw std::runtime_error("Couldn't guess shader type based on file path for " + std::string(path));
}

inline gl::Shader LoadShader(std::string path, gl::ShaderType type) {
	return gl::Shader(type, LoadFile(path));
}

inline gl::Shader LoadShader(std::string path) {
	return LoadShader(path, GuessShaderType(path));
}

} // namespace gl
