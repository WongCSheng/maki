#pragma once
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