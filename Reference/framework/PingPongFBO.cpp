#include "PingPongFBO.h"
#include <iostream>

#define ARRAY_SIZE_IN_ELEMENTS(a) (sizeof(a) / sizeof(a[0]))
PingPongBuffer::PingPongBuffer()
{
	pingpongFBO[0] = 0;
	pingpongFBO[1] = 0;

	pingpongBuffer[0] = 0;
	pingpongBuffer[1] = 0;
}


PingPongBuffer::~PingPongBuffer()
{
	if (pingpongFBO != 0) {
		glDeleteFramebuffers(2, pingpongFBO);
	}
	if (pingpongBuffer[0] != 0) {
		glDeleteTextures(ARRAY_SIZE_IN_ELEMENTS(pingpongBuffer), pingpongBuffer);
	}
}

bool PingPongBuffer::Init(unsigned int WindowWidth, unsigned int WindowHeight)
{
	glGenFramebuffers(2, pingpongFBO);

	// Create the gbuffer textures
	glGenTextures(2, pingpongBuffer);

	for (unsigned int i = 0; i < 2; ++i)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, pingpongFBO[i]);
		glBindTexture(GL_TEXTURE_2D, pingpongBuffer[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, WindowWidth, WindowHeight, 0, GL_RGB, GL_FLOAT, 0);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, pingpongBuffer[i], 0);

		GLenum DrawBuffers[] = { GL_COLOR_ATTACHMENT0 };
		glDrawBuffers(ARRAY_SIZE_IN_ELEMENTS(DrawBuffers), DrawBuffers);

		GLenum Status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

		if (Status != GL_FRAMEBUFFER_COMPLETE) {
			std::cout << "Incomplete framebuffer" << std::endl;
			return false;
		}

		// restore default FBO
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	}

	return true;
}

void PingPongBuffer::StartFrame(void)
{
	
}

void PingPongBuffer::Bind(bool firstIteration, GLuint colorBuffer, bool horizontal)
{
	glBindFramebuffer(GL_FRAMEBUFFER, pingpongFBO[(int)horizontal]);
	if (firstIteration)
	{
		glBindTexture(GL_TEXTURE_2D, colorBuffer);
	}
	else
	{
		glBindTexture(GL_TEXTURE_2D, pingpongBuffer[(int)(!horizontal)]);
	}
}

void PingPongBuffer::BindFinalBlur(GLenum textureLocation)
{
	glActiveTexture(textureLocation);
	glBindTexture(GL_TEXTURE_2D, pingpongBuffer[1]);
}