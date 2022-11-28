/*
File: Transform.cpp
Author: w.chongsheng@digipen.edu
Description: Contains data for every type of transform. From meshes, bounding boxes, camera etc.
*/

#include "Transform.h"
#include "../Engine/Components/Component.h"
#include "../Engine/System/Transformer.h"

namespace Core
{
	Transform::Transform()
	{
	}


	Transform::~Transform()
	{
	}

	void Transform::Init()
	{

	}

	void Transform::Serialise(const std::string name)
	{

	}

	const gfxMatrix3 Transform::TransformMat(void)
	{
		return T * R * S;
	}

	void Transform::Set(gfxVector2 position, gfxVector2 scale, gfxMatrix3 rotation)
	{
		this->localposition = position;
		this->localscale = scale;
		this->localrotation = rotation;
	}

	void Transform::SetPosition(gfxVector2 position)
	{
		this->localposition = position;
	}

	void Transform::SetScale(gfxVector2 scale)
	{
		this->localscale = scale;
	}

	void Transform::SetRotation(gfxMatrix3 rotation)
	{
		this->localrotation = rotation;
	}

	void Transform::SetForward(gfxVector2 forward)
	{
		this->forward = forward;
	}

	void Transform::Translate(gfxVector2 translate)
	{
		this->localposition += translate;
	}

	void Transform::Rotate(gfxMatrix3 rotate)
	{
		localrotation = localrotation * rotate;
	}

	void Transform::Scale(float scale)
	{
		this->localscale *= scale;
	}

	const gfxVector2& Transform::Forward(const double dt)
	{
		return forward;
	}
}