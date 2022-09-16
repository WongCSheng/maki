#ifndef FORWARD_SHADER_H
#define FORWARD_SHADER_H

#include "ShaderProgram.h"

#include <map>
#include <string>

#include "Matrix4f.h"

using std::map;
using std::string;

class ForwardShader : public ShaderProgram
{
public:
	ForwardShader(void);
	virtual ~ForwardShader(void);

	void load_ModelMatrix(const Matrix4f &modelMatrix);
	void load_ViewMatrix(const Matrix4f &viewMatrix);
	void load_ProjectionMatrix(const Matrix4f &projectionMatrix);
	void load_ScreenSize(const unsigned int &width, const unsigned int &height);
	void load_Color(const Vector3 color);
	void load_ColorEnabled(const bool colorEnabled);
	void load_ViewPos(const Vector3 &viewPos);
	void load_CubeMapTextureUnit(const unsigned int textureUnit);

protected:
	virtual void getAllUniformLocations(void);

private:
	map<string, unsigned int> m_parameters;
};
#endif
