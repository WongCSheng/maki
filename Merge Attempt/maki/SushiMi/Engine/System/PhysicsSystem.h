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

		void Init();
		void Update(const double dt);
		void RegisterComponent(std::unordered_map<std::string, Object::GameObject*> ObjectContainer);
		
		float applyAccel(float mass);
		float applyDecel(float mass);
		void updatePosition(Physics* ObjectPhysics);

	private:
		std::unordered_map<std::string, Object::GameObject*> PhysicsContainer;


	};
}