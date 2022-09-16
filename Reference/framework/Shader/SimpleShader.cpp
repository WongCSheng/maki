#include "SimpleShader.h"

SimpleShader::SimpleShader(void) : ShaderProgram("Shader//shader.vs", "Shader//shader.fs")
{
	getAllUniformLocations();
}

SimpleShader::~SimpleShader(void)
{
}

void SimpleShader::load_ModelMatrix(const Matrix4f &modelMatrix)
{
	loadU_Mat4f(m_parameters["U_MODEL"], modelMatrix);
}

void SimpleShader::load_ViewMatrix(const Matrix4f &viewMatrix)
{
	loadU_Mat4f(m_parameters["U_VIEW"], viewMatrix);
}

void SimpleShader::load_ProjectionMatrix(const Matrix4f &projectionMatrix)
{
	loadU_Mat4f(m_parameters["U_PROJECTION"], projectionMatrix);
}
void SimpleShader::load_TextureUnit(int i)
{
	loadU_1i(m_parameters["U_TEXTUREUNIT"], i);
}

void SimpleShader::load_ScreenSize(unsigned int width, unsigned int height)
{
	loadU_Vec2f(m_parameters["U_SCREENSIZE"], width, height);
}

void SimpleShader::getAllUniformLocations(void)
{
	m_parameters["U_MODEL"] = getUniformLocation("model"); 
	m_parameters["U_VIEW"] = getUniformLocation("view");
	m_parameters["U_PROJECTION"] = getUniformLocation("projection");
	m_parameters["U_TEXTUREUNIT"] = getUniformLocation("textureID");
	m_parameters["U_SCREENSIZE"] = getUniformLocation("gScreenSize");
}
