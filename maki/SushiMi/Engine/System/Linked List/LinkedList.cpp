//******************************************************************************/
/*!
\file		LinkedList.cpp
\author 	Wong Chong Sheng
\email    	w.chongsheng@digipen.edu
\date   	25/10/2022
\brief		LinkedList for GameObjects.

Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 //******************************************************************************/

#include "LinkedList.h"

namespace Core
{
	template<typename T>
	LinkedList<T>::LinkedList()
	{
		left = right = data = nullptr;
	}

	template<typename T>
	LinkedList<T>::~LinkedList()
	{
		delete data;
		delete left;
		delete right;
	}
}