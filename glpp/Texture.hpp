#pragma once

#include "Enums.hpp"

#include <GL/glew.h>

#include <cstddef>
#include <string_view>

#include <array>

namespace gl {

enum TextureType {
	TEXTURE_1D                   = GL_TEXTURE_1D,
	TEXTURE_2D                   = GL_TEXTURE_2D,
	TEXTURE_3D                   = GL_TEXTURE_3D,
	TEXTURE_1D_ARRAY             = GL_TEXTURE_1D_ARRAY,
	TEXTURE_2D_ARRAY             = GL_TEXTURE_2D_ARRAY,
	TEXTURE_RECTANGLE            = GL_TEXTURE_RECTANGLE,
	TEXTURE_CUBE_MAP             = GL_TEXTURE_CUBE_MAP,
	TEXTURE_CUBE_MAP_ARRAY       = GL_TEXTURE_CUBE_MAP_ARRAY,
	TEXTURE_BUFFER               = GL_TEXTURE_BUFFER,
	TEXTURE_2D_MULTISAMPLE       = GL_TEXTURE_2D_MULTISAMPLE,
	TEXTURE_2D_MULTISAMPLE_ARRAY = GL_TEXTURE_2D_MULTISAMPLE_ARRAY
};

enum SizedImageFormat : GLenum {
	R8 = GL_R8,
	R8_SNORM = GL_R8_SNORM,
	R16 = GL_R16,
	R16_SNORM = GL_R16_SNORM,
	RG8 = GL_RG8,
	RG8_SNORM = GL_RG8_SNORM,
	RG16 = GL_RG16,
	RG16_SNORM = GL_RG16_SNORM,
	R3_G3_B2 = GL_R3_G3_B2,
	RGB4 = GL_RGB4,
	RGB5 = GL_RGB5,
	RGB8 = GL_RGB8,
	RGB8_SNORM = GL_RGB8_SNORM,
	RGB10 = GL_RGB10,
	RGB12 = GL_RGB12,
	RGB16 = GL_RGB16,
	RGB16_SNORM = GL_RGB16_SNORM,
	RGBA2 = GL_RGBA2,
	RGBA4 = GL_RGBA4,
	RGB5_A1 = GL_RGB5_A1,
	RGBA8 = GL_RGBA8,
	RGBA8_SNORM = GL_RGBA8_SNORM,
	RGB10_A2 = GL_RGB10_A2, RGB10_A2UI = GL_RGB10_A2UI,
	RGBA12 = GL_RGBA12, RGBA16 = GL_RGBA16,
	SRGB8 = GL_SRGB8, SRGB8_ALPHA8 = GL_SRGB8_ALPHA8,
	R16F = GL_R16F, RG16F = GL_RG16F, RGB16F = GL_RGB16F, RGBA16F = GL_RGBA16F,
	R32F = GL_R32F, RG32F = GL_RG32F, RGB32F = GL_RGB32F, RGBA32F = GL_RGBA32F,
	R11F_G11F_B10F = GL_R11F_G11F_B10F, RGB9_E5 = GL_RGB9_E5,
	R8I = GL_R8I, R8UI = GL_R8UI, R16I = GL_R16I, R16UI = GL_R16UI, R32I = GL_R32I, R32UI = GL_R32UI,
	RG8I = GL_RG8I, RG8UI = GL_RG8UI, RG16I = GL_RG16I, RG16UI = GL_RG16UI, RG32I = GL_RG32I, RG32UI = GL_RG32UI,
	RGB8I = GL_RGB8I, RGB8UI = GL_RGB8UI, RGB16I = GL_RGB16I, RGB16UI = GL_RGB16UI, RGB32I = GL_RGB32I, RGB32UI = GL_RGB32UI,
	RGBA8I = GL_RGBA8I, RGBA8UI = GL_RGBA8UI, RGBA16I = GL_RGBA16I, RGBA16UI = GL_RGBA16UI, RGBA32I = GL_RGBA32I, RGBA32UI = GL_RGBA32UI,

	DEPTH16 = GL_DEPTH_COMPONENT16, DEPTH24 = GL_DEPTH_COMPONENT24, DEPTH32 = GL_DEPTH_COMPONENT32, DEPTH32F = GL_DEPTH_COMPONENT32F,
	DEPTH24_STENCIL8  = GL_DEPTH24_STENCIL8, DEPTH32F_STENCIL8 = GL_DEPTH32F_STENCIL8,
};

enum UnsizedImageFormat {
	R    = GL_RED,
	RG   = GL_RG,
	RGB  = GL_RGB,
	RGBA = GL_RGBA,
	BGR  = GL_BGR,
	BGRA = GL_BGRA,
	DEPTH = GL_DEPTH_COMPONENT
};

enum CompressedImageFormat {
	COMPRESSED_RGB_S3TC_DXT1        = GL_COMPRESSED_RGB_S3TC_DXT1_EXT,
	COMPRESSED_SRGB_S3TC_DXT1       = GL_COMPRESSED_SRGB_S3TC_DXT1_EXT,
	COMPRESSED_RGBA_S3TC_DXT1       = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT,
	COMPRESSED_SRGB_ALPHA_S3TC_DXT1 = GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1_EXT,
	COMPRESSED_RGBA_S3TC_DXT3       = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT,
	COMPRESSED_SRGB_ALPHA_S3TC_DXT3 = GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT3_EXT,
	COMPRESSED_RGBA_S3TC_DXT5       = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT,
	COMPRESSED_SRGB_ALPHA_S3TC_DXT5 = GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT5_EXT
};

enum WrapMode {
	CLAMP = GL_CLAMP,
	CLAMP_TO_EDGE   = GL_CLAMP_TO_EDGE,
	CLAMP_TO_BORDER = GL_CLAMP_TO_BORDER,
	WRAP  = GL_REPEAT,
	MIRROR = GL_MIRRORED_REPEAT,
};

enum Filter {
	LINEAR                 = GL_LINEAR,
	NEAREST                = GL_NEAREST,
	TRILINEAR              = GL_LINEAR_MIPMAP_LINEAR,
	LINEAR_MIPMAP_LINEAR   = GL_LINEAR_MIPMAP_LINEAR,
	LINEAR_MIPMAP_NEAREST  = GL_LINEAR_MIPMAP_NEAREST,
	NEAREST_MIPMAP_LINEAR  = GL_NEAREST_MIPMAP_LINEAR,
	NEAREST_MIPMAP_NEAREST = GL_NEAREST_MIPMAP_NEAREST,
};

enum CompareFunc {
	LESS_EQUAL,
	GREATER_EQUAL,
	LESS,
	GREATER,
	EQUAL,
	NOTEQUAL,
	ALWAYS,
	NEVER
};

enum ColorComponent {
	ONE   = GL_ONE,
	ZERO  = GL_ZERO,
	RED   = GL_RED,
	GREEN = GL_GREEN,
	BLUE  = GL_BLUE,
	ALPHA = GL_ALPHA,
};

enum CubemapFace {
	CUBEMAP_POSITIVE_X = GL_TEXTURE_CUBE_MAP_POSITIVE_X,
	CUBEMAP_NEGATIVE_X = GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
	CUBEMAP_POSITIVE_Y = GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
	CUBEMAP_NEGATIVE_Y = GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
	CUBEMAP_POSITIVE_Z = GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
	CUBEMAP_NEGATIVE_Z = GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,
};
constexpr std::array<CubemapFace, 6> cubemapFaces() noexcept {
	return { CUBEMAP_POSITIVE_X, CUBEMAP_NEGATIVE_X, CUBEMAP_POSITIVE_Y, CUBEMAP_NEGATIVE_Y, CUBEMAP_POSITIVE_Z, CUBEMAP_NEGATIVE_Z };
}

template<TextureType tType>
class BasicTextureView {
protected:
	unsigned mHandle;
public:
	BasicTextureView(unsigned handle = 0) noexcept : mHandle(handle) {}

	constexpr inline static const
	TextureType type = tType;

	// TODO: incomplete

	void bind(TextureType as = type) noexcept;
	static void unbind(TextureType from = type) noexcept;
	void activate(unsigned index, TextureType as = type) noexcept;

	void texImage(
		GLint level,
		SizedImageFormat internalFormat,
		GLsizei w,
		UnsizedImageFormat fmt, gl::BasicType type,
		const void* data = nullptr);
	void texImage(
		GLint level,
		SizedImageFormat internalFormat,
		GLsizei w, GLsizei h,
		UnsizedImageFormat fmt, gl::BasicType type,
		const void* data = nullptr);
	void texImage(
		CubemapFace cubemapFace,
		GLint level,
		SizedImageFormat internalFormat,
		GLsizei w, GLsizei h,
		UnsizedImageFormat fmt, gl::BasicType type,
		const void* data = nullptr);
	void texImage(
		GLint level,
		SizedImageFormat internalFormat,
		GLsizei w, GLsizei h, GLsizei d,
		UnsizedImageFormat fmt, gl::BasicType type,
		const void* data = nullptr);

	void compressedTexImage(
		GLint level,
		CompressedImageFormat format,
		GLsizei w,
		unsigned dataSize,
		const void* data = nullptr);
	void compressedTexImage(
		GLint level,
		CompressedImageFormat format,
		GLsizei w, GLsizei h,
		unsigned dataSize,
		const void* data = nullptr);
	void compressedTexImage(
		GLint level,
		CompressedImageFormat format,
		GLsizei w, GLsizei h, GLsizei d,
		unsigned dataSize,
		const void* data = nullptr);

	void texSubimage(
		GLsizei level,
		GLsizei xoff, GLsizei width,
		UnsizedImageFormat format, BasicType pxtype, void const* pixels);
	void texSubimage(
		GLsizei level,
		GLsizei xoff, GLsizei yoff, GLsizei width, GLsizei height,
		UnsizedImageFormat format, BasicType pxtype, void const* pixels);
	void texSubimage(
		GLsizei level,
		GLsizei xoff, GLsizei yoff, GLsizei zoff, GLsizei width, GLsizei height, GLsizei depth,
		UnsizedImageFormat format, BasicType pxtype, void const* pixels);

	void texStorage(GLsizei levels, SizedImageFormat internalFormat, GLsizei width) noexcept;
	void texStorage(GLsizei levels, SizedImageFormat internalFormat, GLsizei width, GLsizei height) noexcept;
	void texStorage(GLsizei levels, SizedImageFormat internalFormat, GLsizei width, GLsizei height, GLsizei depth) noexcept;

	void bindTextureUnit(unsigned textureUnit) noexcept; // sampler in glsl
	// void bindImageUnit(unsigned textureUnit) noexcept; // image in glsl

	void generateMipmaps() noexcept;

	// Properties
	void depthToR() noexcept;
	void stencilToR() noexcept;
	void baseLevel(unsigned level) noexcept;
	void borderColor(float r, float g, float b, float a) noexcept;
	void compareFunc(CompareFunc) noexcept;
	// void compareMode() noexcept; TODO
	void lodBias(float value) noexcept;
	void minFilter(Filter) noexcept;
	void magFilter(Filter) noexcept;
	void filter(Filter minFilter, Filter magFilter) noexcept { this->minFilter(minFilter); this->magFilter(magFilter); }
	void minLod(float level) noexcept;
	void maxLod(float level) noexcept;
	void maxLevel(unsigned level) noexcept;
	void swizzle(ColorComponent r, ColorComponent g, ColorComponent b, ColorComponent a) noexcept;
	void wrapS(WrapMode) noexcept;
	void wrapT(WrapMode) noexcept;
	void wrapR(WrapMode) noexcept;
	void wrap(WrapMode s, WrapMode t = CLAMP, WrapMode r = CLAMP) noexcept;
	float maxAnisotropy() noexcept;
	void  maxAnisotropy(float f) noexcept;

	void debugLabel(std::string_view name) noexcept;

	operator unsigned() noexcept { return mHandle; }
};

template<TextureType tType>
class BasicTexture : public BasicTextureView<tType> {
public:
	BasicTexture() noexcept;
	~BasicTexture() noexcept;

	BasicTexture(std::nullptr_t) noexcept;

	BasicTexture(BasicTexture&& other) noexcept;
	BasicTexture& operator=(BasicTexture&& other) noexcept;
	BasicTexture(BasicTexture const& other) noexcept            = delete;
	BasicTexture& operator=(BasicTexture const& other) noexcept = delete;

	void init() noexcept;
	void destroy() noexcept;
};

inline namespace texture_types {

using TextureView1D                 = BasicTextureView<TEXTURE_1D>;
using TextureView1DArray            = BasicTextureView<TEXTURE_1D_ARRAY>;

using TextureView2D                 = BasicTextureView<TEXTURE_2D>;
using TextureView2DArray            = BasicTextureView<TEXTURE_2D_ARRAY>;
using TextureView2DMultisample      = BasicTextureView<TEXTURE_2D_MULTISAMPLE>;
using TextureView2DMultisampleArray = BasicTextureView<TEXTURE_2D_MULTISAMPLE_ARRAY>;

using TextureView3D                 = BasicTextureView<TEXTURE_3D>;

using TextureViewRectangle          = BasicTextureView<TEXTURE_RECTANGLE>;

using TextureViewCubemap            = BasicTextureView<TEXTURE_CUBE_MAP>;
using TextureViewCubemapArray       = BasicTextureView<TEXTURE_CUBE_MAP_ARRAY>;



using Texture1D                 = BasicTexture<TEXTURE_1D>;
using Texture1DArray            = BasicTexture<TEXTURE_1D_ARRAY>;

using Texture2D                 = BasicTexture<TEXTURE_2D>;
using Texture2DArray            = BasicTexture<TEXTURE_2D_ARRAY>;
using Texture2DMultisample      = BasicTexture<TEXTURE_2D_MULTISAMPLE>;
using Texture2DMultisampleArray = BasicTexture<TEXTURE_2D_MULTISAMPLE_ARRAY>;

using Texture3D                 = BasicTexture<TEXTURE_3D>;

using TextureRectangle          = BasicTexture<TEXTURE_RECTANGLE>;

using TextureCubemap            = BasicTexture<TEXTURE_CUBE_MAP>;
using TextureCubemapArray       = BasicTexture<TEXTURE_CUBE_MAP_ARRAY>;

// using TextureBuffer             = Texture<TEXTURE_BUFFER>; TODO: buffer textures

} // inline namespace textures

} // namespace gl
