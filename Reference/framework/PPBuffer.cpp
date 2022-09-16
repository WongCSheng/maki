#include "PPBuffer.h"
#include <iostream>

#define ARRAY_SIZE_IN_ELEMENTS(a) (sizeof(a) / sizeof(a[0]))
PPBuffer::PPBuffer()
{
	fbo = 0;
	for (int i = 0; i < PPBUFFER_NUM_TEXTURES; ++i)
	{
		textures[i] = 0;
	}
}


PPBuffer::~PPBuffer()
{
	if (fbo != 0) {
		glDeleteFramebuffers(1, &fbo);
	}
	if (textures[0] != 0) {
		glDeleteTextures(ARRAY_SIZE_IN_ELEMENTS(textures), textures);
	}
}

bool PPBuffer::Init(unsigned int WindowWidth, unsigned int WindowHeight)
{
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo);

	// Create the gbuffer textures
	glGenTextures(ARRAY_SIZE_IN_ELEMENTS(textures), textures);

	for (unsigned int i = 0; i < ARRAY_SIZE_IN_ELEMENTS(textures); ++i)
	{
		glBindTexture(GL_TEXTURE_2D, textures[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, WindowWidth, WindowHeight, 0, GL_RGBA, GL_FLOAT, 0);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, textures[i], 0);
	}

	GLenum DrawBuffers[] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
	glDrawBuffers(ARRAY_SIZE_IN_ELEMENTS(DrawBuffers), DrawBuffers);

	GLenum Status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

	if (Status != GL_FRAMEBUFFER_COMPLETE) {
		std::cout << "Incomplete framebuffer" << std::endl;
		return false;
	}

	// restore default FBO
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

	return true;
}

void PPBuffer::StartFrame(void)
{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo);
	GLenum DrawBuffers[] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1};
	glDrawBuffers(ARRAY_SIZE_IN_ELEMENTS(DrawBuffers), DrawBuffers);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void PPBuffer::BindTexture(GLenum textureLocation, PPBUFFER_TEXTURE_TYPE type)
{
	glActiveTexture(textureLocation);
	glBindTexture(GL_TEXTURE_2D, textures[type]);
}

void PPBuffer::BindForFinalPass(void)
{
	/*glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo);
	GLenum DrawBuffers[] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(ARRAY_SIZE_IN_ELEMENTS(DrawBuffers), DrawBuffers);*/
}

GLuint PPBuffer::GetBrightTexture(void)
{
	return textures[PPBUFFER_TEXTURE_TYPE_BRIGHT];
}