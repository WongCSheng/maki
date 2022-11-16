/*!
@file		Window.h
@author		p.tzechengjennifer@digipen.edu
@date		28/09/2022

This file contains class Window that we will use for opening windows..
*//*__________________________________________________________________________*/

#pragma once

#ifndef GAMEWINDOW_H_
#define GAMEWINDOW_H_

#include "../Headers/STL_Header.h"
#include <GLFW/glfw3.h>
//#include "../Engine/System/Graphics/glhelper.h"

namespace Upfront
{
	class Window
	{
	public:
		Window();
		~Window();

		static void Win_Init();
		void CreateWin();
		
		int getWinWidth();
		int getWinHeight();

		inline static GLFWwindow* win = nullptr;
		inline static GLFWmonitor* monitor = nullptr;
		inline static HINSTANCE instance {0};

		inline static int winWidth{ 0 }, winHeight{ 0 },
			dispWidth{ 0 }, dispHeight{ 0 };

		inline static POINT mousePos{};

		inline static const char* titlebar{"Maki Engine"};
	};

	/*class Window_Message : public Message
	{

	};*/
}

#endif