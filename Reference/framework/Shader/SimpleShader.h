#ifndef SIMPLE_SHADER_H
#define SIMPLE_SHADER_H

#include "ShaderProgram.h"

#include <map>
#include <string>

#include "Matrix4f.h"

using std::map;
using std::string;

class SimpleShader : public ShaderProgram
{
public:
	SimpleShader(void);
	virtual ~SimpleShader(void);

	void load_ModelMatrix(const Matrix4f &modelMatrix);
	void load_ViewMatrix(const Matrix4f &viewMatrix);
	void load_ProjectionMatrix(const Matrix4f &projectionMatrix);

	void load_TextureUnit(int i);
	void load_ScreenSize(unsigned int width, unsigned int height);

protected:
	virtual void getAllUniformLocations(void);

private:
	map<string, unsigned int> m_parameters;
};
#endif
