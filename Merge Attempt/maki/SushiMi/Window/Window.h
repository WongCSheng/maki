#pragma once

#ifndef WINDOW_H_
#define WINDOW_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../Headers/STL_Header.h"
#include "../include/glhelper.h"

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