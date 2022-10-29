/*!
@file    Physics.cpp
@author	 Aurelia Chong

		 Manages game physics such as acceleration
*//*__________________________________________________________________________*/

#pragma once
#include "../include/common_headers.hpp"
#include <../object.h>

//glm::vec2 gravity(-9.81, 0); //applying gravity to x axis

// F = ma ; accel = F/m
float force = 50.f; // fixed force

//acceleration
float applyAccel(float mass) //input mass
{
	return force / mass;
}

float applyDecel(float mass) //deceleration for obj to stop
{
	return -force / mass;
}


////apply acceleration
//	glm::vec2 displacement = Object::objects["Object5"].position - Object::objects["Object5"].initialPos;



void updatePosition(Object& objectData)
{

	float acceleration = applyAccel(objectData.mass);	 //	stores acceleration

	// Updating the velocity and position according to acceleration is done by using the following:
	// step1: v1 = a*t + v0        //This is done when the UP or DOWN key is pressed 
	// step2: Pos1 = 1/2 * a*t*t + v0*t + Pos0
	// step3: Pos1 = v1t + Pos0

	gfxVector2 preVel = objectData.velocity;			 //	stores previous velocity/v0
	glm::vec2 prePos = objectData.position;				 //	stores previous position/p0

			/*update velocity based on previous velocity*/
	objectData.velocity.x = (acceleration * GLHelper::delta_time) + preVel.x; //step1 .x
	objectData.velocity.y = (acceleration * GLHelper::delta_time) + preVel.y; //step1 .y

	
	/*update position based on velocity & previous position*/
	objectData.position.x =	(1 / 2 * acceleration * GLHelper::delta_time * GLHelper::delta_time) +
								(objectData.velocity.x * GLHelper::delta_time) + prePos.x;						//step2	.x	


	objectData.position.y =	(1 / 2 * acceleration * GLHelper::delta_time * GLHelper::delta_time) +
								(objectData.velocity.y * GLHelper::delta_time) + prePos.y;					//step2	.y

	
}

