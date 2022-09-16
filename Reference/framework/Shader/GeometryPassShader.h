#ifndef GEOMETRY_PASS_SHADER_H
#define GEOMETRY_PASS_SHADER_H

#include "ShaderProgram.h"

#include <map>
#include <string>

#include "Matrix4f.h"

using std::map;
using std::string;

class GeometryPassShader : public ShaderProgram
{
public:
	GeometryPassShader(void);
	virtual ~GeometryPassShader(void);

	void load_ModelMatrix(const Matrix4f &modelMatrix);
	void load_ViewMatrix(const Matrix4f &viewMatrix);
	void load_ProjectionMatrix(const Matrix4f &projectionMatrix);

	void load_NormalMatrix(const Matrix4f &normalMatrix);
	void load_DiffuseTextureUnit(int diffuseIndex);
	void load_Tessel(int tessel);
	void load_DiffuseColor(const Vector3 &diffuseColor);
	void load_DiffuseColorOnly(const bool &diffuseColorOnly);
	void load_NormalTextureUnit(unsigned normalTextureIndex);
	void load_NormalMapEnable(const bool normalMapEnable);
	void load_ProjectionFar(float far);
	void load_ProjectionNear(float near);
	void load_Parallax(bool parallax);
	void load_DispTextureUnit(int dispTextureUnit);
	void load_ViewPosition(Vector3 viewPosition);
	void load_Gamma(float gamma);
	void load_Specular(bool specular);
	void load_Shininess(float shininess);

protected:
	virtual void getAllUniformLocations(void);

private:
	map<string, unsigned int> m_parameters;
};
#endif
