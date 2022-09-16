#ifndef GAUSSIAN_BLUR_SHADER_H
#define GAUSSIAN_BLUR_SHADER_H

#include "ShaderProgram.h"

#include <map>
#include <string>

#include "Matrix4f.h"

using std::map;
using std::string;

class GaussianBlurShader : public ShaderProgram
{
public:
	GaussianBlurShader(void);
	virtual ~GaussianBlurShader(void);

	void load_ModelMatrix(const Matrix4f &modelMatrix);
	void load_ViewMatrix(const Matrix4f &viewMatrix);
	void load_ProjectionMatrix(const Matrix4f &projectionMatrix);
	void load_ScreenSize(const unsigned int &width, const unsigned int &height);
	void load_HorizontalBlur(bool horizontal);
	void load_TextureUnit(unsigned int textureUnit);

protected:
	virtual void getAllUniformLocations(void);

private:
	map<string, unsigned int> m_parameters;
};
#endif
