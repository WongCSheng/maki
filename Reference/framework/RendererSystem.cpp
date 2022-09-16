#include "RendererSystem.h"
#include "MeshF.h"
#include "Material.h"
#include "MeshRenderer.h"
#include "Entity.h"

RendererSystem::RendererSystem()
{
}

RendererSystem::~RendererSystem()
{
}

void RendererSystem::RegisterComponents(const std::vector<Entity*> &entities)
{
	for (unsigned i = 0; i < entities.size(); ++i)
	{
		MeshRenderer* meshRenderer = entities[i]->GetComponent<MeshRenderer>();
		if (meshRenderer != NULL)
		{
			meshRenderer->Validate();
			meshRendererComponents.push_back(meshRenderer);
		}
		MeshFilter* meshFilter = entities[i]->GetComponent<MeshFilter>();
		if (meshFilter != NULL)
		{
			meshFilterComponents.push_back(meshFilter);
		}
	}
}

void RendererSystem::Update(const double dt)
{
}

void RendererSystem::CheckForNewComponents(void)
{

}