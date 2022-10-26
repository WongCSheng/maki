#pragma once
#include "../include/common_headers.hpp"


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


