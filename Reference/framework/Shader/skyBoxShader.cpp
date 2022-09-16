#include "SkyboxShader.h"

SkyboxShader::SkyboxShader(void) : ShaderProgram("Shader//skyBoxShader.vs", "Shader//skyBoxShader.fs")
{
	getAllUniformLocations();
}

SkyboxShader::~SkyboxShader(void)
{
}

void SkyboxShader::load_ModelMatrix(const Matrix4f &modelMatrix)
{
	loadU_Mat4f(m_parameters["U_MODEL"], modelMatrix);
}

void SkyboxShader::load_ViewMatrix(const Matrix4f &viewMatrix)
{
	loadU_Mat4f(m_parameters["U_VIEW"], viewMatrix);
}

void SkyboxShader::load_ProjectionMatrix(const Matrix4f &projectionMatrix)
{
	loadU_Mat4f(m_parameters["U_PROJECTION"], projectionMatrix);
}

void SkyboxShader::load_TextureUnit(const unsigned int textureUnit)
{
	loadU_1i(m_parameters["SKYBOX"], textureUnit);
}

void SkyboxShader::load_DepthUnit(const unsigned int depthUnit)
{
	loadU_1i(m_parameters["DEPTH"], depthUnit);
}

void SkyboxShader::getAllUniformLocations(void)
{
	m_parameters["U_MODEL"] = getUniformLocation("model"); 
	m_parameters["U_VIEW"] = getUniformLocation("view");
	m_parameters["U_PROJECTION"] = getUniformLocation("projection");
	m_parameters["SKYBOX"] = getUniformLocation("skybox");
	m_parameters["DEPTH"] = getUniformLocation("depth");
}
