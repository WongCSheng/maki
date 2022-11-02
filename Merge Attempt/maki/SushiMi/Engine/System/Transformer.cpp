

#include "Transformer.h"

Core::Transformer::Transformer()
{
}

Core::Transformer::~Transformer()
{
}

void Core::Transformer::Init()
{
	/*std::unordered_map<Object::GameObjectProperty*, Transform*>::iterator it;
	
	for (it = Transforms.begin(); it != Transforms.end(); it++)
	{
		
	}*/
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
	std::unordered_map<unsigned int, Object::GameObject*>::iterator it;

	for (it = ObjectContainer.begin(); it != ObjectContainer.end(); ++it)
	{
		Transforms.insert({ it->second->GetObjectProperties(), it->second->GetObjectProperties()->GetComponent(ComponentID::Transform) });
	}
}

void Core::Transformer::Serialise(const std::string name)
{

}

void Core::Transformer::UpdateTransformation(Transform* trans)
{
	
}