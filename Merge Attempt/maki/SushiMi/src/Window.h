#pragma once
#include "../Game Object/Player.h"
#include "../Engine/Shaders/ShaderLibrary.h"
#include "../Engine/Camera/Camera.h"

#include <iostream>
#include <glfw/include/GLFW/glfw3.h>
using namespace std;




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

private:
	int m_width, m_height;
	GLFWwindow* window_ptr;
	double starttime, endtime, delta;
};