#include "TextureData.h"

TextureData::TextureData(void)
{
	m_textureData = 0;
}
TextureData::TextureData(unsigned int l_data, unsigned int l_width, unsigned int l_height, GLubyte *l_buffer, unsigned int bytesPerPixel)
{
	this->m_textureData = l_data;
	this->width = l_width;
	this->height = l_height;
	this->buffer = l_buffer;
	this->bytesPerPixel = bytesPerPixel;
}
TextureData::~TextureData(void)
{
}
unsigned int TextureData::getTextureData(void)
{
	return this->m_textureData;
}
void TextureData::setTextureData(unsigned int l_data)
{
	this->m_textureData = l_data;
}
unsigned int TextureData::getHeight(void)
{
	return this->height;
}
unsigned int TextureData::getWidth(void)
{
	return this->width;
}
GLubyte * TextureData::getBuffer(void)
{
	return this->buffer;
}
unsigned int TextureData::getBytesPerPixel(void)
{
	return this->bytesPerPixel;
}
void TextureData::cleanUpBuffer(void)
{
	delete[]buffer;
}
