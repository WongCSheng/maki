#include "Window.h"
#include <stdio.h>
#include <stdlib.h>

Window* Window::s_instance = 0;

Window::Window()
{
	width = 1024;
	height = 768;
	monWidth = 1024;
	monHeight = 768;
	title = "framework";
}

Window::~Window()
{
}

void Window::SetUp()
{
	InitMonitor();
	InitWindowHint();
	CreateWindow();
}

void Window::InitMonitor()
{
	myMonitor = glfwGetPrimaryMonitor();
	myMode = glfwGetVideoMode(myMonitor);

	monHeight = myMode->height;
	monWidth = myMode->width;
}

void Window::InitWindowHint()
{
	glfwWindowHint(GLFW_SAMPLES, 4); //Request 4x anti-aliasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //Request a specific OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //Request a specific OpenGL version
	//glfwWindowHint(GLFW_REFRESH_RATE, myMode->refreshRate);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //Have the latest OpenGL, not the old one
}

void Window::CreateWindow()
{
	window = glfwCreateWindow(width, height, title, NULL, NULL); //Create a window and create its OpenGL context

	glfwSetWindowPos(window, 100, 0);
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	
	//If the window couldn't be created.
	if (!window)
	{
		fprintf(stderr, "Failed to open the window. \n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	//This function makes the context of the specified window current on the calling thread.
	glfwMakeContextCurrent(window);
}


int Window::Width()
{
	return width;
}

int Window::Height()
{
	return height;
}