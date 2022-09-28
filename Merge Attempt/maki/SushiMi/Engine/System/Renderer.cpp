
#include "Renderer.h"

Core::Renderer::Renderer()
{
}

Core::Renderer::~Renderer()
{
}

void Core::Renderer::RegisterComponents(const std::vector<Entity*>& entities)
{
	for (unsigned i = 0; i < entities.size(); ++i)
	{
		Model* mesh = entities[i]->GetComponent<Model>();
		if (mesh != NULL)
		{
			meshes.push_back(mesh);
		}
	}
}

void Core::Renderer::Update(const double dt)
{
	
}

void Core::Renderer::CheckForNewComponents(void)
{

}