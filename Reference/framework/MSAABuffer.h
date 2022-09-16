#ifndef MSAA_BUFFER_H
#define MSAA_BUFFER_H

#include <GL\glew.h>

class MSAABuffer
{
public:
	MSAABuffer();
	~MSAABuffer();

	bool Init(unsigned int WindowWidth, unsigned int WindowHeight);
	//void BindForWriting(void);
	//void BindForReading(void);

	void StartFrame(void);
	void Unbind(void);
	//void BindTexture(GLenum textureLocation, MSAABuffer_TEXTURE_TYPE type);

private:
	GLuint fbo;
	GLuint texture;
};

#endif