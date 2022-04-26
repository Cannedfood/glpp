#ifndef GLPP_DECL
	#define GLPP_DECL
#endif

#include <GL/glew.h>
#include <stdexcept>

namespace gl {

GLPP_DECL
void checkError() {
	GLenum error = glGetError();
	if(error != GL_NO_ERROR) {
		throw std::runtime_error((const char*) glewGetErrorString(error));
	}
}

} // namespace gl
