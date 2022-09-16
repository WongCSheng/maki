#ifndef HDR_SHADER_H
#define HDR_SHADER_H

#include "ShaderProgram.h"

#include <map>
#include <string>

#include "Matrix4f.h"

using std::map;
using std::string;

class HDRShader : public ShaderProgram
{
public:
	HDRShader(void);
	virtual ~HDRShader(void);

	void load_ModelMatrix(const Matrix4f &modelMatrix);
	void load_ViewMatrix(const Matrix4f &viewMatrix);
	void load_ProjectionMatrix(const Matrix4f &projectionMatrix);
	void load_ScreenSize(const unsigned int &width, const unsigned int &height);
	void load_TextureUnit(const int textureUnit);
	void load_BloomBlurUnit(const int textureUnit);
	void load_Gamma(const float gamma);
	void load_Bloom(const bool bloom);
	void load_Exposure(const float exposure);

protected:
	virtual void getAllUniformLocations(void);

private:
	map<string, unsigned int> m_parameters;
};
#endif
