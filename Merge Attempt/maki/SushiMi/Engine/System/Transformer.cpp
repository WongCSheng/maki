/*
File: Transformer.cpp
Author: w.chongsheng@digipen.edu
Description: Transform System which takes data in Transform.h to run in it's logic.
*/

#include "Transformer.h"

Core::Transformer::Transformer()
{
}

Core::Transformer::~Transformer()
{
}

void Core::Transformer::Init(Object::GameObject* obj)
{
	/*std::unordered_map<Object::GameObjectProperty*, Transform*>::iterator it;
	
	for (it = Transforms.begin(); it != Transforms.end(); it++)
	{
		
	}*/
}

void Core::Transformer::Update(const double dt)
{
	std::unordered_map<std::string, Object::GameObject*>::iterator it = Transforms.begin();

	for (it; it != Transforms.end(); ++it)
	{
		UpdateTransformation(reinterpret_cast<Core::Transform*>(it->second->GetObjectProperties()->GetComponent(ComponentID::Transform)));
	}
}

void Core::Transformer::RegisterComponent(std::unordered_map<std::string, Object::GameObject*> ObjectContainer)
{
	std::unordered_map<std::string, Object::GameObject*>::iterator it;

	for (it = ObjectContainer.begin(); it != ObjectContainer.end(); ++it)
	{
		Transforms.emplace(it->first, it->second);
	}
}

void Core::Transformer::Serialise(const std::string name)
{

}

void Core::Transformer::UpdateTransformation(Transform* trans)
{
	
}