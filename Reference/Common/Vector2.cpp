#include "Vector2.h"


Vector2f::Vector2f() :
x(0),
y(0)
{
}

Vector2f::Vector2f(int x, int y)
{
	this->x = (float)(x);
	this->y = (float)(y);
}

Vector2f::Vector2f(float x, float y)
{
	this->x = x;
	this->y = y;
}

Vector2f::~Vector2f()
{
}
