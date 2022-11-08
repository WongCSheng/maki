#pragma once

#include "../Headers/STL_Header.h"
#include "../Component.h"
#include "../Headers/Math_Header.h"

namespace Core
{
	class Physics : public Component
	{
	private:
		//Physics* instance;

	public:
		Physics();
		virtual ~Physics();
		
		float mass;
		gfxVector2 velocity;
		gfxVector2 position;

		float GetMass();
		gfxVector2 GetVelocity();
		gfxVector2 GetPosition();
	};
}