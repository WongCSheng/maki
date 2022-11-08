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
		ObjectPhysics->velocity.x = (float)((acceleration * GLHelper::delta_time) + preVel.x); //step1 .x
		ObjectPhysics->velocity.y = (float)((acceleration * GLHelper::delta_time) + preVel.y); //step1 .y


		/*update position based on velocity & previous position*/
		ObjectPhysics->position.x = (float)((1 / 2 * acceleration * GLHelper::delta_time * GLHelper::delta_time) +
			(ObjectPhysics->velocity.x * GLHelper::delta_time) + prePos.x);						//step2	.x	


		ObjectPhysics->position.y = (float)((1 / 2 * acceleration * GLHelper::delta_time * GLHelper::delta_time) +
			(ObjectPhysics->velocity.y * GLHelper::delta_time) + prePos.y);					//step2	.y


	}
}