#include "GeometryPassShader.h"

GeometryPassShader::GeometryPassShader(void) : ShaderProgram("Shader//gPassShader.vs", "Shader//gPassShader.fs")
{
	getAllUniformLocations();
}

GeometryPassShader::~GeometryPassShader(void)
{
}

void GeometryPassShader::getAllUniformLocations(void)
{
	m_parameters["U_MODEL"] = getUniformLocation("model");
	m_parameters["U_VIEW"] = getUniformLocation("view");
	m_parameters["U_PROJECTION"] = getUniformLocation("projection");
	m_parameters["U_DIFFUSETEXTUREUNIT"] = getUniformLocation("texture_diffuse");
	m_parameters["U_NORMALMATRIX"] = getUniformLocation("normalMatrix");
	m_parameters["U_TESSEL"] = getUniformLocation("tessel");
	m_parameters["U_DIFFUSECOLOR"] = getUniformLocation("gDiffuseColor");
	m_parameters["U_DIFFUSECOLORONLY"] = getUniformLocation("gDiffuseColorOnly");
	m_parameters["NORMALTEXTUREUNIT"] = getUniformLocation("texture_normal");
	m_parameters["U_NORMALMAPENABLE"] = getUniformLocation("normalMapEnable");
	m_parameters["U_NEAR"] = getUniformLocation("NEAR");
	m_parameters["U_FAR"] = getUniformLocation("FAR");
	m_parameters["U_PARALLAX"] = getUniformLocation("parallax");
	m_parameters["U_DISPTEXTUREUNIT"] = getUniformLocation("texture_displacement");
	m_parameters["U_VIEWPOS"] = getUniformLocation("viewPos");
	m_parameters["U_GAMMA"] = getUniformLocation("gamma");
	m_parameters["U_SPECULAR"] = getUniformLocation("specular");
	m_parameters["U_SHININESS"] = getUniformLocation("shininess");
}

void GeometryPassShader::load_ModelMatrix(const Matrix4f &modelMatrix)
{
	loadU_Mat4f(m_parameters["U_MODEL"], modelMatrix);
}

void GeometryPassShader::load_ViewMatrix(const Matrix4f &viewMatrix)
{
	loadU_Mat4f(m_parameters["U_VIEW"], viewMatrix);
}

void GeometryPassShader::load_ProjectionMatrix(const Matrix4f &projectionMatrix)
{
	loadU_Mat4f(m_parameters["U_PROJECTION"], projectionMatrix);
}

void GeometryPassShader::load_NormalMatrix(const Matrix4f &normalMatrix)
{
	loadU_Mat4f(m_parameters["U_NORMALMATRIX"], normalMatrix);
}

void GeometryPassShader::load_DiffuseTextureUnit(int diffuseIndex)
{
	loadU_1i(m_parameters["U_DIFFUSETEXTUREUNIT"], diffuseIndex);
}

void GeometryPassShader::load_Tessel(int tessel)
{
	loadU_1i(m_parameters["U_TESSEL"], tessel);
}

void GeometryPassShader::load_DiffuseColor(const Vector3 &diffuseColor)
{
	loadU_Vec3f(m_parameters["U_DIFFUSECOLOR"], diffuseColor);
}

void GeometryPassShader::load_DiffuseColorOnly(const bool &diffuseColorOnly)
{
	loadU_Bool(m_parameters["U_DIFFUSECOLORONLY"], diffuseColorOnly);
}

void GeometryPassShader::load_NormalTextureUnit(unsigned normalTextureIndex)
{
	loadU_1i(m_parameters["NORMALTEXTUREUNIT"], normalTextureIndex);
}

void GeometryPassShader::load_NormalMapEnable(const bool normalMapEnable)
{
	loadU_Bool(m_parameters["U_NORMALMAPENABLE"], normalMapEnable);
}

void GeometryPassShader::load_ProjectionFar(float far)
{
	loadU_1f(m_parameters["U_FAR"], far);
}

void GeometryPassShader::load_ProjectionNear(float near)
{
	loadU_1f(m_parameters["U_NEAR"], near);
}

void GeometryPassShader::load_Parallax(bool parallax)
{
	loadU_Bool(m_parameters["U_PARALLAX"], parallax);
}

void GeometryPassShader::load_DispTextureUnit(int dispTextureUnit)
{
	loadU_1i(m_parameters["U_DISPTEXTUREUNIT"], dispTextureUnit);
}

void GeometryPassShader::load_ViewPosition(Vector3 viewPosition)
{
	loadU_Vec3f(m_parameters["U_VIEWPOS"], viewPosition);
}

void GeometryPassShader::load_Gamma(float gamma)
{
	loadU_1f(m_parameters["U_GAMMA"], gamma);
}

void GeometryPassShader::load_Specular(bool specular)
{
	loadU_Bool(m_parameters["U_SPECULAR"], specular);
}

void GeometryPassShader::load_Shininess(float shininess)
{
	loadU_1f(m_parameters["U_SHININESS"], shininess);
}