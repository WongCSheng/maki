#ifndef SHADOW_SHADER_H
#define SHADOW_SHADER_H

#include "ShaderProgram.h"

#include <map>
#include <string>

#include "Matrix4f.h"

using std::map;
using std::string;

class ShadowShader : public ShaderProgram
{
public:
	ShadowShader(void);
	virtual ~ShadowShader(void);

	void load_ModelMatrix(const Matrix4f &modelMatrix);
	void load_ViewMatrix(const Matrix4f &viewMatrix);
	void load_ProjectionMatrix(const Matrix4f &projectionMatrix);
	void load_ScreenSize(const unsigned int &width, const unsigned int &height);
	void load_TextureUnit(int textureUnit);

protected:
	virtual void getAllUniformLocations(void);

private:
	map<string, unsigned int> m_parameters;
};
#endif
