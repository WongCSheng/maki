#include "DirLightShader.h"
#include "../DirectionLight.h"

DirLightShader::DirLightShader(void) : ShaderProgram("Shader//dirLightShader.vs", "Shader//dirLightShader.fs")
{
	getAllUniformLocations();
}

DirLightShader::~DirLightShader(void)
{
}

void DirLightShader::load_InverseViewMatrix(const Matrix4f &inverseViewMat)
{
	loadU_Mat4f(m_parameters["U_INVERSEVIEW"], inverseViewMat);
}

void DirLightShader::load_DirectionalLight(DirectionLight *dLight)
{
	loadU_Vec3f(m_parameters["U_LIGHTCOLOR"], dLight->color);
	loadU_1f(m_parameters["U_AMBIENT"], dLight->ambientIntensity);
	loadU_Vec3f(m_parameters["U_LIGHTDIRECTION"], dLight->GetDirection());
	loadU_1f(m_parameters["U_DIFFUSE"], dLight->diffuseIntensity);
}

void DirLightShader::load_ViewPosition(const Vector3 &viewPos)
{
	loadU_Vec3f(m_parameters["U_VIEWPOS"], viewPos);
}

void DirLightShader::load_ShadowMapTextureUnit(unsigned int TextureUnit)
{
	loadU_1i(m_parameters["U_SHADOWTEXTUREUNIT"], TextureUnit);
}

void DirLightShader::load_AOTextureUnit(unsigned int AOTextureUnit)
{
	loadU_1i(m_parameters["U_AOTEXTUREUNIT"], AOTextureUnit);
}

void DirLightShader::load_EnableShadow(bool enableShadow)
{
	loadU_Bool(m_parameters["U_ENABLESHADOW"], enableShadow);
}

void DirLightShader::load_EnableAO(bool enableAO)
{
	loadU_Bool(m_parameters["U_ENABLEAO"], enableAO);
}

void DirLightShader::load_LightViewMatrix(const Matrix4f &lightViewMatrix)
{
	loadU_Mat4f(m_parameters["U_LIGHTVIEW"], lightViewMatrix);
}

void DirLightShader::load_LightProjectionMatrix(const Matrix4f &lightProjectionMatrix)
{
	loadU_Mat4f(m_parameters["U_LIGHTPROJECTION"], lightProjectionMatrix);
}

void DirLightShader::load_ScreenSize(unsigned int width, unsigned int height)
{
	loadU_Vec2f(m_parameters["U_SCREENSIZE"], (float)width, (float)height);
}

void DirLightShader::load_TextureIndex(int positionIndex, int colorIndex, int normalIndex)
{
	loadU_1i(m_parameters["U_POSMAP"], positionIndex);
	loadU_1i(m_parameters["U_COLORMAP"], colorIndex);
	loadU_1i(m_parameters["U_NORMALMAP"], normalIndex);
	loadU_1i(m_parameters["U_SPECMAP"], 3);
}

void DirLightShader::getAllUniformLocations(void)
{
	m_parameters["U_INVERSEVIEW"] = getUniformLocation("gInverseView");
	m_parameters["U_COLOR"] = getUniformLocation("color");
	m_parameters["U_LIGHTCOLOR"] = getUniformLocation("directionalLight.Color");
	m_parameters["U_AMBIENT"] = getUniformLocation("directionalLight.AmbientIntensity");
	m_parameters["U_LIGHTDIRECTION"] = getUniformLocation("directionalLight.Direction");
	m_parameters["U_DIFFUSE"] = getUniformLocation("directionalLight.DiffuseIntensity");
	m_parameters["U_LIGHTING"] = getUniformLocation("lighting");
	m_parameters["U_VIEWPOS"] = getUniformLocation("viewPos");
	m_parameters["U_SCREENSIZE"] = getUniformLocation("gScreenSize");
	m_parameters["U_POSMAP"] = getUniformLocation("gPositionMap");
	m_parameters["U_COLORMAP"] = getUniformLocation("gColorMap");
	m_parameters["U_NORMALMAP"] = getUniformLocation("gNormalMap");
	m_parameters["U_LIGHTVIEW"] = getUniformLocation("lightView");
	m_parameters["U_LIGHTPROJECTION"] = getUniformLocation("lightProjection");
	m_parameters["U_SHADOWTEXTUREUNIT"] = getUniformLocation("gShadowMap");
	m_parameters["U_AOTEXTUREUNIT"] = getUniformLocation("gAOMap");
	m_parameters["U_ENABLESHADOW"] = getUniformLocation("gEnableShadow");
	m_parameters["U_ENABLEAO"] = getUniformLocation("gEnableAO");
	m_parameters["U_SPECMAP"] = getUniformLocation("gSpecMap");
}
