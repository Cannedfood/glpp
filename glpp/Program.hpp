#pragma once

#include <initializer_list>
#include <string>
#include <stdexcept>

#include <GL/glew.h>

#include <glm/fwd.hpp>


namespace gl {

class ValidationError : public std::runtime_error {
public: using std::runtime_error::runtime_error;
};

class LinkerError : public std::runtime_error {
public: using std::runtime_error::runtime_error;
};

class CompilerError : public std::runtime_error {
public: using std::runtime_error::runtime_error;
};

// TODO: incomplete

class Program {
	unsigned mHandle;
public:
	Program() noexcept;
	~Program() noexcept;

	Program(Program&& other) noexcept;
	Program& operator=(Program&& other) noexcept;
	Program(Program const& other) = delete;
	Program& operator=(Program const& other) = delete;

	Program(std::initializer_list<unsigned> shaders);

	void init() noexcept;
	void reset() noexcept;

	void hintBinaryRetrievable(bool b = true) noexcept;
	void separable(bool b = true) noexcept;

	void attach(unsigned shader) noexcept;
	void detach(unsigned shader) noexcept;
	[[nodiscard]] bool link() noexcept;
	void assertLinked() const;

	void attach(std::initializer_list<unsigned> shaders) noexcept;
	void detach(std::initializer_list<unsigned> shaders) noexcept;
	[[nodiscard]] bool link  (std::initializer_list<unsigned> shaders) noexcept;

	bool validate() const noexcept;
	void assertValid() const;

	void use() const noexcept;

	// Uniforms and stuff
	int uniformLocation(const char* name) const noexcept;
	void uniform(int at, float f) noexcept;
	void uniform(int at, glm::vec2 const& v) noexcept;
	void uniform(int at, glm::vec3 const& v) noexcept;
	void uniform(int at, glm::vec4 const& v) noexcept;
	void uniform(int at, glm::mat3x3 const& m) noexcept;
	void uniform(int at, glm::mat4x4 const& m) noexcept;

	template<class Arg0, class... Args>
	void uniform(const char* name, Arg0&& arg0, Args&&... args) {
		if(int u = uniformLocation(name); u >= 0)
			uniform(u, std::forward<Arg0>(arg0), std::forward<Args>(args)...);
	}

	int  uniformBlockIndex(const char* name) noexcept;
	void uniformBlockBinding(unsigned blockIndex, unsigned blockBinding) noexcept;
	void uniformBlockBinding(const char* blockName, unsigned blockBinding) noexcept;

	// Queries (part 1)
	bool        deletionStatus() const noexcept;
	bool        linkStatus() const noexcept;
	bool        validationStatus() const noexcept;
	size_t      infoLogLength() const noexcept;
	std::string infoLog() const noexcept;
	size_t      numAttachedShaders() const noexcept;
	size_t      numActiveAttributes() const noexcept;
	size_t      longestActiveAttribute() const noexcept;
	size_t      numActiveUniforms() const noexcept;

	// Reflection Queries
	int attribLocation(const char* name) const noexcept;

	operator unsigned() noexcept { return mHandle; }

	void debugLabel(std::string_view name) noexcept;
};

} // namespace gl
