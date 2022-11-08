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
#include "../Engine/System/Graphics/glhelper.h"

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

		static GLFWwindow* win;
		static GLFWmonitor* monitor;
		static HINSTANCE instance;

		static int winWidth, winHeight,
			dispWidth, dispHeight;

		static POINT mousePos;

		static const char* titlebar;
	};

	/*class Window_Message : public Message
	{

	};*/
}

#endif