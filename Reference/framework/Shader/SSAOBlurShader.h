#ifndef SSAO_SHADER_BLUR_H
#define SSAO_SHADER_BLUR_H

#include "ShaderProgram.h"
#include <map>
#include <string>
using std::map;
using std::string;

class SSAOBlurShader :
	public ShaderProgram
{
public:
	SSAOBlurShader(void);
	virtual ~SSAOBlurShader(void);

	void load_SSAOTexUnit(int i);
	void load_ScreenSize(float x, float y);

private:
	map<string, unsigned int> m_parameters;

protected:

	// get all the uniform location info into m_parameters[]
	void getAllUniformLocations(void);
};

#endif

