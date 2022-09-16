#include "Transform.h"
#include "Entity.h"

Transform::Transform() :
localscale(1, 1, 1),
forward(DEFAULTFORWARD),
parent(NULL)
{
}

Transform::~Transform()
{
}

const Matrix4f& Transform::TransformMat(void)
{
	return Top;
}

void Transform::Set(Vector3 position, Vector3 scale, Quaternion rotation)
{
	this->localposition = position;
	this->localscale = scale;
	this->localrotation = rotation;
}

void Transform::SetPosition(Vector3 position)
{
	this->localposition = position;
}

void Transform::SetScale(Vector3 scale)
{
	this->localscale = scale;
}

void Transform::SetRotation(Quaternion rotation)
{
	this->localrotation = rotation;
}

void Transform::SetForward(Vector3 forward)
{
	this->forward = forward;
}

void Transform::Translate(Vector3 translate)
{
	this->localposition += translate;
}

void Transform::Rotate(Quaternion rotate)
{
	localrotation = localrotation * rotate;
}

void Transform::Scale(float scale)
{
	this->localscale *= scale;
}

const Vector3& Transform::Forward()
{
	return forward;
}