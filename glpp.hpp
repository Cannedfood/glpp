#pragma once

#include <GL/glew.h>

#ifndef GLPP_NO_INLINE

	#define GLPP_INLINE
	#define GLPP_DECL inline

#endif

#include "glpp/Buffer.hpp"
#include "glpp/Debug.hpp"
#include "glpp/Drawing.hpp"
#include "glpp/Enums.hpp"
#include "glpp/Framebuffer.hpp"
#include "glpp/Pipeline.hpp"
#include "glpp/Program.hpp"
#include "glpp/Sampler.hpp"
#include "glpp/Shader.hpp"
#include "glpp/State.hpp"
#include "glpp/Texture.hpp"
#include "glpp/VertexArray.hpp"


#ifndef GLPP_NO_INLINE

	#include "glpp/Buffer.cpp"
	#include "glpp/Framebuffer.cpp"
	#include "glpp/Program.cpp"
	#include "glpp/Sampler.cpp"
	#include "glpp/Shader.cpp"
	#include "glpp/Texture.cpp"
	#include "glpp/VertexArray.cpp"

#endif // (GLPP_NO_INLINE)
