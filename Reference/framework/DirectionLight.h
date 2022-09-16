#ifndef DIRECTION_LIGHT_H
#define DIRECTION_LIGHT_H

#include "Component.h"
#include "Vector3.h"

class Matrix4f;
class DirectionLight :
	public Component
{
public:
	DirectionLight();
	virtual ~DirectionLight();

	virtual void Update(const double dt);
	void Set(Vector3 target = Vector3(0, 0, 0), Vector3 color = Vector3(1, 1, 1), float ambientIntensity = 0, float diffuseIntensity = 0);
	Vector3 GetDirection(void);
	Matrix4f GetTransformMat(void);
	Matrix4f GetViewMat(void);

	Vector3 target;
	Vector3 color;
	float ambientIntensity;
	float diffuseIntensity;

private:
	Vector3 position;
	Vector3 direction;
};

#endif