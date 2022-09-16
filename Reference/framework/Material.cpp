#include "Material.h"
#include "Texture.h"
#include "Asset.h"

#define DIFFUSE_TEXTURE_UNIT GL_TEXTURE0

Material::Material() :
color(1, 1, 1),
colorOnly(false),
lighting(true),
shininess(5.f),
tessel(1),
normalMapEnable(false),
handledByMesh(true),
parallaxMapEnable(false),
specMapEnable(false)
{
	diffuseTextures.resize(1);
	diffuseColors.resize(1);
	diffuseOnly.resize(1);
	normalTextures.resize(1);
	dispTextures.resize(1);
	specTextures.resize(1);
}

Material::~Material()
{
	if (handledByMesh)
	{
		for (unsigned int i = 0; i < diffuseTextures.size(); i++)
		{
			if (diffuseTextures[i] != 0)
			{
				delete diffuseTextures[i];
				diffuseTextures[i] = 0;
			}
		}
		for (unsigned int i = 0; i < normalTextures.size(); ++i)
		{
			if (normalTextures[i] != 0)
			{
				delete normalTextures[i];
				normalTextures[i] = 0;
			}
		}
	}
}

void Material::SetManualDiffuse(Texture* diffuse_texture)
{
	this->diffuseTextures[0] = diffuse_texture;
	handledByMesh = false;
}

void Material::SetManualNormal(Texture* normal_texture)
{
	this->normalTextures[0] = normal_texture;
	normalMapEnable = true;
	handledByMesh = false;
}

void Material::SetManualDisp(Texture* disp_texture)
{
	this->dispTextures[0] = disp_texture;
	parallaxMapEnable = true;
	handledByMesh = false;
}

void Material::SetManualSpec(Texture* spec_texture)
{
	this->specTextures[0] = spec_texture;
	specMapEnable = true;
	handledByMesh = false;
}

void Material::SetManualColor(Vector3 color)
{
	this->color = color;
	handledByMesh = false;
	colorOnly = true;
}

bool Material::BindDiffuse(int index)
{
	if (diffuseTextures[index] != NULL)
	{
		diffuseTextures[index]->Bind(DIFFUSE_TEXTURE_UNIT);
		return true;
	}
	return false;
}

bool Material::BindNormal(int index)
{
	if (normalTextures[index] != NULL)
	{
		normalTextures[index]->Bind(GL_TEXTURE1);
		return true;
	}
	return false;
}

bool Material::BindDisp(int index)
{
	if (dispTextures[index] != NULL)
	{
		dispTextures[index]->Bind(GL_TEXTURE2);
		return true;
	}
	return false;
}

bool Material::BindSpec(int index)
{
	if (specTextures[index] != NULL)
	{
		specTextures[index]->Bind(GL_TEXTURE3);
		return true;
	}
	return false;
}

void Material::CopySettings(Material* other)
{
	this->color = other->color;
	colorOnly = other->colorOnly;
	shininess = other->shininess;
	//lighting = other->
	handledByMesh = other->handledByMesh;
	normalMapEnable = other->normalMapEnable;
	parallaxMapEnable = other->parallaxMapEnable;
	specMapEnable = other->specMapEnable;

	diffuseTextures = other->diffuseTextures;
	normalTextures = other->normalTextures;
	diffuseColors = other->diffuseColors;
	diffuseOnly = other->diffuseOnly;
	dispTextures = other->dispTextures;
	specTextures = other->specTextures;
}