#ifndef TEXTURE_DATA_H
#define TEXTURE_DATA_H

#include <GL\glew.h>

class TextureData
{
public:
	TextureData(void);
	TextureData(unsigned int l_data, unsigned int l_width, unsigned int l_height, GLubyte *	l_buffer, unsigned int bytesPerPixel);
	~TextureData(void);

	unsigned int getTextureData(void);
	void setTextureData(unsigned int l_data);

	unsigned int getHeight(void);
	unsigned int getWidth(void);
	GLubyte* getBuffer(void);
	unsigned int getBytesPerPixel(void);

	void cleanUpBuffer(void);

private:
	unsigned int m_textureData;

	unsigned int width, height, bytesPerPixel;
	GLubyte * buffer;
};
#endif
