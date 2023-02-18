//******************************************************************************/
/*!
\file		Collision.cpp
\author 	Thea Sea
\par    	email: thea.sea@digipen.edu
\author 	Aurelia Chong
\par    	email: fei.x@digipen.edu
\date   	2/8/2022
\brief		This source file contains the function definitions for
			building line segment, checking for collision between line segment
			and circles, and the response when collision occurs.

Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#include "collision.h"
#include "../Engine/TileMap/Map.h"

namespace Core
{
	collision::collision()
	{

	}

	collision::~collision()
	{

	}

	void collision::Init()
	{

	}

	bool collision::IsActive()
	{
		return active;
	}

	void collision::Activate()
	{
		active = true;
	}

	void collision::Deactivate()
	{
		active = false;
	}

	void collision::Remove()
	{
		remove = true;
	}

	bool collision::checkleft()
	{
		return collide_left;
	}

	bool collision::checkright()
	{
		return collide_right;
	}

	bool collision::checkdown()
	{
		return collide_bottom;
	}

	bool collision::checkup()
	{
		return collide_top;
	}

	void collision::collided_left(bool result)
	{
		collide_left = result;
	}

	void collision::collided_right(bool result)
	{
		collide_right = result;
	}

	void collision::collided_bottom(bool result)
	{
		collide_bottom = result;
	}

	void collision::collided_top(bool result)
	{
		collide_top = result;
	}

	void collision::Toggle_Stuck(bool result)
	{
		stuck = result;
	}

	bool collision::Is_it_Stuck()
	{
		return stuck;
	}
}