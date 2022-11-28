/******************************************************************************/
/*!
\file		Input.h
\author 	Aurelia Chong
\par    	email: fei.x@digipen.edu
\date   	16 Nov 2022
\brief		This file contains functions header files for input.cpp

Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
*/
/******************************************************************************/
#include "Input.h"

namespace Core
{
	/******************************************************************************/
	/*!
	\brief
			Input constructor (constructor to load all the keys)

	*/
	/******************************************************************************/

	//Input* Input::instance = 0;
	Input::Input()
	{
		/******************************************************************************/
		/*!
		\brief
			loop through all keys in ASCII character, set them to default false state(key not pressed)

		*/
		/******************************************************************************/
		for (int i = 0; i <= 86; ++i)
		{
			keys[(KEY)(i)][KEY_STATE_RELEASE] = false;
			keys[(KEY)(i)][KEY_STATE_PRESS] = false;
			keys[(KEY)(i)][KEY_STATE_REPEAT] = false;
		}

		keys[(KEY)(999)][KEY_STATE_RELEASE] = false;
		keys[(KEY)(999)][KEY_STATE_PRESS] = false;
		keys[(KEY)(999)][KEY_STATE_REPEAT] = false;
	}

	/******************************************************************************/
	/*!
	\brief
			key destructor

	*/
	/******************************************************************************/
	Input::~Input()
	{
		keys.clear();
	}

	void Input::Init()
	{

	}

	/******************************************************************************/
	/*!
	\brief
			Checks for key state

	\param 
			const KEY key, const KEY_STATE action

	\return
				void
	*/
	/******************************************************************************/
	void Input::UpdateInput(const KEY key, const KEY_STATE action)
	{
		if (keyqueue.size() > 0)
		{
			keys[keyqueue.front()][KEY_STATE_RELEASE] = false;
			keyqueue.pop();
		}

		if (action != KEY_STATE_RELEASE)
		{
			keys[key][action] = true;
			keyqueue.push(key);
		}
		else
		{
			keys[key][KEY_STATE_PRESS] = false;
			keys[key][KEY_STATE_REPEAT] = false;
		}
	}

	/******************************************************************************/
	/*!
	\brief
			Get input key

	\param
			const KEY key, const KEY_STATE action

	\return
				bool
	*/
	/******************************************************************************/
	bool Input::GetKey(const KEY key, const KEY_STATE action)
	{
		return keys[key][action];
	}

	/******************************************************************************/
	/*!
	\brief
			check if a key is held down

	\param
			const KEY key, const KEY_STATE action

	\return
				bool
	*/
	/******************************************************************************/
	bool Input::GetKeyDown(const KEY key)
	{
		if (keys[key][KEY_STATE_PRESS] || keys[key][KEY_STATE_REPEAT])
		{
			return true;
		}
		return false;
	}
	
	/******************************************************************************/
	/*!
	\brief
			GetMouse

	\param
			const KEY key, const KEY_STATE action

	\return
				void
	*/
	/******************************************************************************/
	void Input::GetMouse(GLFWwindow* window, int action)
	{
		if (/*mouse == MOUSE_BUTTON_LEFT &&*/ action == KEY_STATE_PRESS)
		{
			double xpos, ypos;
			glfwGetCursorPos(window, &xpos, & ypos);
			std::cout << "Coursor position at " << xpos << " : " << ypos;
		}
	}
}