#pragma once

namespace gl {

// TODO

class Pipeline {
	unsigned mHandle;
public:
	Pipeline() noexcept;
	~Pipeline() noexcept;

	Pipeline(Pipeline&& other) noexcept                 = delete;
	Pipeline& operator=(Pipeline&& other) noexcept      = delete;
	Pipeline(Pipeline const& other) noexcept            = delete;
	Pipeline& operator=(Pipeline const& other) noexcept = delete;
};

} // namespace gl