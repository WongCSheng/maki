#pragma once
#include "../include/common_headers.hpp"


glm::vec2 gravity(-9.81, 0); //applying gravity to x axis

glm::vec2 applyGravity(float mass)
{
	return gravity * mass;
}


