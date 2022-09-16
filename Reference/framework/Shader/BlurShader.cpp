#include "BlurShader.h"

BlurShader::BlurShader(void) : ShaderProgram("Shader//blurShader.vs", "Shader//blurShader.fs")
{
	getAllUniformLocations();
}

BlurShader::~BlurShader(void)
{
}

void BlurShader::load_ColorIndex(unsigned colorIndex)
{
	loadU_1i(m_parameters["U_COLORMAP"], colorIndex);
}

void BlurShader::getAllUniformLocations(void)
{
	m_parameters["U_COLORMAP"] = getUniformLocation("gColorMap");
}
