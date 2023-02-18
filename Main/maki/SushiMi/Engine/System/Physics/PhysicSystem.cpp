/*!
@file    PhysicsSystem.cpp
@author	 Aurelia Chong
\par	 email: fei.x@digipen.edu
		 Manages game physics such as acceleration and decelleration
/*
File: PhysicSystem.cpp
Author:
Description: Physics System which runs data from Physics.cpp into it's logics.
*/

#include "PhysicSystem.h"
#include "../../Core/Core.h"
//#include "../Engine/Components/Physics/Physics.h"

namespace Core
{
	PhysicsSystem::PhysicsSystem()
	{

	}

	PhysicsSystem::~PhysicsSystem()
	{

	}

	void PhysicsSystem::Init()
	{

	}

	void PhysicsSystem::Update(const double dt)
	{
		
	}

	void PhysicsSystem::RegisterComponent(std::unordered_map<std::string, Object::GameObject*> ObjectContainer)
	{

	}

	void PhysicsSystem::collision_check_down(Object::GameObject* first, Object::GameObject* second)
	{
		Transform* firstobj = dynamic_cast<Transform*>(first->GetObjectProperties()->GetComponent(ComponentID::Transform));

	}

	void PhysicsSystem::collision_check_left(Object::GameObject* first, Object::GameObject* second)
	{

	}

	void PhysicsSystem::collision_check_right(Object::GameObject* first, Object::GameObject* second)
	{
		
	}

	void PhysicsSystem::collision_check_up(Object::GameObject* first, Object::GameObject* second)
	{

	}

	bool PhysicsSystem::isStuck(Object::GameObject* obj)
	{
		if (obj->GetObjectProperties()->GetComponent(ComponentID::Collision)->IsActive())
		{
			if (dynamic_cast<collision*>(obj->GetObjectProperties()->GetComponent(ComponentID::Collision)))
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			assert(!obj->GetObjectProperties()->GetComponent(ComponentID::Collision)->IsActive());
			std::cout << "No collision component in game object\n";

			return false;
		}
	}
}