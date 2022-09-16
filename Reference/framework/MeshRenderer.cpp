#include "MeshRenderer.h"
#include "Entity.h"
#include "Material.h"
#include "MeshF.h"
#include "Mesh.h"
#include "Shader\GeometryPassShader.h"

MeshRenderer::MeshRenderer()
{
}

MeshRenderer::~MeshRenderer()
{
}

void MeshRenderer::Validate()
{
	this->meshFilter = owner->GetComponent<MeshFilter>();
	Material* ownerMat = owner->GetComponent<Material>();
	if (ownerMat != NULL)
	{
		if (ownerMat->handledByMesh)
		{
			ownerMat->CopySettings(meshFilter->GetMesh()->material);
		}
	}
	else
	{
		ownerMat = owner->AddComponent<Material>();
		ownerMat->CopySettings(meshFilter->GetMesh()->material);
	}

	this->material = ownerMat;
}

void MeshRenderer::Draw(GeometryPassShader *gPassShader)
{
	if (meshFilter->GetMesh()->handlesMaterial && material->handledByMesh)
	{
		meshFilter->GetMesh()->Render(gPassShader);
	}
	else
	{
		// Diffuse
		if (material->colorOnly)
		{
			gPassShader->load_DiffuseColor(material->color);
			gPassShader->load_DiffuseColorOnly(true);
		}
		else
		{
			material->BindDiffuse();	// bind at index 0, GL_TEXTURE0
			gPassShader->load_DiffuseColorOnly(false);
		}

		// Normal
		if (material->normalMapEnable)
		{
			material->BindNormal(0);	// bind at index 0, GL_TEXTURE1
		}

		// Parallax/Displacement
		if (material->parallaxMapEnable)
		{
			material->BindDisp(0);	// bind at index 0, GL_TEXTURE2
		}

		// Specular
		if (material->specMapEnable)
		{
			material->BindSpec(0);	// bind at inedx 0, GL_TEXTURE3
		}

		gPassShader->load_NormalMapEnable(material->normalMapEnable);
		gPassShader->load_Parallax(material->parallaxMapEnable);
		gPassShader->load_Specular(material->specMapEnable);
		gPassShader->load_Tessel(material->tessel);
		gPassShader->load_Shininess(material->shininess);
		meshFilter->GetMesh()->RenderMeshOnly();
	}
}

void MeshRenderer::DrawMeshOnly()
{
	if (meshFilter->GetMesh() != NULL)
	{
		meshFilter->GetMesh()->RenderMeshOnly();
	}
}