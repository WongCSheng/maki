//******************************************************************************/
/*!
\file		LinkedList.h
\author 	Wong Chong Sheng
\email    	w.chongsheng@digipen.edu
\date   	25/10/2022
\brief		Header for LinkedList for GameObjects.

Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 //******************************************************************************/

#pragma once

namespace Core
{
	template<typename T>
	class LinkedList
	{
	private:
		T* left, * right;
		T* data;

	public:
		LinkedList();
		~LinkedList();

		/*T* AddLeft(T* child);
		T* AddRight(T* child);*/
	};
}