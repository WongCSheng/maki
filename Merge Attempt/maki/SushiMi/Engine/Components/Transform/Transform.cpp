

#include "Transform.h"
#include "../Engine/Components/Component.h"
#include "../Engine/System/Transformer.h"

Core::Transform::Transform()
{
}


Core::Transform::~Transform()
{
}

const gfxMatrix3& Core::Transform::TransformMat(void)
{
	return T * R * S;
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

const gfxVector2& Core::Transform::Forward(const double dt)
{
	return forward;
}