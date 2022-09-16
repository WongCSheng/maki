#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "ShaderStorage.h"
#include "script_common.h"

#include <vector>

using std::vector;

struct GraphicSettings
{
	GraphicSettings::GraphicSettings()
	{
		shadow = true;
		ssao = false;
		ssaoKernelSize = 64;
		ssaoRadius = 1.0f;
		ssaoIntensity = 2.0f;
		gamma = 2.2f;
		bloom = false;
		pointLight = true;
		directionalLight = true;
		exposure = 1.f;
	}
	bool shadow;
	bool ssao;
	int ssaoKernelSize;
	float ssaoRadius;
	float ssaoIntensity;
	bool bloom;
	bool pointLight;
	bool directionalLight;
	float gamma;
	float exposure;
};

class GBuffer;
class PPBuffer;
class ShadowMapFBO;
class ssaobuffer;
class PingPongBuffer;
class Graphics
{
public:
	Graphics();
	~Graphics();

	void Init(void);
	void Render(Camera* camera, vector<Entity*> entities);

	GraphicSettings graphicSettings;

private:
	void GetShaders();
	void InitShaders();
	void InitBuffers();

	void ShadowMapPass(Matrix4f Lightperspective, vector<Entity*> &entities);
	void GeometryPass(Camera* camera, Matrix4f perspective, vector<Entity*> &entities);
	void SSAOPass(Matrix4f &perspective);
	void SSAOBlurPass();
	void StencilPass(PointLight* pointLight);
	void PointLightPass(PointLight* pointLight);
	void DirLightPass(Camera* camera, Matrix4f Lightperspective);
	void ForwardPass(Camera* camera, Matrix4f perspective);	// forward + post processing start
	void BloomPass();
	void FinalPass();	// HDR & Gamma Correction
	void UIPass(Camera* camera, Matrix4f perspective);

	unsigned int WindowWidth, WindowHeight;

	SimpleShader* preProcessShader;	// Shader for forward rendering and to start pre processing
	DirLightShader* dirLightShader;
	PointLightShader* pointLightShader;
	GeometryPassShader* gPassShader;
	NullShader* nullShader;
	ShadowShader* shadowShader;
	SSAOShader* ssaoShader;
	SSAOBlurShader* ssaoBlurShader;
	HDRShader* hdrShader;
	GaussianBlurShader* gaussianBlurShader;
	SkyboxShader* skyBoxShader;
	ForwardShader* forwardShader;

	GBuffer* gbuffer;
	ShadowMapFBO* shadowMapFBO;
	ssaobuffer* ssaoBuffer;
	PPBuffer* ppBuffer;
	PingPongBuffer* pingpongFBO;

	LightSystem *lightSystem;
};

#endif