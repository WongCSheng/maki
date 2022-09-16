#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#include "Component.h"
#include "Vector3.h"

struct Attenuation
{
	float Constant;
	float Linear;
	float Exp;
};

class Matrix4f;
class Transform;
class PointLight :
	public Component
{
	friend class LightSystem;
public:
	PointLight();
	virtual ~PointLight();

	virtual void Update(const double dt);
	void Set(Vector3 color, float ambientIntensity, float diffuseIntensity);
	void SetAttenuation(float Constant, float Linear, float Exp);
	// Use fixed values from a table.
	// Distances: 7, 13, 20, 32, 50, 65, 100, 160, 200, 325, 600, 3250
	void SetAttenuation(int distance);	
	Matrix4f GetTransformMat(void);

	Vector3 position;
	Vector3 color;
	float ambientIntensity;
	float diffuseIntensity;
	Attenuation atten;

	Transform* transform;

private:
	float CalcPointLightBSphere(void);
};

#endif