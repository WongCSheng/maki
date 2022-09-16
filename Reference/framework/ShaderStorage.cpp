#include "ShaderStorage.h"

ShaderStorage* ShaderStorage::instance = NULL;

ShaderStorage::ShaderStorage() :
shader(NULL),
dirLightShader(NULL),
pointLightShader(NULL),
gPassShader(NULL),
nullShader(NULL),
shadowShader(NULL),
ssaoShader(NULL),
ssaoBlurShader(NULL),
hdrShader(NULL),
gaussianBlurShader(NULL),
skyboxShader(NULL),
forwardShader(NULL)
{
}

ShaderStorage::~ShaderStorage()
{
}

void ShaderStorage::InitShaders(void)
{
	// Create Shaders
	shader = new SimpleShader();
	gPassShader = new GeometryPassShader();
	dirLightShader = new DirLightShader();
	pointLightShader = new PointLightShader();
	nullShader = new NullShader();
	shadowShader = new ShadowShader();
	ssaoShader = new SSAOShader();
	ssaoBlurShader = new SSAOBlurShader();
	hdrShader = new HDRShader();
	gaussianBlurShader = new GaussianBlurShader();
	skyboxShader = new SkyboxShader();
	forwardShader = new ForwardShader();
}

void ShaderStorage::CleanUpShaders(void)
{
	CleanUpShader(shader);
	CleanUpShader(gPassShader);
	CleanUpShader(dirLightShader);
	CleanUpShader(pointLightShader);
	CleanUpShader(nullShader);
	CleanUpShader(shadowShader);
	CleanUpShader(ssaoShader);
	CleanUpShader(ssaoBlurShader);
	CleanUpShader(hdrShader);
	CleanUpShader(gaussianBlurShader);
	CleanUpShader(skyboxShader);
	CleanUpShader(forwardShader);
}

void ShaderStorage::CleanUpShader(ShaderProgram* shader)
{
	if (shader != NULL)
	{
		shader->CleanUp();
		delete shader;
		shader = NULL;
	}
}