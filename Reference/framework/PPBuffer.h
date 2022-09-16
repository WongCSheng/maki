#ifndef PPBUFFER_H
#define PPBUFFER_H

#include <GL\glew.h>

// FBO for post processing
class PPBuffer
{
public:
	enum PPBUFFER_TEXTURE_TYPE {
		PPBUFFER_TEXTURE_TYPE_COLOR,
		PPBUFFER_TEXTURE_TYPE_BRIGHT,
		PPBUFFER_NUM_TEXTURES
	};
	PPBuffer();
	~PPBuffer();

	bool Init(unsigned int WindowWidth, unsigned int WindowHeight);
	void StartFrame(void);
	void BindTexture(GLenum textureLocation, PPBUFFER_TEXTURE_TYPE type);
	void BindForFinalPass(void);
	GLuint GetBrightTexture(void);

private:
	GLuint fbo;
	GLuint textures[PPBUFFER_NUM_TEXTURES];
};

#endif