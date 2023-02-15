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
#include "../Engine/Components/Physics/Physics.h"

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
		// if player's grid index is 50, means its STUCK or put all ingr into goals
		if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] == static_cast<int>(grid_number::sinkhole) &&
			!isWin())
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}