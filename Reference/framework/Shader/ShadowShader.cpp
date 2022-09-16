#include "ShadowShader.h"

ShadowShader::ShadowShader(void) : ShaderProgram("Shader//shadowShader.vs", "Shader//shadowShader.fs")
{
	getAllUniformLocations();
}

ShadowShader::~ShadowShader(void)
{
}

void ShadowShader::load_ModelMatrix(const Matrix4f &modelMatrix)
{
	loadU_Mat4f(m_parameters["U_MODEL"], modelMatrix);
}

void ShadowShader::load_ViewMatrix(const Matrix4f &viewMatrix)
{
	loadU_Mat4f(m_parameters["U_VIEW"], viewMatrix);
}

void ShadowShader::load_ProjectionMatrix(const Matrix4f &projectionMatrix)
{
	loadU_Mat4f(m_parameters["U_PROJECTION"], projectionMatrix);
}

void ShadowShader::load_TextureUnit(int textureUnit)
{
	loadU_1i(m_parameters["SHADOWMAP"], textureUnit);
}

void ShadowShader::getAllUniformLocations(void)
{
	m_parameters["U_MODEL"] = getUniformLocation("model"); 
	m_parameters["U_VIEW"] = getUniformLocation("view");
	m_parameters["U_PROJECTION"] = getUniformLocation("projection");
	m_parameters["SHADOWMAP"] = getUniformLocation("gShadowMap");
}
