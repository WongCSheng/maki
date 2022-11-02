//******************************************************************************/
/*!
\file		Transform.cpp
\author 	Wong Chong Sheng
\email    	w.chongsheng@digipen.edu
\date   	25/10/2022
\brief		Transform component for GameObjects.

Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 //******************************************************************************/

#include "Transform.h"
#include "../Engine/Components/Component.h"
#include "../Engine/System/Transformer.h"

Core::Transform::Transform()
{
	owner = nullptr;
	instance = nullptr;
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