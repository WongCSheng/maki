#ifndef VECTOR2_H
#define VECTOR2_H

class Vector2f
{
public:
	Vector2f();
	Vector2f(int x, int y);
	Vector2f(float x, float y);
	~Vector2f();

	float x, y;
};

#endif