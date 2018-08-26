#include "Texture.hpp"

#ifndef GLPP_DECL
	#define GLPP_DECL
#endif

namespace gl {

template<TextureType type> GLPP_DECL
Texture<type>::Texture() noexcept {
	init();
}
template<TextureType type> GLPP_DECL
Texture<type>::~Texture() noexcept {
	reset();
}

template<TextureType type> GLPP_DECL
Texture<type>::Texture(Texture&& other) noexcept  :
	mHandle(other.mHandle)
{
	other.mHandle = 0;
}
template<TextureType type> GLPP_DECL
Texture<type>& Texture<type>::operator=(Texture&& other) noexcept {
	reset();
	mHandle = other.mHandle;
	other.mHandle = 0;
	return *this;
}

template<TextureType type> GLPP_DECL
Texture<type>::Texture(std::nullptr_t) noexcept : mHandle(0) {}
template<TextureType type> GLPP_DECL
void Texture<type>::init() noexcept {
	glGenTextures(1, &mHandle);
	bind(); unbind();
}
template<TextureType type> GLPP_DECL
void Texture<type>::reset() noexcept {
	if(mHandle) {
		glDeleteTextures(1, &mHandle);
		mHandle = 0;
	}
}

template<TextureType type> GLPP_DECL
void Texture<type>::bind(TextureType as) noexcept {
	glBindTexture(as, mHandle);
}
template<TextureType type> GLPP_DECL
void Texture<type>::unbind(TextureType from) noexcept {
	glBindTexture(from, 0);
}
template<TextureType type> GLPP_DECL
void Texture<type>::activate(unsigned index, TextureType as) noexcept {
	glActiveTexture(GL_TEXTURE0 + index);
	bind(as);
}

template<TextureType type> GLPP_DECL
void Texture<type>::texSubimage(
	GLsizei level,
	GLsizei xoff, GLsizei width,
	UnsizedImageFormat format, BasicType pxtype, void const* pixels)
{
	glTextureSubImage1D(mHandle, level, xoff, width, format, pxtype, pixels);
}
template<TextureType type> GLPP_DECL
void Texture<type>::texSubimage(
	GLsizei level,
	GLsizei xoff, GLsizei yoff, GLsizei width, GLsizei height,
	UnsizedImageFormat format, BasicType pxtype, void const* pixels)
{
	glTextureSubImage2D(mHandle, level, xoff, yoff, width, height, format, pxtype, pixels);
}
template<TextureType type> GLPP_DECL
void Texture<type>::texSubimage(
	GLsizei level,
	GLsizei xoff, GLsizei yoff, GLsizei zoff, GLsizei width, GLsizei height, GLsizei depth,
	UnsizedImageFormat format, BasicType pxtype, void const* pixels)
{
	glTextureSubImage3D(mHandle, level, xoff, yoff, zoff, width, height, depth, format, pxtype, pixels);
}

template<TextureType type> GLPP_DECL
void Texture<type>::texStorage(GLsizei levels, SizedImageFormat internalFormat, GLsizei width) noexcept {
	glTextureStorage1D(mHandle, levels, internalFormat, width);
}
template<TextureType type> GLPP_DECL
void Texture<type>::texStorage(GLsizei levels, SizedImageFormat internalFormat, GLsizei width, GLsizei height) noexcept {
	glTextureStorage2D(mHandle, levels, internalFormat, width, height);
}
template<TextureType type> GLPP_DECL
void Texture<type>::texStorage(GLsizei levels, SizedImageFormat internalFormat, GLsizei width, GLsizei height, GLsizei depth) noexcept {
	glTextureStorage3D(mHandle, levels, internalFormat, width, height, depth);
}

template<TextureType type> GLPP_DECL
void Texture<type>::bindTextureUnit(unsigned textureUnit) noexcept {
	glBindTextureUnit(textureUnit, mHandle);
}

template<TextureType type> GLPP_DECL
void Texture<type>::generateMipmaps() noexcept {
	glGenerateTextureMipmap(mHandle);
}


template<TextureType type> GLPP_DECL
void Texture<type>::depthToR() noexcept {
	// glTextureParameteri(mHandle, GL_RED_DEPTh) // TODO
}
template<TextureType type> GLPP_DECL
void Texture<type>::stencilToR() noexcept {

}
template<TextureType type> GLPP_DECL
void Texture<type>::baseLevel(unsigned level) noexcept {
	glTextureParameteri(mHandle, GL_TEXTURE_BASE_LEVEL, level);
}
template<TextureType type> GLPP_DECL
void Texture<type>::borderColor(float r, float g, float b, float a) noexcept {
	float rgba[4] = {r, g, b, a};
	glTextureParameterfv(mHandle, GL_TEXTURE_BORDER_COLOR, rgba);
}
template<TextureType type> GLPP_DECL
void Texture<type>::compareFunc(CompareFunc fn) noexcept {
	glTextureParameteri(mHandle, GL_TEXTURE_COMPARE_FUNC, fn);
}
template<TextureType type> GLPP_DECL
void Texture<type>::lodBias(float value) noexcept {
	glTextureParameterf(mHandle, GL_TEXTURE_LOD_BIAS, value);
}
template<TextureType type> GLPP_DECL
void Texture<type>::minFilter(Filter filter) noexcept {
	glTextureParameterf(mHandle, GL_TEXTURE_MIN_FILTER, filter);
}
template<TextureType type> GLPP_DECL
void Texture<type>::magFilter(Filter filter) noexcept {
	glTextureParameterf(mHandle, GL_TEXTURE_MAG_FILTER, filter);
}
template<TextureType type> GLPP_DECL
void Texture<type>::minLod(float level) noexcept {
	glTextureParameterf(mHandle, GL_TEXTURE_MIN_LOD, level);
}
template<TextureType type> GLPP_DECL
void Texture<type>::maxLod(float level) noexcept {
	glTextureParameterf(mHandle, GL_TEXTURE_MAX_LOD, level);
}
template<TextureType type> GLPP_DECL
void Texture<type>::maxLevel(unsigned level) noexcept {
	glTextureParameteri(mHandle, GL_TEXTURE_MAX_LEVEL, level);
}
template<TextureType type> GLPP_DECL
void Texture<type>::swizzle(ColorComponent r, ColorComponent g, ColorComponent b, ColorComponent a) noexcept {
	GLint params[4] = {r, g, b, a};
	glTextureParameteriv(mHandle, GL_TEXTURE_SWIZZLE_RGBA, params);
}
template<TextureType type> GLPP_DECL
void Texture<type>::wrapS(WrapMode wrap) noexcept {
	glTextureParameterf(mHandle, GL_TEXTURE_WRAP_S, wrap);
}
template<TextureType type> GLPP_DECL
void Texture<type>::wrapT(WrapMode wrap) noexcept {
	glTextureParameterf(mHandle, GL_TEXTURE_WRAP_T, wrap);
}
template<TextureType type> GLPP_DECL
void Texture<type>::wrapR(WrapMode wrap) noexcept {
	glTextureParameterf(mHandle, GL_TEXTURE_WRAP_R, wrap);
}
template<TextureType type> GLPP_DECL
void Texture<type>::wrap(WrapMode s, WrapMode t, WrapMode r) noexcept {
	wrapS(s);
	wrapT(t);
	wrapR(r);
}

template class Texture<TEXTURE_1D>;
template class Texture<TEXTURE_2D>;
template class Texture<TEXTURE_3D>;
template class Texture<TEXTURE_1D_ARRAY>;
template class Texture<TEXTURE_2D_ARRAY>;
template class Texture<TEXTURE_RECTANGLE>;
template class Texture<TEXTURE_CUBE_MAP>;
template class Texture<TEXTURE_CUBE_MAP_ARRAY>;
template class Texture<TEXTURE_BUFFER>;
template class Texture<TEXTURE_2D_MULTISAMPLE>;
template class Texture<TEXTURE_2D_MULTISAMPLE_ARRAY>;

} // namespace gl
