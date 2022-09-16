#ifndef GBUFFER_H
#define GBUFFER_H

#include <GL\glew.h>

class GBuffer
{
public:

	enum GBUFFER_TEXTURE_TYPE {
		GBUFFER_TEXTURE_TYPE_POSITION,
		GBUFFER_TEXTURE_TYPE_POSITIONVIEW,
		GBUFFER_TEXTURE_TYPE_DIFFUSE,
		GBUFFER_TEXTURE_TYPE_NORMAL,
		GBUFFER_TEXTURE_TYPE_NORMALVIEW,
		GBUFFER_TEXTURE_TYPE_SPECULAR,
		GBUFFER_NUM_TEXTURES
	};

	GBuffer();
	~GBuffer();

	bool Init(unsigned int WindowWidth, unsigned int WindowHeight);
	//void BindForWriting(void);
	//void BindForReading(void);

	void StartFrame(void);
	void Unbind(void);
	void BindTexture(GLenum textureLocation, GBUFFER_TEXTURE_TYPE type);
	void BindForGeoPass(void);
	void BindForSSAOPass(void);
	void BindForStencilPass(void);
	void BindForLightPass(void);
	void BindForFinalPass(void);
	void BindForHDRPass(void);
	void ReadDepthTexture(GLenum textureUnit);
	void BindForForwardPass();

private:
	GLuint fbo;
	GLuint textures[GBUFFER_NUM_TEXTURES];
	GLuint depthTexture;
	GLuint finalTexture;
};

#endif