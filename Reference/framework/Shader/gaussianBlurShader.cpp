#include "GaussianBlurShader.h"

GaussianBlurShader::GaussianBlurShader(void) : ShaderProgram("Shader//gaussianBlurShader.vs", "Shader//gaussianBlurShader.fs")
{
	getAllUniformLocations();
}

GaussianBlurShader::~GaussianBlurShader(void)
{
}

void GaussianBlurShader::getAllUniformLocations(void)
{
	m_parameters["U_MODEL"] = getUniformLocation("model");
	m_parameters["U_VIEW"] = getUniformLocation("view");
	m_parameters["U_PROJECTION"] = getUniformLocation("projection");
	m_parameters["U_SCREENSIZE"] = getUniformLocation("gScreenSize");
	m_parameters["U_HORIZONTAL"] = getUniformLocation("horizontal");
	m_parameters["U_IMAGETEXTUREUNIT"] = getUniformLocation("image");
}

void GaussianBlurShader::load_ModelMatrix(const Matrix4f &modelMatrix)
{
	loadU_Mat4f(m_parameters["U_MODEL"], modelMatrix);
}

void GaussianBlurShader::load_ViewMatrix(const Matrix4f &viewMatrix)
{
	loadU_Mat4f(m_parameters["U_VIEW"], viewMatrix);
}

void GaussianBlurShader::load_ProjectionMatrix(const Matrix4f &projectionMatrix)
{
	loadU_Mat4f(m_parameters["U_PROJECTION"], projectionMatrix);
}

void GaussianBlurShader::load_ScreenSize(const unsigned int &width, const unsigned int &height)
{
	loadU_Vec2f(m_parameters["U_SCREENSIZE"], width, height);
}

void GaussianBlurShader::load_HorizontalBlur(bool horizontal)
{
	loadU_Bool(m_parameters["U_HORIZONTAL"], horizontal);
}

void GaussianBlurShader::load_TextureUnit(unsigned int textureUnit)
{
	loadU_1i(m_parameters["U_IMAGETEXTUREUNIT"], textureUnit);
}
