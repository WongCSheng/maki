#include "DirectionLight.h"
#include "Entity.h"
#include "Transform.h"

DirectionLight::DirectionLight() :
target(0, 0, 0)
{
}


DirectionLight::~DirectionLight()
{
}

void DirectionLight::Update(const double dt)
{
	position = owner->transform->worldposition;
}

void DirectionLight::Set(Vector3 target, Vector3 color, float ambientIntensity, float diffuseIntensity)
{
	this->target = target;
	this->color = color;
	this->ambientIntensity = ambientIntensity;
	this->diffuseIntensity = diffuseIntensity;
}

Vector3 DirectionLight::GetDirection(void)
{
	direction = target - position;
	return direction;
}

Matrix4f DirectionLight::GetTransformMat(void)
{
	return owner->transform->TransformMat();
}

Matrix4f DirectionLight::GetViewMat(void)
{
	Matrix4f view;
	view.SetToIdentity();
	view.SetToLookAt(position.x, position.y, position.z,
		target.x, target.y, target.z, 0.0, 1.0, 0.0);

	return view;
}