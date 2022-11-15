#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../../../lib/stb-master/stb_image.h"
#include <iostream>
#include "../../include/glhelper.h"
#include "../../include/glapp.h"
enum AnimationType
{
	Idle,
	Run,
	Jump
};

class Animation2D
{
public:
	static void init(const char* filename);
	//void draw();
	static void readKeyboard(GLFWwindow* window, float* x_direction, float* y_direction);

};

