#pragma once
<<<<<<< HEAD

#include "../Headers/STL_Header.h"
#include "Keys.h"
#include <glfw/include/GLFW/glfw3.h>
=======
/******************************************************************************/
/*!
\file		Input.h
\author 	Aurelia Chong
\par    	email: fei.x@digipen.edu
\date   	16 Nov 2022
\brief		This file contains functions that are related to keys and user inputs.

Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
*/
/******************************************************************************/
#include "../Headers/STL_Header.h"
#include "Keys.h"
#include <GLFW/glfw3.h>
>>>>>>> M3-submission-branch
#include "../Engine/System/SystemFrame.h"
#include "../Headers/Math_Header.h"

namespace Core
{
	class Input
	{
	public:
		/*static Input& Instance()
		{
			if (instance != 0)
			{
				return *instance;
			}
			instance = new Input();
			return *instance;
		}*/

		Input();
		~Input();

		void Init();

		void UpdateInput(const KEY key, const KEY_STATE action);
		bool GetKey(const KEY key, const KEY_STATE action);
		bool GetKeyDown(const KEY key);
		gfxVector2 GetMouse(GLFWwindow* window, int action);

	private:
		/*Input();
		~Input();*/

		//static Input* instance;
		std::map<KEY, std::map<KEY_STATE, bool>> keys;
		std::queue<KEY> keyqueue;
	};
}