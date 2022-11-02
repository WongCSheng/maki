/*!
@file    Input.cpp
@author	 Aurelia Chong

		 Input funcrions checking for input key pressed & allowing users to press on inputs


/*		Copyright(C) 2022 DigiPen Institute of Technology.
		Reproduction or disclosure of this file or its contents without the
		prior written consent of DigiPen Institute of Technology is prohibited.
*//*__________________________________________________________________________*/

/*                                                                   includes
----------------------------------------------------------------------------- */
#include "../include/common_headers.hpp"

/*                                                                   Initialisation
----------------------------------------------------------------------------- */
Input* Input::instance = 0;


/*!				Input::key_callback(GLFWwindow * window, int key, int scancode, int action, int mods)
@param			GLFWwindow * window, int key, int scancode, int action, int mods
@return none

				Link input keys to windows to display the outcome
*/
void Input::key_callback(GLFWwindow * window, int key, int scancode, int action, int mods)
{
	if (key == KEY::KEY_E && action == GLFW_PRESS)
	{
		std::cout << "Key E is pressed" << std::endl;
	
	}
	if (action == GLFW_PRESS)
	{
		
		Input::Instance().keys[static_cast<KEY>(key)].operator[](KEY_STATE::KEY_STATE_PRESS) = true;
		std::cout << "Any key is pressed" << std::endl;

	}
}

/*                                                                 Construnctor
----------------------------------------------------------------------------- */
Input::Input()
{
	/*  
	loop through all keys in ASCII character, set them to default false state(key not pressed)
	----------------------------------------------------------------------------- */
	for (int i = 32; i <= 122; ++i)
	{
		keys[(KEY)(i)][KEY_STATE_RELEASE] = false;
		keys[(KEY)(i)][KEY_STATE_PRESS] = false;
		keys[(KEY)(i)][KEY_STATE_REPEAT] = false;
	}

	for (int i = 256; i <= 269; ++i)
	{
		keys[(KEY)(i)][KEY_STATE_RELEASE] = false;
		keys[(KEY)(i)][KEY_STATE_PRESS] = false;
		keys[(KEY)(i)][KEY_STATE_REPEAT] = false;
	}

	for (int i = 290; i <= 299; ++i)
	{
		keys[(KEY)(i)][KEY_STATE_RELEASE] = false;
		keys[(KEY)(i)][KEY_STATE_PRESS] = false;
		keys[(KEY)(i)][KEY_STATE_REPEAT] = false;
	}
}

/*                                                               Key destructor
----------------------------------------------------------------------------- */
Input::~Input()
{
	keys.clear();
}


/*!				Input::Update(const KEY key, const KEY_STATE action)
@param			const KEY key, const KEY_STATE action
@return none

				Update input key pressed&released states
*/
void Input::Update(const KEY key, const KEY_STATE action)
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

/*!				bool Input::GetKey(const KEY key, const KEY_STATE action)
@param			const KEY key, const KEY_STATE action
@return			true/false

				return true/false depending on the key state pressed/released
*/
bool Input::GetKey(const KEY key, const KEY_STATE action)
{
	return keys[key][action];
}

/*!				bool Input::GetKeyDown(const KEY key)
@param			const KEY key
@return			true/false

				check if a key is held down
*/
bool Input::GetKeyDown(const KEY key)
{
	if (keys[key][KEY_STATE_PRESS] || keys[key][KEY_STATE_REPEAT])
	{
		return true;
	}
	return false;
}