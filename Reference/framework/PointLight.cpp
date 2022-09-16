#include "PointLight.h"
#include "Entity.h"
#include "Transform.h"
#include <iostream>

PointLight::PointLight() :
position(0, 0, 0),
color(1, 1, 1),
ambientIntensity(0.2f),
diffuseIntensity(0.6f)
{
	atten.Constant = 1;
	atten.Linear = 0.35f;
	atten.Exp = 0.44f;
}

PointLight::~PointLight()
{
}

void PointLight::Update(const double dt)
{
	position = owner->transform->worldposition;
}

void PointLight::Set(Vector3 color, float ambientIntensity, float diffuseIntensity)
{
	this->color = color;
	this->ambientIntensity = ambientIntensity;
	this->diffuseIntensity = diffuseIntensity;

	float BSphereScale = CalcPointLightBSphere();
	owner->transform->SetScale(Vector3::Splat(BSphereScale));

	this->transform = owner->transform;
}

void PointLight::SetAttenuation(float Constant, float Linear, float Exp)
{
	this->atten.Constant = Constant;
	this->atten.Linear = Linear;
	this->atten.Exp = Exp;
}

Matrix4f PointLight::GetTransformMat(void)
{
	return owner->transform->TransformMat();
}

float PointLight::CalcPointLightBSphere(void)
{
	float MaxChannel = fmax(fmax(color.x, color.y), color.z);

	float ret = (-atten.Linear + sqrtf(atten.Linear * atten.Linear - 4 * atten.Exp * (atten.Exp - 256 * MaxChannel * diffuseIntensity)))
		/
		(2 * atten.Exp);

	return ret;
}