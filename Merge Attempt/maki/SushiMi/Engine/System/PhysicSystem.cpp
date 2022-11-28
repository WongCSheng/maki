/*
File: PhysicSystem.cpp
Author: 
Description: Physics System which runs data from Physics.cpp into it's logics.
*/

#include "PhysicsSystem.h"
#include "../Engine/Components/Physics/Physics.h"

namespace Core
{
	PhysicSystem::PhysicSystem()
	{
	}

	PhysicSystem::~PhysicSystem()
	{
	}

	void PhysicSystem::Init()
	{

	}

	void PhysicSystem::Update(const double dt)
	{
		
	}

	void PhysicSystem::RegisterComponent(std::unordered_map<std::string, Object::GameObject*> ObjectContainer)
	{

	}

	//glm::vec2 gravity(-9.81, 0); //applying gravity to x axis

// F = ma ; accel = F/m
	float force = 50.f; // fixed force

	//acceleration
	float PhysicSystem::applyAccel(float mass) //input mass
	{
		return force / mass;
	}

	float PhysicSystem::applyDecel(float mass) //deceleration for obj to stop
	{
		return -force / mass;
	}


	////apply acceleration
	//	glm::vec2 displacement = Object::objects["Object5"].position - Object::objects["Object5"].initialPos;
	void PhysicSystem::updatePosition(Physics* ObjectPhysics)
	{
		float acceleration = applyAccel(ObjectPhysics->GetMass());	 //	stores acceleration

		// Updating the velocity and position according to acceleration is done by using the following:
		// step1: v1 = a*t + v0        //This is done when the UP or DOWN key is pressed 
		// step2: Pos1 = 1/2 * a*t*t + v0*t + Pos0
		// step3: Pos1 = v1t + Pos0

		gfxVector2 preVel = ObjectPhysics->velocity;			 //	stores previous velocity/v0
		gfxVector2 prePos = ObjectPhysics->position;				 //	stores previous position/p0

		/*update velocity based on previous velocity*/
		ObjectPhysics->velocity.x = ((acceleration * static_cast<float>(GLHelper::delta_time)) + preVel.x); //step1 .x
		ObjectPhysics->velocity.y = ((acceleration * static_cast<float>(GLHelper::delta_time)) + preVel.y); //step1 .y


		/*update position based on velocity & previous position*/
		ObjectPhysics->position.x = ((1 / 2 * acceleration * static_cast<float>(GLHelper::delta_time * GLHelper::delta_time) +
			(ObjectPhysics->velocity.x * static_cast<float>(GLHelper::delta_time))) + prePos.x);						//step2	.x	


		ObjectPhysics->position.y = ((1 / 2 * acceleration * static_cast<float>(GLHelper::delta_time * GLHelper::delta_time)) +
			(ObjectPhysics->velocity.y * static_cast<float>(GLHelper::delta_time)) + prePos.y);					//step2	.y

	}
	
	void PhysicSystem::updateCollision(std::unordered_map<std::string, Object::GameObject*> Container)
	{
		
	}

	bool PhysicSystem::CollisionIntersection_RectRect(const AABB& aabb1, const gfxVector2& vel1,
		const AABB& aabb2, const gfxVector2& vel2)
	{

		/*
		Implement the collision intersection over here.

		The steps are:
		Step 1: Check for static collision detection between rectangles (before moving).
					If the check returns no overlap you continue with the following next steps (dynamics).
					Otherwise you return collision true

		Step 2: Initialize and calculate the new velocity of Vb
				tFirst = 0
				tLast = dt

		Step 3: Working with one dimension (x-axis).
				if(Vb < 0)
					case 1
					case 4
				if(Vb > 0)
					case 2
					case 3

				case 5

		Step 4: Repeat step 3 on the y-axis

		Step 5: Otherwise the rectangles intersect

		*/
		double tFirst = 0.f;
		double tLast = GLHelper::delta_time;
		double dFirst = 0.f, dLast = 0.f;
		if (aabb1.max.y < aabb2.min.y || aabb1.max.x < aabb2.min.x || aabb1.min.y > aabb2.max.y || aabb1.min.x > aabb2.max.x) //if no overlap, continue
		{
			return false;
		}

		/***************************************/
		// working with x-axis
		/***************************************/
		if ((vel2.x - vel1.x) < 0.f) //case 1 & 4
		{
			if (aabb1.min.x > aabb2.max.x) //case 1
			{
				return false;
			}
			if (aabb1.max.x < aabb2.min.x) //case 4  (1/2)
			{
				dFirst = aabb1.max.x - aabb2.min.x;
				tFirst = dFirst / (vel2.x - vel1.x);

			}
			if (aabb1.min.x < aabb2.max.x) //case 4  (2/2)
			{

				dLast = aabb1.min.x - aabb2.max.x;
				tLast = dLast / (vel2.x - vel1.x);
			}
		}
		if ((vel2.x - vel1.x) > 0.f) //case 2 & case 3
		{
			if (aabb1.min.x > aabb2.max.x) //case 2 (1/2)
			{
				dFirst = aabb1.min.x - aabb2.max.x;
				tFirst = dFirst / (vel2.x - vel1.x);



			}
			if (aabb1.max.x < aabb2.min.x) //case 2 (2/2)
			{

				dLast = aabb1.max.x - aabb2.min.x;
				tLast = dLast / (vel2.x - vel1.x);

			}
			if (aabb1.max.x < aabb2.min.x) //case 3
			{
				return 0;
			}
			if (tFirst > GLHelper::delta_time)
			{
				return 0;
			}
		}
		//case 5:
		if (tFirst > tLast) { return 0; } //no collision


		/***************************************/
		// working with y-axis
		/***************************************/
		if ((vel2.y - vel1.y) < 0.f) //case 1 & 4
		{
			if (aabb1.min.y > aabb2.max.y) //case 1
			{
				return 0;
			}
			if (aabb1.max.y < aabb2.min.y) //case 4 revisited (1/2)
			{
				dFirst = aabb1.max.y - aabb2.min.y;
				tFirst = max((dFirst) / (vel2.y - vel1.y), tFirst);

			}
			if (aabb1.min.y < aabb2.max.y) //case 4 revisited (2/2)
			{

				dLast = aabb1.min.y - aabb2.max.y;
				tLast = min((dLast) / (vel2.y - vel1.y), tLast);
			}
		}
		if ((vel2.y - vel1.y) > 0.f) //case 2 & case 3
		{
			if (aabb1.min.y > aabb2.max.y) //case 2 (1/2)
			{
				dFirst = aabb1.min.y - aabb2.max.y;
				tFirst = max((dFirst) / (vel2.y - vel1.y), tFirst);



			}
			if (aabb1.max.y < aabb2.min.y) //case 2 (2/2)
			{

				dLast = aabb1.max.y - aabb2.min.y;
				tLast = min((dLast) / (vel2.y - vel1.y), tLast);

			}
			if (aabb1.max.y < aabb2.min.y) //case 3
			{
				return 0; //no intersection
			}
		}
		//case 5:
		if (tFirst > tLast) { return 0; } //no collision
		//std::cout << "Collision Detected!" << std::endl;
		return 1; //collision
	}
}