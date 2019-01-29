#include "Program.hpp"

#include <algorithm>

#ifndef GLPP_DECL
	#define GLPP_DECL
#endif

namespace gl {

GLPP_DECL
Program::Program() noexcept :
	mHandle(0)
{
	init();
}
GLPP_DECL
Program::~Program() noexcept {
	reset();
}

GLPP_DECL
Program::Program(std::initializer_list<unsigned> shaders) noexcept :
	Program()
{
	link(shaders);
}

Program::Program(Program&& other) noexcept :
	mHandle(other.mHandle)
{
	other.mHandle = 0;
}
Program& Program::operator=(Program&& other) noexcept {
	reset();
	mHandle = std::exchange(other.mHandle, 0);
	return *this;
}

GLPP_DECL
void Program::init() noexcept {
	reset();
	mHandle = glCreateProgram();
}

GLPP_DECL
void Program::reset() noexcept {
	if(mHandle) {
		glDeleteProgram(mHandle);
		mHandle = 0;
	}
}

GLPP_DECL
void Program::hintBinaryRetrievable(bool b) noexcept {
	glProgramParameteri(mHandle, GL_PROGRAM_BINARY_RETRIEVABLE_HINT, b ? GL_TRUE : GL_FALSE);
}
GLPP_DECL
void Program::separable(bool b) noexcept {
	glProgramParameteri(mHandle, GL_PROGRAM_SEPARABLE, b ? GL_TRUE : GL_FALSE);
}

GLPP_DECL
void Program::attach(unsigned shader) noexcept {
	glAttachShader(mHandle, shader);
}
GLPP_DECL
void Program::detach(unsigned shader) noexcept {
	glDetachShader(mHandle, shader);
}
GLPP_DECL
bool Program::link() noexcept {
	glLinkProgram(mHandle);
	return linkStatus();
}

GLPP_DECL
void Program::attach(std::initializer_list<unsigned> shaders) noexcept {
	for(auto& shader : shaders)
		glAttachShader(mHandle, shader);
}
GLPP_DECL
void Program::detach(std::initializer_list<unsigned> shaders) noexcept {
	for(auto& shader : shaders)
		glDetachShader(mHandle, shader);
}
GLPP_DECL
bool Program::link(std::initializer_list<unsigned> shaders) noexcept {
	attach(shaders);
	bool success = link();
	detach(shaders);
	return success;
}

GLPP_DECL
bool Program::validate() const noexcept {
	glValidateProgram(mHandle);
	return validationStatus();
}

GLPP_DECL
void Program::assertValid() const {
	if(!validate()) throw ValidationError(infoLog());
}

GLPP_DECL
void Program::use() const noexcept {
	glUseProgram(mHandle);
}

GLPP_DECL
int Program::uniformLocation(const char* name) const noexcept {
	return glGetUniformLocation(mHandle, name);
}
GLPP_DECL
void Program::uniform(int at, float f) noexcept {
	glUniform1f(at, f);
}
GLPP_DECL
void Program::uniform(int at, glm::vec2 const& v) noexcept {
	glUniform2fv(at, 1, &((float&)v));
}
GLPP_DECL
void Program::uniform(int at, glm::vec3 const& v) noexcept {
	glUniform3fv(at, 1, &((float&)v));
}
GLPP_DECL
void Program::uniform(int at, glm::vec4 const& v) noexcept {
	glUniform4fv(at, 1, &((float&)v));
}
GLPP_DECL
void Program::uniform(int at, glm::mat3x3 const& m) noexcept {
	glUniformMatrix3fv(at, 1, GL_FALSE, &((float&)m));
}
GLPP_DECL
void Program::uniform(int at, glm::mat4x4 const& m) noexcept {
	glUniformMatrix4fv(at, 1, GL_FALSE, &((float&)m));
}

GLPP_DECL
int Program::uniformBlockIndex(const char* name) noexcept {
	return glGetUniformBlockIndex(mHandle, name);
}
GLPP_DECL
void Program::uniformBlockBinding(unsigned blockIndex, unsigned blockBinding) noexcept {
	glUniformBlockBinding(mHandle, blockIndex, blockBinding);
}
GLPP_DECL
void Program::uniformBlockBinding(const char* blockName, unsigned blockBinding) noexcept {
	if(int index = uniformBlockIndex(blockName); index >= 0) {
		uniformBlockBinding(index, blockBinding);
	}
}

GLPP_DECL
bool Program::deletionStatus() const noexcept {
	GLint result;
	glGetProgramiv(mHandle, GL_DELETE_STATUS, &result);
	return result == GL_TRUE;
}
GLPP_DECL
bool Program::linkStatus() const noexcept {
	GLint result;
	glGetProgramiv(mHandle, GL_LINK_STATUS, &result);
	return result == GL_TRUE;
}
GLPP_DECL
bool Program::validationStatus() const noexcept {
	GLint result;
	glGetProgramiv(mHandle, GL_VALIDATE_STATUS, &result);
	return result == GL_TRUE;
}
GLPP_DECL
size_t Program::infoLogLength() const noexcept {
	GLint result;
	glGetProgramiv(mHandle, GL_INFO_LOG_LENGTH, &result);
	return result;
}
GLPP_DECL
std::string Program::infoLog() const noexcept {
	std::string result(infoLogLength(), ' ');
	GLint len;
	glGetShaderInfoLog(mHandle, result.size(), &len, result.data());
	result.resize(len);
	return result;
}
GLPP_DECL
size_t Program::numAttachedShaders() const noexcept {
	GLint result;
	glGetProgramiv(mHandle, GL_ATTACHED_SHADERS, &result);
	return result;
}
GLPP_DECL
size_t Program::numActiveAttributes() const noexcept {
	GLint result;
	glGetProgramiv(mHandle, GL_ATTACHED_SHADERS, &result);
	return result;
}
GLPP_DECL
size_t Program::longestActiveAttribute() const noexcept {
	GLint result;
	glGetProgramiv(mHandle, GL_ACTIVE_UNIFORM_MAX_LENGTH, &result);
	return result;
}
GLPP_DECL
size_t Program::numActiveUniforms() const noexcept {
	GLint result;
	glGetProgramiv(mHandle, GL_ACTIVE_UNIFORMS, &result);
	return result;
}

GLPP_DECL
int Program::attribLocation(const char* name) const noexcept {
	return glGetAttribLocation(mHandle, name);
}

/*
GLint numBlocks = 0;
glGetProgramInterfaceiv(prog, GL_UNIFORM_BLOCK, GL_ACTIVE_RESOURCES, &numBlocks);
const GLenum blockProperties[1] = {GL_NUM_ACTIVE_VARIABLES};
const GLenum activeUnifProp[1] = {GL_ACTIVE_VARIABLES};
const GLenum unifProperties[3] = {GL_NAME_LENGTH​, GL_TYPE​, GL_LOCATION};

for(int blockIx = 0; blockIx < numBlocks; ++blockIx)
{
  GLint numActiveUnifs = 0;
  glGetProgramResourceiv(prog, GL_UNIFORM_BLOCK, blockIx, 1, blockProperties, 1, NULL, numActiveUnifs);

  if(!numActiveUnifs)
    continue;

  std::vector<GLint> blockUnifs(numActiveUnifs);
  glGetProgramResourceiv(prog, GL_UNIFORM_BLOCK, blockIx, 1, activeUnifProp, numActiveUnifs, NULL, &blockUnifs[0]);

  for(int unifIx = 0; unifIx < numActiveUnifs; ++unifIx)
  {
    GLint values[3];
    glGetProgramResourceiv(prog, GL_UNIFORM, blockUnifs[unifIx], 3, unifProperties, 3, NULL, values);

    // Get the name. Must use a std::vector rather than a std::string for C++03 standards issues.
    // C++11 would let you use a std::string directly.
    std::vector<char> nameData(values[0]);
    glGetProgramResourceName(prog, GL_UNIFORM, blockUnifs[unifIx], nameData.size(), NULL, &nameData[0]);
    std::string name(nameData.begin(), nameData.end() - 1);
  }
}
*/

GLPP_DECL
void Program::debugLabel(std::string_view name) noexcept {
	glObjectLabel(GL_PROGRAM, mHandle, name.length(), name.data());
}

} // namespace gl
