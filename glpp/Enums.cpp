#include "Enums.hpp"

#ifndef GLPP_DECL
	#define GLPP_DECL
#endif

namespace gl {

GLPP_DECL
size_t sizeOf(BasicType type) noexcept {
	switch(type) {
	case INT8:    return 1;
	case UINT8:   return 1;
	case FLOAT16: return 2;
	case INT16:   return 2;
	case UINT16:  return 2;
	case FLOAT32: return 3;
	case INT32:   return 3;
	case UINT32:  return 3;
	case FLOAT64: return 4;
	};
}

} // namespace gl
