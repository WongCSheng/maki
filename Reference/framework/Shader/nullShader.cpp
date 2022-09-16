#include "NullShader.h"

NullShader::NullShader(void) : ShaderProgram("Shader//nullShader.vs", "Shader//nullShader.fs")
{
	getAllUniformLocations();
}

NullShader::~NullShader(void)
{
}

void NullShader::getAllUniformLocations(void)
{
	m_parameters["U_MODEL"] = getUniformLocation("model");
	m_parameters["U_VIEW"] = getUniformLocation("view");
	m_parameters["U_PROJECTION"] = getUniformLocation("projection");
}

void NullShader::load_ModelMatrix(const Matrix4f &modelMatrix)
{
	loadU_Mat4f(m_parameters["U_MODEL"], modelMatrix);
}

void NullShader::load_ViewMatrix(const Matrix4f &viewMatrix)
{
	loadU_Mat4f(m_parameters["U_VIEW"], viewMatrix);
}

void NullShader::load_ProjectionMatrix(const Matrix4f &projectionMatrix)
{
	loadU_Mat4f(m_parameters["U_PROJECTION"], projectionMatrix);
}
