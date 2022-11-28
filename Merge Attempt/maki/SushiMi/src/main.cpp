//******************************************************************************/
/*!
\file		main.cpp
\author 	Thea Sea
\par    	email: thea.sea@digipen.edu
\date   	2/8/2022
\brief		This source file contains the main function to call all other functions and implement the game loop

Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/





/*                                                                   includes
----------------------------------------------------------------------------- */
// Extension loader library's header must be included before GLFW's header!!!
#include "../Headers/STL_Header.h"
#include "../Engine/Core/Core.h"
#include "../Window/GameWindow.h"
#include <memory> 
#include <crtdbg.h> 


/*                                                      function definitions
----------------------------------------------------------------------------- */
namespace Core
{
	/*  _________________________________________________________________________ */
/*! main

@param none

@return int

Indicates how the program existed. Normal exit is signaled by a return value of
0. Abnormal termination is signaled by a non-zero return value.
Note that the C++ compiler will insert a return 0 statement if one is missing.
*/
	int main() {

		// Enable run-time memory check for debug builds.
#if defined(DEBUG) | defined(_DEBUG)
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

		// Part 1
		/********************Renderer Stuff********************/
		Core::Renderer::Init();

		// Part 2
		while (!glfwWindowShouldClose(GLHelper::ptr_window)) {
			// Part 2a
			Core::Renderer::Update(GLHelper::delta_time);

			// Part 2b
			Core::Renderer::Draw();
		}
		//glfwSetKeyCallback(GLHelper::ptr_window, Input::key_callback);

		// Part 3
		Core::Renderer::Cleanup();
		/*******************Rednderer Stuff*********************/


	}
}