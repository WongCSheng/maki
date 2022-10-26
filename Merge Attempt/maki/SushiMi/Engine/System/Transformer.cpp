

#include "Transformer.h"

Core::Transformer::Transformer()
{
}

Core::Transformer::~Transformer()
{
}

void Core::Transformer::Init()
{
	//for (int i = 0; i < entities.size(); ++i)
	//{
	//	Transform* transform = entities[i]->GetComponent<Transform>();
	//	if (transform != NULL)
	//	{
	//		// If entity does not have a parent, add it to the scene root
	//		if (transform->parent == NULL)
	//		{
	//			root->AddChild(entities[i]);
	//		}
	//	}
	//}
}

void Core::Transformer::Update(const double dt)
{
	std::unordered_map<Object::GameObjectProperty*, Transform*>::iterator it = Transforms.begin();

	for (it; it != Transforms.end(); ++it)
	{
		UpdateTransformation(it->second);
	}
}

void Core::Transformer::RegisterComponent(std::unordered_map<unsigned int, Object::GameObject*> ObjectContainer)
{
	
}

void Core::Transformer::Serialise(const std::string name)
{

}

void Core::Transformer::UpdateTransformation(Transform* trans)
{
	
}

void Core::Transformer::RegisterComponent(std::unordered_map<unsigned int, Object::GameObject*> ObjectContainer)
{

}