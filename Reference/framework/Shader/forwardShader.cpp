#include "ForwardShader.h"

ForwardShader::ForwardShader(void) : ShaderProgram("Shader//forwardShader.vs", "Shader//forwardShader.fs")
{
	getAllUniformLocations();
}

ForwardShader::~ForwardShader(void)
{
}

void ForwardShader::getAllUniformLocations(void)
{
	m_parameters["U_MODEL"] = getUniformLocation("model");
	m_parameters["U_VIEW"] = getUniformLocation("view");
	m_parameters["U_PROJECTION"] = getUniformLocation("projection");
	m_parameters["U_COLOR"] = getUniformLocation("color");
	m_parameters["U_COLORENABLED"] = getUniformLocation("colorEnabled");
	m_parameters["U_VIEWPOS"] = getUniformLocation("viewPos");
	m_parameters["U_SKYBOX"] = getUniformLocation("skybox");
}

void ForwardShader::load_ModelMatrix(const Matrix4f &modelMatrix)
{
	loadU_Mat4f(m_parameters["U_MODEL"], modelMatrix);
}

void ForwardShader::load_ViewMatrix(const Matrix4f &viewMatrix)
{
	loadU_Mat4f(m_parameters["U_VIEW"], viewMatrix);
}

void ForwardShader::load_ProjectionMatrix(const Matrix4f &projectionMatrix)
{
	loadU_Mat4f(m_parameters["U_PROJECTION"], projectionMatrix);
}

void ForwardShader::load_Color(const Vector3 color)
{
	loadU_Vec3f(m_parameters["U_COLOR"], color);
}

void ForwardShader::load_ColorEnabled(const bool colorEnabled)
{
	loadU_Bool(m_parameters["U_COLORENABLED"], colorEnabled);
}

void ForwardShader::load_ViewPos(const Vector3 &viewPos)
{
	loadU_Vec3f(m_parameters["U_VIEWPOS"], viewPos);
}

void ForwardShader::load_CubeMapTextureUnit(const unsigned int textureUnit)
{
	loadU_1i(m_parameters["U_SKYBOX"], textureUnit);
}