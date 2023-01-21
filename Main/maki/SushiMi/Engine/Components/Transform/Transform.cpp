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

	void Transform::Serialize(const std::string name)
	{

	}

	void Transform::Deserialize(const std::string name)
	{

	}

	void Transform::Set(gfxVector2 position, gfxVector2 scale, gfxMatrix3 rotation)
	{
		this->Position = position;
		this->Scale = scale;
		this->Rotation = rotation;
	}

	void Transform::SetPosition(gfxVector2 position)
	{
		this->Position = position;
	}

	void Transform::SetScale(gfxVector2 scale)
	{
		this->Scale = scale;
	}

	void Transform::SetRotation(gfxMatrix3 rotation)
	{
		this->Rotation = rotation;
	}

	void Transform::Translating(gfxVector2 translate)
	{
		this->Position += translate;
	}

	void Transform::Rotating(gfxMatrix3 rotate)
	{
		Rotation *= rotate;
	}

	void Transform::Scaling(float scale)
	{
		Scale *= scale;
	}
}