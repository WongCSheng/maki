/*
File:		 ECS.cpp
Author:		 w.chongsheng@digipen.edu
Description: This file contains the function definition for Entities and Components
*/

#include "Component.h"
#include "../Engine/Components/Transform/Transform.h"
#include "../Game Object/GameObject.h"

namespace Core
{
	
	Component::Component()
	{
		owner = nullptr;
		add = false;
		active = false;
		remove = false;
	}
	
	Component::~Component()
	{
		//delete owner;
	}

	Object::GameObjectProperty* Component::GetOwner()
	{
		return owner;
	}

	void Component::SetOwner(Object::GameObjectProperty* NewOwner)
	{
		owner = NewOwner;
	}

	bool Component::IsActive()
	{
		return active;
	}

	void Component::Activate()
	{
		active = true;
	}

	void Component::Deactivate()
	{
		active = false;
	}

	void Component::Remove()
	{
		remove = true;
	}

	//int Core::Entity::entity_count = 0; // Counter for amount of entities created.
//
///*
//	Constructor for a Entity.
//*/
//
//Core::Entity::Entity() :
//	active(true),
//	remove(false)
//{
//	transform = AddComponent<Transform>();
//	//AddComponent<Material>();
//	id = entity_count;
//	++entity_count;
//}
//
///*
//	Destructor for Entity.
//*/
//
//Core::Entity::~Entity()
//{
//	transform->children.clear();
//	transform->parent->Owner()->DetachChild(this);
//	transform->parent = NULL;
//	for (unsigned i = 0; i < components.size(); ++i)
//	{
//		if (components[i] != NULL)
//		{
//			delete components[i];
//			components[i] = NULL;
//		}
//	}
//}
//
///*
//	Returns the identification number for the Entity.
//	To see what components it has.
//*/
//
//const int Core::Entity::GetID()
//{
//	return id;
//}
//
///*
//	Check if the Entity is active.
//*/
//
//bool Core::Entity::IsActive()
//{
//	return active;
//}
//
///*
//	Activates the Entity.
//*/
//
//void Core::Entity::Activate()
//{
//	active = true;
//}
//
///*
//	Deactivates the Entity.
//*/
//
//void Core::Entity::Deactivate()
//{
//	active = false;
//}
//
///*
//	Attaches an Entity a parent Entity.
//*/
//
//void Core::Entity::AddChild(Entity* child)
//{
//	//children.push_back(child);
//	//child->parent = this;
//	transform->children.push_back(child->transform);
//	//transform->parent = transform;
//	child->transform->parent = transform;
//}
//
///*
//	Detaches an Entity from a parent Entity.
//*/
//
//void Core::Entity::DetachChild(Entity* child)
//{
//	for (unsigned i = 0; i < transform->children.size(); ++i)
//	{
//		if (transform->children[i] == child->transform)
//		{
//			transform->children[i]->parent = NULL;
//			transform->children.erase(transform->children.begin() + i);
//			break;
//		}
//	}
//}
//
///*
//	
//*/
//
//void Core::Entity::DetachChild(int number)
//{
//	transform->children[number]->parent = NULL;
//	transform->children.erase(transform->children.begin() + number);
//}
//
//void Core::Entity::DetachAllChild()
//{
//	for (unsigned i = 0; i < transform->children.size(); ++i)
//	{
//		transform->children[i]->parent = NULL;
//	}
//
//	transform->children.clear();
//}
//
//void Core::Entity::DetachParent()
//{
//	transform->parent = NULL;
//}
//
//Core::Component::Component() :
//	active(true),
//	remove(false)
//{
//}
}