#ifndef DIR_LIGHT_SHADER_H
#define DIR_LIGHT_SHADER_H

#include "ShaderProgram.h"

#include <map>
#include <string>

#include "Matrix4f.h"

using std::map;
using std::string;

class DirectionLight;
class DirLightShader : public ShaderProgram
{
public:
	DirLightShader(void);
	virtual ~DirLightShader(void);
	
	void load_InverseViewMatrix(const Matrix4f &inverseViewMat);
	void load_DirectionalLight(DirectionLight *dLight);
	void load_ViewPosition(const Vector3 &viewPos);
	void load_ShadowMapTextureUnit(unsigned int TextureUnit);
	void load_AOTextureUnit(unsigned int AOTextureUnit);
	void load_EnableShadow(bool enableShadow);
	void load_EnableAO(bool enableAO);
	void load_LightViewMatrix(const Matrix4f &lightViewMatrix);
	void load_LightProjectionMatrix(const Matrix4f &lightProjectionMatrix);

	void load_TextureIndex(int positionIndex, int colorIndex, int normalIndex);
	void load_ScreenSize(unsigned int width, unsigned int height);

protected:
	virtual void getAllUniformLocations(void);

private:
	map<string, unsigned int> m_parameters;
};
#endif
