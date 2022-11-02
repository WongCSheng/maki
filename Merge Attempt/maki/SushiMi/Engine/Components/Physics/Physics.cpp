
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