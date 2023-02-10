<<<<<<< HEAD

=======
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
>>>>>>> M3-submission-branch
#include "Input.h"

namespace Core
{
	//Input* Input::instance = 0;

<<<<<<< HEAD
	//constructor to load all the keys
	Input::Input()
	{
		//loop through all keys in ASCII character, set them to default false state(key not pressed)
=======
	/******************************************************************************/
	/*!
	\brief
			Input constructor (constructor to load all the keys)
	*/
	/******************************************************************************/
	Input::Input()
	{
		/******************************************************************************/
		/*!
		\brief
			loop through all keys in ASCII character, set them to default false state(key not pressed)
		*/
		/******************************************************************************/
>>>>>>> M3-submission-branch
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

<<<<<<< HEAD
	//key destructor
=======
	/******************************************************************************/
	/*!
	\brief
			key destructor
	*/
	/******************************************************************************/
>>>>>>> M3-submission-branch
	Input::~Input()
	{
		keys.clear();
	}

	void Input::Init()
	{
<<<<<<< HEAD
	}

=======

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
>>>>>>> M3-submission-branch
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

<<<<<<< HEAD
	//return true when checking a key is pressed
=======
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
>>>>>>> M3-submission-branch
	bool Input::GetKey(const KEY key, const KEY_STATE action)
	{
		return keys[key][action];
	}

<<<<<<< HEAD
	//check if a key is held down
=======
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
>>>>>>> M3-submission-branch
	bool Input::GetKeyDown(const KEY key)
	{
		if (keys[key][KEY_STATE_PRESS] || keys[key][KEY_STATE_REPEAT])
		{
			return true;
		}
		return false;
	}

<<<<<<< HEAD
=======
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
>>>>>>> M3-submission-branch
	gfxVector2 Input::GetMouse(GLFWwindow* window, int action)
	{
		double xpos, ypos;
		if (action == KEY_STATE_PRESS)
		{
			glfwGetCursorPos(window, &xpos, & ypos);
			gfxVector2 coordinates(xpos, ypos);
<<<<<<< HEAD
			//std::cout << "Coursor position at " << xpos << " : " << ypos << std::endl;
=======
			//std::cout << "Cursor position at " << xpos << " : " << ypos << std::endl;
>>>>>>> M3-submission-branch
			return coordinates;
		}
		return gfxVector2(0, 0);
	}
}