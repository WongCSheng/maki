#pragma once
//******************************************************************************/
/*!
\file		Window.h
\author 	Thea Sea
\par    	email: thea.sea@digipen.edu
\co-author	Louis Wang (10%)
\par    	email: louishetong.wang@digipen.edu
\date   	2/8/2022
\brief		This source file contains the main function to call all other functions and implement the game loop.
			It instantiates player and sprites as well.

Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#include "../Game Object/Player.h"
#include "../Engine/Shaders/ShaderLibrary.h"
#include "../Engine/Camera/Camera.h"

#include "../Engine/Texture/Sprite.h"

#include <iostream>
#include <glfw/include/GLFW/glfw3.h>




class Window
{
public:
	Window(int width, int height);

	~Window();

	void Input();

	void Resize();

	void Mainloop();

	Player* player;
	Sprite* sp;
	Sprite* sp1;
	inline static GLFWwindow* window_ptr; //moved from private to public for access in main.cpp

private:
	int m_width, m_height;
	GLFWwindow* ptr_win;
	double starttime, endtime, delta;
};

class pseudomain
{
public:
	static void draw();
	static void update();
	static void init();
	static void cleanup();

};