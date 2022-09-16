#ifndef BLUR_FBO_H
#define BLUR_FBO_H

#include <GL\glew.h>

class BlurBuffer
{
public:
	BlurBuffer();
	~BlurBuffer();

	bool Init(unsigned int WindowWidth, unsigned int WindowHeight);

	void BindForWriting();

	void BindForReading(GLenum TextureUnit);

private:
	GLuint fbo;
	GLuint blur;
};

#endif