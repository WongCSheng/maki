
#include "Transform.h"

Core::Transform::Transform() :
	localscale(1, 1),
	forward(DEFAULTFORWARD),
	parent(NULL)
{
}

Core::Transform::~Transform()
{
}

const gfxMatrix3& Core::Transform::TransformMat(void)
{
	return Top;
}

void Core::Transform::Set(gfxVector2 position, gfxVector2 scale, gfxMatrix3 rotation)
{
	this->localposition = position;
	this->localscale = scale;
	this->localrotation = rotation;
}

void Core::Transform::SetPosition(gfxVector2 position)
{
	this->localposition = position;
}

void Core::Transform::SetScale(gfxVector2 scale)
{
	this->localscale = scale;
}

void Core::Transform::SetRotation(gfxMatrix3 rotation)
{
	this->localrotation = rotation;
}

void Core::Transform::SetForward(gfxVector2 forward)
{
	this->forward = forward;
}

void Core::Transform::Translate(gfxVector2 translate)
{
	this->localposition += translate;
}

void Core::Transform::Rotate(gfxMatrix3 rotate)
{
	localrotation = localrotation * rotate;
}

void Core::Transform::Scale(float scale)
{
	this->localscale *= scale;
}

const gfxVector2& Core::Transform::Forward()
{
	return forward;
}