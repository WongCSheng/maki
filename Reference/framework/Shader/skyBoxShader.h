#ifndef SKYBOX_SHADER_H
#define SKYBOX_SHADER_H

#include "ShaderProgram.h"

#include <map>
#include <string>

#include "Matrix4f.h"

using std::map;
using std::string;

class SkyboxShader : public ShaderProgram
{
public:
	SkyboxShader(void);
	virtual ~SkyboxShader(void);

	void load_ModelMatrix(const Matrix4f &modelMatrix);
	void load_ViewMatrix(const Matrix4f &viewMatrix);
	void load_ProjectionMatrix(const Matrix4f &projectionMatrix);
	void load_ScreenSize(const unsigned int &width, const unsigned int &height);
	void load_TextureUnit(const unsigned int textureUnit);
	void load_DepthUnit(const unsigned int depthUnit);

protected:
	virtual void getAllUniformLocations(void);

private:
	map<string, unsigned int> m_parameters;
};
#endif
