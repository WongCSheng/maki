#include "PointLightShader.h"
#include "../PointLight.h"

PointLightShader::PointLightShader(void) : ShaderProgram("Shader//pointLightShader.vs", "Shader//pointLightShader.fs")
{
	getAllUniformLocations();
}

PointLightShader::~PointLightShader(void)
{
}

void PointLightShader::load_ModelMatrix(const Matrix4f &modelMatrix)
{
	loadU_Mat4f(m_parameters["U_MODEL"], modelMatrix);
}

void PointLightShader::load_ViewMatrix(const Matrix4f &viewMatrix)
{
	loadU_Mat4f(m_parameters["U_VIEW"], viewMatrix);
}

void PointLightShader::load_ProjectionMatrix(const Matrix4f &projectionMatrix)
{
	loadU_Mat4f(m_parameters["U_PROJECTION"], projectionMatrix);
}

void PointLightShader::load_ScreenSize(const unsigned int &width, const unsigned int &height)
{
	loadU_Vec2f(m_parameters["U_SCREENSIZE"], (float)width, (float)height);
}

void PointLightShader::load_PointLight(const PointLight *pointLight)
{
	loadU_Vec3f(m_parameters["U_LIGHTCOLOR"], pointLight->color);
	loadU_1f(m_parameters["U_AMBIENT"], pointLight->ambientIntensity);
	loadU_1f(m_parameters["U_DIFFUSE"], pointLight->diffuseIntensity);
	loadU_Vec3f(m_parameters["U_LIGHTPOSITION"], pointLight->position);
	loadU_1f(m_parameters["U_CONSTANT"], pointLight->atten.Constant);
	loadU_1f(m_parameters["U_LINEAR"], pointLight->atten.Linear);
	loadU_1f(m_parameters["U_EXP"], pointLight->atten.Exp);
}

void PointLightShader::load_ViewPosition(const Vector3 &viewPos)
{
	loadU_Vec3f(m_parameters["U_VIEWPOS"], viewPos);
}

void PointLightShader::load_MatSpecularIntensity(const float &specularIntensity)
{
	loadU_1f(m_parameters["U_SPECINTENSITY"], specularIntensity);
}

void PointLightShader::load_MatSpecularPower(const float &specularPower)
{
	loadU_1f(m_parameters["U_SPECPOWER"], specularPower);
}

void PointLightShader::load_InverseView(const Matrix4f &inverseViewMatrix)
{
	loadU_Mat4f(m_parameters["U_INVERSEMAT"], inverseViewMatrix);
}

void PointLightShader::load_TextureIndex(int positionIndex, int colorIndex, int normalIndex, int ssaoIndex)
{
	loadU_1i(m_parameters["U_POSMAP"], positionIndex);
	loadU_1i(m_parameters["U_COLORMAP"], colorIndex);
	loadU_1i(m_parameters["U_NORMALMAP"], normalIndex);
	loadU_1i(m_parameters["U_SPECULAR"], 3);
	loadU_1i(m_parameters["U_SSAOINDEX"], 4);
}

void PointLightShader::getAllUniformLocations(void)
{
	m_parameters["U_MODEL"] = getUniformLocation("model"); 
	m_parameters["U_VIEW"] = getUniformLocation("view");
	m_parameters["U_PROJECTION"] = getUniformLocation("projection");
	m_parameters["U_TEXTUREUNIT"] = getUniformLocation("texture_diffuse");
	m_parameters["U_LIGHTCOLOR"] = getUniformLocation("pointLights.Color");
	m_parameters["U_AMBIENT"] = getUniformLocation("pointLights.AmbientIntensity");
	m_parameters["U_LIGHTPOSITION"] = getUniformLocation("pointLights.Position");
	m_parameters["U_CONSTANT"] = getUniformLocation("pointLights.Constant");
	m_parameters["U_LINEAR"] = getUniformLocation("pointLights.Linear");
	m_parameters["U_EXP"] = getUniformLocation("pointLights.Exp");
	m_parameters["U_DIFFUSE"] = getUniformLocation("pointLights.DiffuseIntensity");
	m_parameters["U_VIEWPOS"] = getUniformLocation("viewPos");
	m_parameters["U_SPECINTENSITY"] = getUniformLocation("SpecularIntensity");
	m_parameters["U_SPECPOWER"] = getUniformLocation("SpecularPower");
	m_parameters["U_SCREENSIZE"] = getUniformLocation("gScreenSize");
	m_parameters["U_POSMAP"] = getUniformLocation("gPositionMap");
	m_parameters["U_COLORMAP"] = getUniformLocation("gColorMap");
	m_parameters["U_NORMALMAP"] = getUniformLocation("gNormalMap");
	m_parameters["U_INVERSEMAT"] = getUniformLocation("gInverseView");
	m_parameters["U_SSAOINDEX"] = getUniformLocation("ssao");
	m_parameters["U_SPECULAR"] = getUniformLocation("gSpecMap");
}
