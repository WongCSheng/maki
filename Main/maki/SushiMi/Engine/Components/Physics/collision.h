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
	enum class grid_number;

	class Sprite;
	
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

		void checkleft();
		void checkright();
		void checkdown();
		void checkup();

		std::unordered_map<wall_type, Sprite*> tilecontainer;
		std::unordered_map<grid_number, Sprite*> ingredientcontainer;
		std::unordered_map<grid_number, Sprite*> ingredient_starting_pos;
		unsigned int x, y;

		bool stuck;
	};
}

#endif // CSD1130_COLLISION_H_