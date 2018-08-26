#pragma once

namespace gl {

class Sampler {
	unsigned mHandle;
public:
	Sampler() noexcept;
	~Sampler() noexcept;
	// TODO

	Sampler(Sampler&& other) noexcept                 = delete;
	Sampler& operator=(Sampler&& other) noexcept      = delete;
	Sampler(Sampler const& other) noexcept            = delete;
	Sampler& operator=(Sampler const& other) noexcept = delete;
};

} // namespace gl