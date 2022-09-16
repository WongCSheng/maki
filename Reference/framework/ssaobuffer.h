#ifndef SSAO_FBO_H
#define SSAO_FBO_H

#include <GL\glew.h>
#include <vector>
#include "Vector3.h"

using std::vector;

class ssaobuffer
{
public:
	ssaobuffer(void);
	~ssaobuffer(void);

	vector<Vector3> ssaoKernel;

	void Init(int SCR_WIDTH, int SCR_HEIGHT);

	void BindSSAO(void);
	void BindForSSAOPass(void);

	void BindSSAOColor(void);
	void BindSSAOColorBlur(void);

	void BindSSAOBlur(void);


private:
	void generateNoiseTexAndKernel(void);

	GLuint ssaoFBO, ssaoBlurFBO; // Frame buffer for SSAO and SSAO's Blur
	GLuint ssaoColorBuffer, ssaoColorBufferBlur; // two color buffer
	GLuint noiseTexture;
};

#endif

