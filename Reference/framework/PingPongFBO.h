#ifndef PING_PONG_BUFFER_H
#define PING_PONG_BUFFER_H

#include <GL\glew.h>

// FBO for blurring (gaussian)
class PingPongBuffer
{
public:
	PingPongBuffer();
	~PingPongBuffer();

	bool Init(unsigned int WindowWidth, unsigned int WindowHeight);
	void StartFrame(void);
	void Bind(bool firstIteration, GLuint colorBuffer, bool horizontal);
	void BindFinalBlur(GLenum textureLocation);

	GLuint pingpongFBO[2];
	GLuint pingpongBuffer[2];
};

#endif