#ifndef POINT_LIGHT_SHADER_H
#define POINT_LIGHT_SHADER_H

#include "ShaderProgram.h"

#include <map>
#include <string>

#include "Matrix4f.h"

using std::map;
using std::string;

class PointLight;
class PointLightShader : public ShaderProgram
{
public:
	PointLightShader(void);
	virtual ~PointLightShader(void);

	void load_ModelMatrix(const Matrix4f &modelMatrix);
	void load_ViewMatrix(const Matrix4f &viewMatrix);
	void load_ProjectionMatrix(const Matrix4f &projectionMatrix);
	void load_PointLight(const PointLight *pointLight);
	void load_ViewPosition(const Vector3 &viewPos);
	void load_MatSpecularIntensity(const float &specularIntensity);
	void load_MatSpecularPower(const float &specularPower);
	void load_ScreenSize(const unsigned int &width, const unsigned int &height);
	void load_InverseView(const Matrix4f &inverseViewMatrix);

	void load_TextureIndex(int positionIndex, int colorIndex, int normalIndex, int ssaoIndex);

protected:
	virtual void getAllUniformLocations(void);

private:
	map<string, unsigned int> m_parameters;
};
#endif
