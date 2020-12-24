#include "Texture.hpp"

#ifndef GLPP_DECL
	#define GLPP_DECL
#endif

namespace gl {

template<TextureType type> GLPP_DECL
BasicTexture<type>::BasicTexture() noexcept {
	init();
}
template<TextureType type> GLPP_DECL
BasicTexture<type>::~BasicTexture() noexcept {
	reset();
}

template<TextureType type> GLPP_DECL
BasicTexture<type>::BasicTexture(BasicTexture&& other) noexcept  :
	BasicTextureView<type>(other.mHandle)
{
	other.mHandle = 0;
}
template<TextureType type> GLPP_DECL
BasicTexture<type>& BasicTexture<type>::operator=(BasicTexture&& other) noexcept {
	reset();
	this->mHandle = other.mHandle;
	other.mHandle = 0;
	return *this;
}

template<TextureType type> GLPP_DECL
BasicTexture<type>::BasicTexture(std::nullptr_t) noexcept : BasicTextureView<type>(0) {}
template<TextureType type> GLPP_DECL
void BasicTexture<type>::init() noexcept {
	glGenTextures(1, &this->mHandle);
	this->bind();
	this->unbind();
}
template<TextureType type> GLPP_DECL
void BasicTexture<type>::reset() noexcept {
	if(this->mHandle) {
		glDeleteTextures(1, &this->mHandle);
		this->mHandle = 0;
	}
}

template<TextureType type> GLPP_DECL
void BasicTextureView<type>::bind(TextureType as) noexcept {
	glBindTexture(as, mHandle);
}
template<TextureType type> GLPP_DECL
void BasicTextureView<type>::unbind(TextureType from) noexcept {
	glBindTexture(from, 0);
}
template<TextureType type> GLPP_DECL
void BasicTextureView<type>::activate(unsigned index, TextureType as) noexcept {
	glActiveTexture(GL_TEXTURE0 + index);
	bind(as);
}
template<TextureType type> GLPP_DECL
void BasicTextureView<type>::texImage(
	GLint level,
	SizedImageFormat internalFormat,
	GLsizei w,
	gl::UnsizedImageFormat fmt, gl::BasicType dataType,
	const void* data)
{
	glBindTexture(type, *this);
	glTexImage1D(type, level, internalFormat, w, 0, fmt, dataType, data);
}
template<TextureType type> GLPP_DECL
void BasicTextureView<type>::texImage(
	GLint level,
	SizedImageFormat internalFormat,
	GLsizei w, GLsizei h,
	gl::UnsizedImageFormat fmt, gl::BasicType dataType,
	const void* data)
{
	glBindTexture(type, *this);
	glTexImage2D(type, level, internalFormat, w, h, 0, fmt, dataType, data);
}
template<TextureType type> GLPP_DECL
void BasicTextureView<type>::texImage(
	CubemapFace cubemapFaceIndex,
	GLint level,
	SizedImageFormat internalFormat,
	GLsizei w, GLsizei h,
	UnsizedImageFormat fmt, gl::BasicType dataType,
	const void* data)
{
	glBindTexture(type, *this);
	glTexImage2D(cubemapFaceIndex, level, internalFormat, w, h, 0, fmt, dataType, data);
}
template<TextureType type> GLPP_DECL
void BasicTextureView<type>::texImage(
	GLint level,
	SizedImageFormat internalFormat,
	GLsizei w, GLsizei h, GLsizei d,
	gl::UnsizedImageFormat fmt, gl::BasicType dataType,
	const void* data)
{
	glBindTexture(type, *this);
	glTexImage3D(type, level, internalFormat, w, h, d, 0, fmt, dataType, data);
}

template<TextureType type> GLPP_DECL
void BasicTextureView<type>::compressedTexImage(
	GLint level,
	CompressedImageFormat format,
	GLsizei w,
	unsigned dataSize,
	const void* data)
{
	glBindTexture(type, *this);
	glCompressedTexImage1D(type, level, format, w, 0, dataSize, data);
}
template<TextureType type> GLPP_DECL
void BasicTextureView<type>::compressedTexImage(
	GLint level,
	CompressedImageFormat format,
	GLsizei w, GLsizei h,
	unsigned dataSize,
	const void* data)
{
	glBindTexture(type, *this);
	glCompressedTexImage2D(type, level, format, w, h, 0, dataSize, data);
}
template<TextureType type> GLPP_DECL
void BasicTextureView<type>::compressedTexImage(
	GLint level,
	CompressedImageFormat format,
	GLsizei w, GLsizei h, GLsizei d,
	unsigned dataSize,
	const void* data)
{
	glBindTexture(type, *this);
	glCompressedTexImage3D(type, level, format, w, h, d, 0, dataSize, data);
}

template<TextureType type> GLPP_DECL
void BasicTextureView<type>::texSubimage(
	GLsizei level,
	GLsizei xoff, GLsizei width,
	UnsizedImageFormat format, BasicType pxtype, void const* pixels)
{
	glTextureSubImage1D(mHandle, level, xoff, width, format, pxtype, pixels);
}
template<TextureType type> GLPP_DECL
void BasicTextureView<type>::texSubimage(
	GLsizei level,
	GLsizei xoff, GLsizei yoff, GLsizei width, GLsizei height,
	UnsizedImageFormat format, BasicType pxtype, void const* pixels)
{
	glTextureSubImage2D(mHandle, level, xoff, yoff, width, height, format, pxtype, pixels);
}
template<TextureType type> GLPP_DECL
void BasicTextureView<type>::texSubimage(
	GLsizei level,
	GLsizei xoff, GLsizei yoff, GLsizei zoff, GLsizei width, GLsizei height, GLsizei depth,
	UnsizedImageFormat format, BasicType pxtype, void const* pixels)
{
	glTextureSubImage3D(mHandle, level, xoff, yoff, zoff, width, height, depth, format, pxtype, pixels);
}

template<TextureType type> GLPP_DECL
void BasicTextureView<type>::texStorage(GLsizei levels, SizedImageFormat internalFormat, GLsizei width) noexcept {
	glTextureStorage1D(mHandle, levels, internalFormat, width);
}
template<TextureType type> GLPP_DECL
void BasicTextureView<type>::texStorage(GLsizei levels, SizedImageFormat internalFormat, GLsizei width, GLsizei height) noexcept {
	glTextureStorage2D(mHandle, levels, internalFormat, width, height);
}
template<TextureType type> GLPP_DECL
void BasicTextureView<type>::texStorage(GLsizei levels, SizedImageFormat internalFormat, GLsizei width, GLsizei height, GLsizei depth) noexcept {
	glTextureStorage3D(mHandle, levels, internalFormat, width, height, depth);
}

template<TextureType type> GLPP_DECL
void BasicTextureView<type>::bindTextureUnit(unsigned textureUnit) noexcept {
	glBindTextureUnit(textureUnit, mHandle);
}

template<TextureType type> GLPP_DECL
void BasicTextureView<type>::generateMipmaps() noexcept {
	glGenerateTextureMipmap(mHandle);
}


template<TextureType type> GLPP_DECL
void BasicTextureView<type>::depthToR() noexcept {
	// glTextureParameteri(mHandle, GL_RED_DEPTh) // TODO
}
template<TextureType type> GLPP_DECL
void BasicTextureView<type>::stencilToR() noexcept {

}
template<TextureType type> GLPP_DECL
void BasicTextureView<type>::baseLevel(unsigned level) noexcept {
	glTextureParameteri(mHandle, GL_TEXTURE_BASE_LEVEL, level);
}
template<TextureType type> GLPP_DECL
void BasicTextureView<type>::borderColor(float r, float g, float b, float a) noexcept {
	float rgba[4] = {r, g, b, a};
	glTextureParameterfv(mHandle, GL_TEXTURE_BORDER_COLOR, rgba);
}
template<TextureType type> GLPP_DECL
void BasicTextureView<type>::compareFunc(CompareFunc fn) noexcept {
	glTextureParameteri(mHandle, GL_TEXTURE_COMPARE_FUNC, fn);
}
template<TextureType type> GLPP_DECL
void BasicTextureView<type>::lodBias(float value) noexcept {
	glTextureParameterf(mHandle, GL_TEXTURE_LOD_BIAS, value);
}
template<TextureType type> GLPP_DECL
void BasicTextureView<type>::minFilter(Filter filter) noexcept {
	glTextureParameteri(mHandle, GL_TEXTURE_MIN_FILTER, filter);
}
template<TextureType type> GLPP_DECL
void BasicTextureView<type>::magFilter(Filter filter) noexcept {
	glTextureParameteri(mHandle, GL_TEXTURE_MAG_FILTER, filter);
}
template<TextureType type> GLPP_DECL
void BasicTextureView<type>::minLod(float level) noexcept {
	glTextureParameteri(mHandle, GL_TEXTURE_MIN_LOD, level);
}
template<TextureType type> GLPP_DECL
void BasicTextureView<type>::maxLod(float level) noexcept {
	glTextureParameteri(mHandle, GL_TEXTURE_MAX_LOD, level);
}
template<TextureType type> GLPP_DECL
void BasicTextureView<type>::maxLevel(unsigned level) noexcept {
	glTextureParameteri(mHandle, GL_TEXTURE_MAX_LEVEL, level);
}
template<TextureType type> GLPP_DECL
void BasicTextureView<type>::swizzle(ColorComponent r, ColorComponent g, ColorComponent b, ColorComponent a) noexcept {
	GLint params[4] = {r, g, b, a};
	glTextureParameteriv(mHandle, GL_TEXTURE_SWIZZLE_RGBA, params);
}
template<TextureType type> GLPP_DECL
void BasicTextureView<type>::wrapS(WrapMode wrap) noexcept {
	glTextureParameteri(mHandle, GL_TEXTURE_WRAP_S, wrap);
}
template<TextureType type> GLPP_DECL
void BasicTextureView<type>::wrapT(WrapMode wrap) noexcept {
	glTextureParameteri(mHandle, GL_TEXTURE_WRAP_T, wrap);
}
template<TextureType type> GLPP_DECL
void BasicTextureView<type>::wrapR(WrapMode wrap) noexcept {
	glTextureParameteri(mHandle, GL_TEXTURE_WRAP_R, wrap);
}
template<TextureType type> GLPP_DECL
void BasicTextureView<type>::wrap(WrapMode s, WrapMode t, WrapMode r) noexcept {
	wrapS(s);
	if constexpr(type == gl::TEXTURE_1D || type == gl::TEXTURE_1D_ARRAY) return;
	wrapT(t);
	if constexpr(
		type == gl::TEXTURE_2D ||
		type == gl::TEXTURE_2D_ARRAY ||
		type == gl::TEXTURE_2D_MULTISAMPLE ||
		type == gl::TEXTURE_2D_MULTISAMPLE_ARRAY ||
		type == gl::TEXTURE_CUBE_MAP ||
		type == gl::TEXTURE_CUBE_MAP_ARRAY ||
		type == gl::TEXTURE_RECTANGLE
	)
	{
		return;
	}

	wrapR(r);
}
template<TextureType type> GLPP_DECL
float BasicTextureView<type>::maxAnisotropy() noexcept {
	float result = 0;
	glGetTextureParameterfv(mHandle, GL_TEXTURE_MAX_ANISOTROPY, &result);
	return result;
}
template<TextureType type> GLPP_DECL
void BasicTextureView<type>::maxAnisotropy(float f) noexcept {
	glTextureParameterf(mHandle, GL_TEXTURE_MAX_ANISOTROPY, f);
}

template<TextureType type> GLPP_DECL
void BasicTextureView<type>::debugLabel(std::string_view name) noexcept {
	glObjectLabel(GL_TEXTURE, mHandle, name.size(), name.data());
}

template class BasicTexture<TEXTURE_1D>;
template class BasicTexture<TEXTURE_2D>;
template class BasicTexture<TEXTURE_3D>;
template class BasicTexture<TEXTURE_1D_ARRAY>;
template class BasicTexture<TEXTURE_2D_ARRAY>;
template class BasicTexture<TEXTURE_RECTANGLE>;
template class BasicTexture<TEXTURE_CUBE_MAP>;
template class BasicTexture<TEXTURE_CUBE_MAP_ARRAY>;
template class BasicTexture<TEXTURE_BUFFER>;
template class BasicTexture<TEXTURE_2D_MULTISAMPLE>;
template class BasicTexture<TEXTURE_2D_MULTISAMPLE_ARRAY>;

} // namespace gl
