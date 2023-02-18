/******************************************************************************/
/*!
\file		Collision.h
\author 	Thea Sea
\par    	email: thea.sea@digipen.edu
\author 	Aurelia Chong
\par    	email: fei.x@digipen.edu
\date   	2/8/2022
\brief		This source file contains the function declarations for
			building line segment, checking for collision between line segment
			and circle instances, and lastly the response when collision occurs.

Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#ifndef _COLLISION_H_
#define _COLLISION_H_

#include "../Headers/STL_Header.h"
#include "../Headers/Math_Header.h"
#include "../Engine/System/Graphics/glhelper.h"
#include "../Component.h"

namespace Core
{
	enum class wall_type;
	enum class ingredients;

	class Map;
	
	class collision : public Component
	{
	public:
		
		collision();
		virtual ~collision();

		void Init();

		bool IsActive();
		void Activate();
		void Deactivate();
		void Remove();

		bool checkleft();
		bool checkright();
		bool checkdown();
		bool checkup();

		void collided_left(bool result);
		void collided_right(bool result);
		void collided_bottom(bool result);
		void collided_top(bool result);

		void Toggle_Stuck(bool result);
		bool Is_it_Stuck();

		unsigned int Grid_Pos_x, Grid_Pos_y;

	private:
		bool stuck,
			collide_left, collide_right, collide_bottom, collide_top;
	};
}

#endif // CSD1130_COLLISION_H_