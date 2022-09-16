#include "HDRShader.h"

HDRShader::HDRShader(void) : ShaderProgram("Shader//hdrShader.vs", "Shader//hdrShader.fs")
{
	getAllUniformLocations();
}

HDRShader::~HDRShader(void)
{
}

void HDRShader::getAllUniformLocations(void)
{
	m_parameters["U_MODEL"] = getUniformLocation("model");
	m_parameters["U_VIEW"] = getUniformLocation("view");
	m_parameters["U_PROJECTION"] = getUniformLocation("projection");
	m_parameters["U_TEXTUREUNIT"] = getUniformLocation("scene");
	m_parameters["U_BLOOMBLURUNIT"] = getUniformLocation("bloomBlur");
	m_parameters["U_SCREENSIZE"] = getUniformLocation("gScreenSize");
	m_parameters["U_GAMMA"] = getUniformLocation("gamma");
	m_parameters["U_BLOOM"] = getUniformLocation("bloom");
	m_parameters["U_EXPOSURE"] = getUniformLocation("exposure");
}

void HDRShader::load_ModelMatrix(const Matrix4f &modelMatrix)
{
	loadU_Mat4f(m_parameters["U_MODEL"], modelMatrix);
}

void HDRShader::load_ViewMatrix(const Matrix4f &viewMatrix)
{
	loadU_Mat4f(m_parameters["U_VIEW"], viewMatrix);
}

void HDRShader::load_ProjectionMatrix(const Matrix4f &projectionMatrix)
{
	loadU_Mat4f(m_parameters["U_PROJECTION"], projectionMatrix);
}

void HDRShader::load_ScreenSize(const unsigned int &width, const unsigned int &height)
{
	loadU_Vec2f(m_parameters["U_SCREENSIZE"], (float)width, (float)height);
}

void HDRShader::load_TextureUnit(const int textureUnit)
{
	loadU_1i(m_parameters["U_TEXTUREUNIT"], textureUnit);
}

void HDRShader::load_BloomBlurUnit(const int textureUnit)
{
	loadU_1i(m_parameters["U_BLOOMBLURUNIT"], textureUnit);
}

void HDRShader::load_Gamma(const float gamma)
{
	loadU_1f(m_parameters["U_GAMMA"], gamma);
}

void HDRShader::load_Bloom(const bool bloom)
{
	loadU_Bool(m_parameters["U_BLOOM"], bloom);
}

void HDRShader::load_Exposure(const float exposure)
{
	loadU_1f(m_parameters["U_EXPOSURE"], exposure);
}