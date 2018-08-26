#include "Sampler.hpp"

#include <GL/glew.h>

#ifndef GLPP_DECL
	#define GLPP_DECL
#endif

namespace gl {

GLPP_DECL
Sampler::Sampler() noexcept {
	glGenSamplers(1, &mHandle);
}
GLPP_DECL
Sampler::~Sampler() noexcept {
	glDeleteSamplers(1, &mHandle);
}



} // namespace gl