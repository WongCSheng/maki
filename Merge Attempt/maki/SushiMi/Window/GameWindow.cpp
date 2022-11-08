/*!
@file		Window.cpp
@author		p.tzechengjennifer@digipen.edu
@date		28/09/2022

This file contains functions for class Window that we will use for opening windows.
*//*__________________________________________________________________________*/

#include "../include/glhelper.h"	//GLEW first
#include "GameWindow.h"				//GLFW second

Upfront::Window::Window()
{
	mousePos = { 0, 0 };
	win = nullptr;
	monitor = nullptr;
	instance = nullptr;

	winWidth = winHeight = dispWidth = dispHeight = 0;
	titlebar = nullptr;
}

Upfront::Window::~Window()
{
}

void Upfront::Window::Win_Init()
{
	monitor = glfwGetPrimaryMonitor();
	
	titlebar = "Maki_Engine";

	glfwGetMonitorPhysicalSize(monitor, &dispWidth, &dispHeight);
	
	win = glfwCreateWindow(1280, 720, titlebar, NULL, NULL); // 720p resolution for now

	if (!GLHelper::init(1280, 720, "Maki Game Engine")) {
		std::cout << "Unable to create OpenGL context" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	glViewport(0, 0, 1280, 720); // 70 resolution for now

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Upfront::Window::CreateWin()
{
}

int Upfront::Window::getWinWidth()
{
	return winWidth;
}

int Upfront::Window::getWinHeight()
{
	return winHeight;
}
