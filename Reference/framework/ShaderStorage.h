#ifndef SHADER_STORAGE_H
#define SHADER_STORAGE_H

#include "Shader\SimpleShader.h"
#include "Shader\GeometryPassShader.h"
#include "Shader\DirLightShader.h"
#include "Shader\PointLightShader.h"
#include "Shader\nullShader.h"
#include "Shader\ShadowShader.h"
#include "Shader\SSAOBlurShader.h"
#include "Shader\SSAOShader.h"
#include "Shader\hdrShader.h"
#include "Shader\gaussianBlurShader.h"
#include "Shader\skyBoxShader.h"
#include "Shader\forwardShader.h"

class ShaderStorage
{
public:
	ShaderStorage();
	~ShaderStorage();

	static inline ShaderStorage& Instance()
	{
		if (instance != NULL)
		{
			return *instance;
		}
		else
		{
			instance = new ShaderStorage();
			return *instance;
		}
	}

	void InitShaders(void);
	void CleanUpShaders(void);

	SimpleShader *shader;
	DirLightShader *dirLightShader;
	PointLightShader *pointLightShader;
	GeometryPassShader* gPassShader;
	NullShader* nullShader;
	ShadowShader* shadowShader;
	SSAOShader* ssaoShader;
	SSAOBlurShader* ssaoBlurShader;
	HDRShader* hdrShader;
	GaussianBlurShader* gaussianBlurShader;
	SkyboxShader* skyboxShader;
	ForwardShader* forwardShader;

private:
	static ShaderStorage* instance;
	void CleanUpShader(ShaderProgram* shader);
};

#endif