# GLpp - A very thin abstraction over modern opengl

A C++20 header only library providing abstractions of OpenGL.
The library uses bindless versions of a function wherever possible, because it maps better to the C++ programming model. (Hence OpenGL 4.5+)

## Usage Example
```
#include <cstdlib>

#include <glpp.hpp>
#include <glpp-io-util.hpp> // For gl::LoadShader

int main() {
	// ...create window
	// ...init GLEW

	gl::Program program {
		gl::LoadShader("./example.frag"),
		gl::LoadShader("./example.vert"),
	};
	program.assertLinked();
	program.assertValid();

	gl::ArrayBuffer mesh;

	return EXIT_SUCCESS;
}
```


## Compiler Options
- `GLPP_NO_INLINE`: If you don't want to use this library as a header-only library


## License: Public Domain (via. Unlicense)

This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.

In jurisdictions that recognize copyright laws, the author or authors
of this software dedicate any and all copyright interest in the
software to the public domain. We make this dedication for the benefit
of the public at large and to the detriment of our heirs and
successors. We intend this dedication to be an overt act of
relinquishment in perpetuity of all present and future rights to this
software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

For more information, please refer to <https://unlicense.org>
