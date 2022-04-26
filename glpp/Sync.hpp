#pragma once

#include <GL/glew.h>
#include <cassert>
#include <utility>

namespace gl {

class [[nodiscard]] Sync {
	GLsync mHandle = nullptr;
public:
	void wait      (GLuint64 timeout = GL_TIMEOUT_IGNORED) const noexcept { glWaitSync(mHandle, 0, timeout); }
	bool waitClient(GLuint64 timeout = GL_TIMEOUT_IGNORED) const noexcept { return glClientWaitSync(mHandle, 0, timeout) != GL_TIMEOUT_EXPIRED; }
	bool signaled() const noexcept { return get(GL_SYNC_STATUS) == GL_SIGNALED; }
	GLint get(GLenum name) const noexcept {
		GLint value = GL_UNSIGNALED;
		int length = 0;
		glGetSynciv(mHandle, name, 1, &length, &value);
		assert(length == 1);
		return value;
	}


	Sync() noexcept = default;
	explicit Sync(GLsync handle) noexcept : mHandle(handle) {}
	~Sync() { reset(); }

	Sync(Sync&& other) noexcept : Sync(other.release()) {}
	Sync& operator=(Sync&& other) noexcept { reset(other.release()); return *this; }

	GLsync release() noexcept { return std::exchange(mHandle, nullptr); }

	void reset(GLsync handle = nullptr) noexcept {
		if(mHandle != nullptr) {
			glDeleteSync(mHandle);
		}
		mHandle = handle;
	}

	operator GLsync() const noexcept { return mHandle; }
};

inline Sync fence() noexcept {
	return Sync(glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, 0));
}

} // namespace gl
