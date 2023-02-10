<<<<<<< HEAD
/*
File: Physics.cpp
Author: 
Description: Physics components that stores data for which to be used in PhysicSystem.h
*/

=======

/*!
@file    Physics.cpp
@author	 Aurelia Chong
\par	 email: fei.x@digipen.edu
		 Manages game physics such as acceleration and decelleration
 /*		Copyright(C) 2022 DigiPen Institute of Technology.
		Reproduction or disclosure of this file or its contents without the
		prior written consent of DigiPen Institute of Technology is prohibited.
*//*__________________________________________________________________________*/
>>>>>>> M3-submission-branch
#include "Physics.h"

namespace Core
{
	Physics::Physics()
	{
	}

	Physics::~Physics()
	{
	}

	void Physics::Init()
	{

	}

	void Physics::Serialise(const std::string name)
	{

	}

<<<<<<< HEAD
=======
	void Physics::Deserialise(const std::string name)
	{

	}

>>>>>>> M3-submission-branch
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