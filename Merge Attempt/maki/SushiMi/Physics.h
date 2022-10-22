#pragma once
#include "../Headers/Math_Header.h"
#include "../Headers/Graphics_Header.h"

#ifndef PHYSICS_H
#define PHYSICS_H

class PhysicsSystem {

public:
	void UpdateDynamics(float dt);
	void IntegrateForces(float dt);
	void IntegratePositions(float dt);
	glm::vec2 applyGravity(float mass);

};

class RigidBody {

public:


};


#endif