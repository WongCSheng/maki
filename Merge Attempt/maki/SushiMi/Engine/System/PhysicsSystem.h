#pragma once

#include "../Headers/STL_Header.h"
#include "../System/SystemFrame.h"
#include "../Game Object/GameObject.h"
#include "../Engine/Components/Physics/collision.h"

namespace Core
{
	//Forward Declaration
	class Physics;
	
	class PhysicSystem : public SystemFrame
	{
	public:
		PhysicSystem();
		virtual ~PhysicSystem();
		
		float applyAccel(float mass);
		float applyDecel(float mass);
		void updatePosition(Physics* ObjectPhysics);

	private:
		std::unordered_map<Object::GameObject*, Component*> PhysicsContainer;


	};
}