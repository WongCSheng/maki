#include "SSAOBlurShader.h"


SSAOBlurShader::SSAOBlurShader(void) : ShaderProgram("Shader//ssaoBlur.vs", "Shader//ssaoBlur.fs")
{
	getAllUniformLocations();
}


SSAOBlurShader::~SSAOBlurShader()
{
}

void SSAOBlurShader::getAllUniformLocations(void)
{
	m_parameters["U_SSAO"] = getUniformLocation("ssaoInput");
	m_parameters["U_SCREENSIZE"] = getUniformLocation("gScreenSize");
}

void SSAOBlurShader::load_SSAOTexUnit(int i)
{
	loadU_1i(m_parameters["U_SSAO"], i);
}

void SSAOBlurShader::load_ScreenSize(float x, float y)
{
	loadU_Vec2f(m_parameters["U_SCREENSIZE"], x, y);
}
