
#include "Renderer.h"

Core::Renderer::Renderer()
{
}

Core::Renderer::~Renderer()
{
}

void Core::Renderer::Init()
{
	/*for (unsigned i = 0; i < entities.size(); ++i)
	{
		Model* mesh = entities[i]->GetComponent<Model>();
		if (mesh != NULL)
		{
			meshes.push_back(mesh);
		}
	}*/
}

void Core::Renderer::Update(const double dt)
{
	
}

void Core::Renderer::RegisterComponent(std::unordered_map<std::string, Object::GameObject*> ObjectContainer)
{

}