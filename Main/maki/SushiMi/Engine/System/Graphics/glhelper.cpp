/*!
@file		glhelper.cpp
@author		louishetong.wang@digipen.edu
@date		20/09/2022

This file implements functionality useful and necessary to build OpenGL
applications including use of external APIs such as GLFW to create a
window and start up an OpenGL context and use GLEW to extract function
pointers to OpenGL implementations.

*//*__________________________________________________________________________*/

/*                                                                   includes
----------------------------------------------------------------------------- */
#include "../Engine/System/Graphics/glhelper.h"
#include "../Game Object/GameObject.h"
#include "../Engine/Camera/Camera2D.h"
#include <iostream>

/*                                                   objects with file scope
----------------------------------------------------------------------------- */
// static data members declared in GLHelper
GLint GLHelper::width;
GLint GLHelper::height;
GLdouble GLHelper::fps;
GLdouble GLHelper::delta_time;
std::string GLHelper::title;
GLFWwindow* GLHelper::ptr_window;
/*  _________________________________________________________________________ */
/*! print_specs()

@param none

@return none

To print the specs of vendors, versions etc
*/
void GLHelper::print_specs()
{
	GLubyte const* str_ven = glGetString(GL_VENDOR); // gets the vendor name
	GLubyte const* str_ren = glGetString(GL_RENDERER); // gets the renderer name
	GLubyte const* str_ver = glGetString(GL_VERSION); // gets the version number of graphics driver
	GLubyte const* str_num = glGetString(GL_SHADING_LANGUAGE_VERSION); // gets the shading language version number

	std::cout << "GPU Vendor: " << str_ven << std::endl;
	std::cout << "GL Renderer: " << str_ren << std::endl;
	std::cout << "GL Version: " << str_ver << std::endl;
	std::cout << "GL Shader Version: " << str_num << std::endl;

	GLint maj_ver, min_ver, dbl_buffer, max_vertices, max_indices, tex_size, max_viewport_x[2], maxVertexAttributes, maxVertexBuffer;
	glGetIntegerv(GL_MAJOR_VERSION, &maj_ver); // Major ver num of OpenGL API
	glGetIntegerv(GL_MINOR_VERSION, &min_ver); // minor ver num of openGL API
	glGetIntegerv(GL_DOUBLEBUFFER, &dbl_buffer); // whether double buffer is enabled
	glGetIntegerv(GL_MAX_ELEMENTS_VERTICES, &max_vertices); // max num of array vertices
	glGetIntegerv(GL_MAX_ELEMENTS_INDICES, &max_indices); // max num of array indices
	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &tex_size); // max texture size
	glGetIntegerv(GL_MAX_VIEWPORT_DIMS, max_viewport_x); // max supported viewport
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &maxVertexAttributes); // max vertex attrib
	glGetIntegerv(GL_MAX_VERTEX_ATTRIB_BINDINGS, &maxVertexBuffer); // max vertex bindings

	std::cout << "GL Major Version: " << maj_ver << std::endl;
	std::cout << "GL Minor Version: " << min_ver << std::endl;
	if (dbl_buffer)
	{
		std::cout << "Current OpenGL Context is double buffered " << std::endl;
	}
	else
	{
		std::cout << "Current OpenGL Context is not double buffered " << std::endl;
	}
	std::cout << "Maximum Vertex Count: " << max_vertices << std::endl;
	std::cout << "Maximum Indices Count: " << max_indices << std::endl;
	std::cout << "GL Maximum texture size: " << tex_size << std::endl;
	std::cout << "Maximum Viewport Dimensions: " << max_viewport_x[0] << " x " << max_viewport_x[1] << std::endl;
	std::cout << "Maximum generic vertex attributes: " << maxVertexAttributes << std::endl;
	std::cout << "Maximum vertex buffer bindings: " << maxVertexBuffer << std::endl;


}

/*  _________________________________________________________________________ */
/*! cleanup

@param none

@return none

GLFW return resources back to the system and terminate.
*/
void GLHelper::cleanup() {
	// Part 1
	glfwTerminate();
}

/*  _________________________________________________________________________*/
/*! mousepos_cb

@param GLFWwindow*
Handle to window that is receiving event

@param double
new cursor x-coordinate, relative to the left edge of the client area

@param double
new cursor y-coordinate, relative to the top edge of the client area

@return none

This functions receives the cursor position, measured in screen coordinates but
relative to the top-left corner of the window client area.
*/
void GLHelper::mousepos_cb(GLFWwindow* /*pwin*/, double /*xpos*/, double /*ypos*/) {
#ifdef _DEBUG
	//std::cout << "Mouse cursor position: (" << xpos << ", " << ypos << ")" << std::endl;
#endif
}

/*  _________________________________________________________________________ */
/*! error_cb

@param int
GLFW error code

@parm char const*
Human-readable description of the code

@return none

The error callback receives a human-readable description of the error and
(when possible) its cause.
*/
void GLHelper::error_cb(int /*error*/, char const* description) {
#ifdef _DEBUG
	std::cerr << "GLFW error: " << description << std::endl;
#endif
}

/*  _________________________________________________________________________ */
/*! fbsize_cb

@param GLFWwindow*
Handle to window that is being resized

@parm int
Width in pixels of new window size

@parm int
Height in pixels of new window size

@return none

This function is called when the window is resized - it receives the new size
of the window in pixels.
*/
void GLHelper::fbsize_cb(GLFWwindow* /*ptr_win*/, int width_, int height_) {
#ifdef _DEBUG
	std::cout << "fbsize_cb getting called!!!" << std::endl;
#endif
	// use the entire framebuffer as drawing region
	glViewport(0, 0, width_, height_);
	// later, if working in 3D, we'll have to set the projection matrix here ...
}

/*  _________________________________________________________________________*/
/*! update_time

@param double
fps_calc_interval: the interval (in seconds) at which fps is to be
calculated

This function must be called once per game loop. It uses GLFW's time functions
to compute:
1. the interval in seconds between each frame
2. the frames per second every "fps_calc_interval" seconds
*/
void GLHelper::update_time(double fps_calc_interval) {
	// get elapsed time (in seconds) between previous and current frames
	static double prev_time = glfwGetTime();
	double curr_time = glfwGetTime();
	delta_time = curr_time - prev_time;
	prev_time = curr_time;

	// fps calculations
	static double count = 0.0; // number of game loop iterations
	static double start_time = glfwGetTime();
	// get elapsed time since very beginning (in seconds) ...
	double elapsed_time = curr_time - start_time;

	++count;

	if (elapsed_time > 1/60) {
		GLHelper::fps = count / elapsed_time;
		start_time = curr_time;
		count = 0.0;
	}
}
