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
double GLHelper::fps;
GLdouble GLHelper::delta_time;
std::string GLHelper::title;
GLFWwindow* GLHelper::ptr_window;

#define FRAME_TIME_MIN   1.0/60.0

bool GLHelper::init(GLint w, GLint h, std::string t) {
	GLHelper::width = w;
	GLHelper::height = h;
	GLHelper::title = t;

	// Part 1
	if (!glfwInit()) {
		std::cout << "GLFW init has failed - abort program!!!" << std::endl;
		return false;
	}

	// In case a GLFW function fails, an error is reported to callback function
	glfwSetErrorCallback(GLHelper::error_cb);

	// Before asking GLFW to create an OpenGL context, we specify the minimum constraints
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // major ver 4 (4.x)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5); //minor ver 5 (x.5)
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // show that opengl is forward compatible
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // opengl profile
	glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE); // enable double buffer
	glfwWindowHint(GLFW_RED_BITS, 8); glfwWindowHint(GLFW_GREEN_BITS, 8); // red and green both 8 bits each
	glfwWindowHint(GLFW_BLUE_BITS, 8); glfwWindowHint(GLFW_ALPHA_BITS, 8); // blue and alpha both 8 bits each
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE); // window dimensions are static

	GLHelper::ptr_window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL); // create window and context using variables from GLHelper::init
	if (!GLHelper::ptr_window) {
		std::cerr << "GLFW unable to create OpenGL context - abort program\n";
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(GLHelper::ptr_window); // make current window the context

	// first parameter represent the handle to the window (ptr_window) while 2nd paramter is the callback function

	glfwSetFramebufferSizeCallback(GLHelper::ptr_window, GLHelper::fbsize_cb);
	glfwSetCursorPosCallback(GLHelper::ptr_window, GLHelper::mousepos_cb);

	// this is the default setting ...
	glfwSetInputMode(GLHelper::ptr_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	// Part 2: Initialize entry points to OpenGL functions and extensions
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		std::cerr << "Unable to initialize GLEW - error: "
			<< glewGetErrorString(err) << " abort program" << std::endl;
		return false;
	}
	if (GLEW_VERSION_4_3) {
		std::cout << "Using glew version: " << glewGetString(GLEW_VERSION) << std::endl;
		std::cout << "Driver supports OpenGL 4.5\n" << std::endl;
	}
	else {
		std::cerr << "Driver doesn't support OpenGL 4.5 - abort program" << std::endl;
		return false;
	}

	return true;
}
/*  _________________________________________________________________________ */
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

	// update fps at least every 10 seconds ...
	fps_calc_interval = (fps_calc_interval < 0.0) ? 0.0 : fps_calc_interval;
	fps_calc_interval = (fps_calc_interval > 10.0) ? 10.0 : fps_calc_interval;
	if (elapsed_time > fps_calc_interval) {
		GLHelper::fps = static_cast<GLint>(count / elapsed_time);
		start_time = curr_time;
		count = 0.0;
	}
}