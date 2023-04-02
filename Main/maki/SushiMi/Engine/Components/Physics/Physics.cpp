
/*!
@file    Physics.cpp
@author	 Aurelia Chong
\par	 email: fei.x@digipen.edu
		 Manages game physics such as acceleration and decelleration
 /*		Copyright(C) 2022 DigiPen Institute of Technology.
		Reproduction or disclosure of this file or its contents without the
		prior written consent of DigiPen Institute of Technology is prohibited.
*//*__________________________________________________________________________*/
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

	bool Physics::IsActive()
	{
		return active;
	}

	void Physics::Activate()
	{
		active = true;
	}

	void Physics::Deactivate()
	{
		active = false;
	}

	void Physics::Remove()
	{
		remove = true;
	}





	void Physics::Serialise(const std::string name)
	{

	}

	void Physics::Deserialise(const std::string name)
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