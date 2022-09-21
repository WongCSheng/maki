/* !
@file		glhelper.h
@author  louishetong.wang@digipen.edu
@date		9/15/2022

This file contains the declaration of namespace Helper that encapsulates the
functionality required to create an OpenGL context using GLFW. Has keyboard inputs
as well.
*//*__________________________________________________________________________*/
#ifndef GLHELPER_H_
#define GLHELPER_H_

/*                                                                   includes
----------------------------------------------------------------------------- */
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

class GLHelper
{
public:
	//initialize window
	static bool init(GLint w, GLint h, std::string str);
	//clean up resources
	static void cleanup();
	//error handling
	static void error_cb(int error, char const* description);
	//resize window(If we are doing fullscreen)
	static void win_resize(GLFWwindow* ptr_window, int w, int h);
	//key callback when a key is pressed/hold/released
	static void key_cb(GLFWwindow* pwin, int key, int scancode, int action, int mod);
	//mouse button callback when mouseclick is pressed
	static void mouse_cb(GLFWwindow* ptr_window, int mouse, int action, int mod);
	//function will return mouse position coordinates
	static void mousepos_cb(GLFWwindow* ptr_window, double x_coord, double y_coord);
	//update fps
	static void fps_counter(double interval = 1.0f);
	//printing of system specs
	static void print_specs();

	static GLFWwindow* ptr_window;
	//arrow keys
	static GLboolean keystateW;
	static GLboolean keystateS;
	static GLboolean keystateA;
	static GLboolean keystateD;

	static GLboolean right_click;

	static GLint width;
	static GLint height;
	static GLfloat fps;
	static std::string title;
	static double delta_time;
	
};
#endif GLHELPER_H_