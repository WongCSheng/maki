#pragma once

#include "../Headers/STL_Header.h"
#include "../System/SystemFrame.h"
#include "../Game Object/GameObject.h"
#include "../Engine/Components/Physics/collision.h"

namespace Core
{
	class PhysicSystem : public SystemFrame
	{
	private:
		std::unordered_map<unsigned int, Object::GameObject*> ObjectContainer;

	public:
		PhysicSystem();
		virtual ~PhysicSystem();
	};
}