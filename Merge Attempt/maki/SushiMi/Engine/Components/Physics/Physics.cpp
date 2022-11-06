/*
File: Physics.cpp
Author: 
Description: Physics components that stores data for which to be used in PhysicSystem.h
*/

#include "Physics.h"

namespace Core
{
	Physics::Physics()
	{
	}

	Physics::~Physics()
	{
	}

	float Physics::GetMass()
	{
		return mass;
	}

	gfxVector2 Physics::GetPosition()
	{
		return position;
	}

	gfxVector2 Physics::GetVelocity()
	{
		return velocity;
	}
}