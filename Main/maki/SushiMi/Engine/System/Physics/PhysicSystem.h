#pragma once
/*!
@file    PhysicSystem.h
@author	 Aurelia Chong
\par	 email: fei.x@digipen.edu
		 Manages game physics such as acceleration and decelleration
 /*		Copyright(C) 2022 DigiPen Institute of Technology.
		Reproduction or disclosure of this file or its contents without the
		prior written consent of DigiPen Institute of Technology is prohibited.
*//*__________________________________________________________________________*/


#include "../Headers/STL_Header.h"
#include "../SystemFrame.h"
#include "../Game Object/GameObject.h"
#include "../Engine/Components/Physics/collision.h"

#undef min
#undef max

namespace Core
{
	class PhysicsSystem : public SystemFrame
	{
	public:
		friend class Map;
		friend class collision;

		PhysicsSystem();
		~PhysicsSystem();

		void Init();
		void Update(const double dt);
		void RegisterComponent(std::unordered_map<std::string, Object::GameObject*> ObjectContainer);

		void collision_check_right(Object::GameObject* first, Object::GameObject* second);
		void collision_check_left(Object::GameObject* first, Object::GameObject* second);
		void collision_check_up(Object::GameObject* first, Object::GameObject* second);
		void collision_check_down(Object::GameObject* first, Object::GameObject* second);

		bool isStuck(Object::GameObject* obj);
	};
}