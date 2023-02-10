#pragma once
<<<<<<< HEAD

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

		//Collision
		void updateCollision(std::unordered_map<std::string, Object::GameObject*> Container);
		/**************************************************************************/
		/*!
		* \brief		structure for the axis bound binding box
		* \param		aabb1 - the first rectangle to checked for collision with the second rectangle
		* \param		aabb2 - the second rectangle to checked for collision with the first rectangle
		* \param		vel1, the velocity that is set to 0 (vel1-vel1 = 0)
		* \param		vel2, the velocity that is set to the resultant velocity (vel2-vel1 = vRel)
		* \return		bool, 0 if no collision/intersection and 1 if there is collision/intersection

		*/
		/**************************************************************************/
		bool CollisionIntersection_RectRect(const AABB& aabb1, const gfxVector2& vel1,
			const AABB& aabb2, const gfxVector2& vel2);

	private:
		std::unordered_map<std::string, Object::GameObject*> PhysicsContainer;
	};
=======
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
#include "../System/SystemFrame.h"

#include "../Game Object/GameObject.h"
#include "../Engine/Components/Physics/collision.h"

#undef min
#undef max

namespace Core
{
	
>>>>>>> M3-submission-branch
}