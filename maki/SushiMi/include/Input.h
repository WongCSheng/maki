/*!
@file    Input.h
@author	 Aurelia Chong

		 header files for input.cpp
*//*__________________________________________________________________________*/


#pragma once
#ifndef INPUT_H
#define INPUT_H

#include <map>
#include <queue>
#include "Keys.h"


/*                                                                      Class
----------------------------------------------------------------------------- */
class Input
{
public:
	static Input& Instance()
	{
		if (instance != 0)
		{
			return *instance;
		}
		instance = new Input();
		return *instance;
	}

	/*!				Input::Update(const KEY key, const KEY_STATE action)
	@param			const KEY key, const KEY_STATE action
	@return none

					Update input key pressed&released states
	*/

	void Update(const KEY key, const KEY_STATE action);
	/*!				bool Input::GetKey(const KEY key, const KEY_STATE action)
	@param			const KEY key, const KEY_STATE action
	@return			true/false

					return true/false depending on the key state pressed/released
	*/

	bool GetKey(const KEY key, const KEY_STATE action);
	/*!				bool Input::GetKeyDown(const KEY key)
	@param			const KEY key
	@return			true/false

				check if a key is held down
	*/
	bool GetKeyDown(const KEY key);


	/*!				Input::key_callback(GLFWwindow * window, int key, int scancode, int action, int mods)
	@param			GLFWwindow * window, int key, int scancode, int action, int mods
	@return none

					Link input keys to windows to display the outcome,added function from GLFW 
	*/
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

private:
	/*                                                                       Class
	----------------------------------------------------------------------------- */
	Input();
	~Input();

	/*                                                                     Instances
	----------------------------------------------------------------------------- */
	static Input* instance;
	std::map<KEY, std::map<KEY_STATE, bool>> keys;
	std::queue<KEY> keyqueue;
};

#endif