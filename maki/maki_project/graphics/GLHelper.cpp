/* !
@file		glhelper.h
@author  louishetong.wang@digipen.edu
@date		9/15/2022

This file contains the declaration of namespace Helper that encapsulates the
functionality required to create an OpenGL context using GLFW. Has keyboard inputs
as well.
*//*__________________________________________________________________________*/

/*                                                                   includes
----------------------------------------------------------------------------- */
#include "glhelper.h"
#include <iostream>

/*                                                   objects with file scope
----------------------------------------------------------------------------- */
// static data members declared in GLHelper

GLFWwindow* GLHelper::ptr_window;

GLint GLHelper::width;
GLint GLHelper::height;
GLfloat GLHelper::fps;
std::string GLHelper::title;
double GLHelper::delta_time;

GLboolean GLHelper::keystateW = GL_FALSE;
GLboolean GLHelper::keystateS = GL_FALSE;
GLboolean GLHelper::keystateA = GL_FALSE;
GLboolean GLHelper::keystateD = GL_FALSE;
GLboolean GLHelper::right_click = GL_FALSE;
/*  _________________________________________________________________________ */

//initialize window
bool GLHelper::init(GLint w, GLint h, std::string str)
{
	GLHelper::width = w;
	GLHelper::height = h;
	GLHelper::title = str;

	if (!glfwInit())
	{
		std::cout << "GLFW cannot be initialized, aborting program!";
	}
	return false;

	//if a GLFW function fails, error callback
	glfwSetErrorCallback(GLHelper::error_cb);

	//specify minimum requirements
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // major ver 4 (4.x)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5); //minor ver 5 (x.5)
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // show that opengl is forward compatible
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // opengl profile
	glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE); // enable double buffer
	glfwWindowHint(GLFW_RED_BITS, 8); glfwWindowHint(GLFW_GREEN_BITS, 8); // red and green both 8 bits each
	glfwWindowHint(GLFW_BLUE_BITS, 8); glfwWindowHint(GLFW_ALPHA_BITS, 8); // blue and alpha both 8 bits each
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE); // window dimensions are static

	//create window
	GLHelper::ptr_window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	if (!GLHelper::ptr_window) {
		std::cerr << "GLFW unable to create OpenGL context - abort program\n";
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(GLHelper::ptr_window); // make current window the context

// first parameter represent the handle to the window (ptr_window) while 2nd paramter is the callback function
	glfwSetFramebufferSizeCallback(GLHelper::ptr_window, GLHelper::win_resize);
	glfwSetKeyCallback(GLHelper::ptr_window, GLHelper::key_cb);
	glfwSetMouseButtonCallback(GLHelper::ptr_window, GLHelper::mouse_cb);
	glfwSetCursorPosCallback(GLHelper::ptr_window, GLHelper::mousepos_cb);

	// this is the default setting ...
	glfwSetInputMode(GLHelper::ptr_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	GLenum err = glewInit();
	if (GLEW_OK != err) {
		std::cerr << "Unable to initialize GLEW - error: "
			<< glewGetErrorString(err) << " abort program" << std::endl;
		return false;
	}
	if (GLEW_VERSION_4_5) {
		std::cout << "Using glew version: " << glewGetString(GLEW_VERSION) << std::endl;
		std::cout << "Driver supports OpenGL 4.5\n" << std::endl;
	}
	else {
		std::cerr << "Driver doesn't support OpenGL 4.5 - abort program" << std::endl;
		return false;
	}

	return true;
}
//clean up resources
void GLHelper::cleanup()
{
	glfwTerminate();
}
//error handling
void GLHelper::error_cb(GLint error, char const* description)
{
	std::cerr << "GLFW Error:" << description << std::endl;
}
//resize window(If we are doing fullscreen)
void GLHelper::win_resize(GLFWwindow* ptr_window, int w, int h)
{
	//use entire framebuffer to draw
	glViewport(0, 0, w, h);
}
//key callback when a key is pressed/hold/released
void GLHelper::key_cb(GLFWwindow* pwin, int key, int scancode, int action, int mod)
{
	//example of keypress
	if (GLFW_PRESS == action && key == GLFW_KEY_W)
	{
		GLHelper::keystateW = GL_TRUE;
	}
	else if (GLFW_RELEASE == action)
	{
		GLHelper::keystateW = GL_FALSE;
	}
}
//mouse button callback when mouseclick is pressed
void GLHelper::mouse_cb(GLFWwindow* ptr_window, int mouse, int action, int mod)
{
	//example of right click
	if (GLFW_PRESS == action && mouse == GLFW_MOUSE_BUTTON_RIGHT)
	{
		GLHelper::right_click = GL_TRUE;
	}
	else if (GLFW_RELEASE == action)
	{
		GLHelper::right_click = GL_FALSE;
	}
}
//function will return mouse position coordinates
void GLHelper::mousepos_cb(GLFWwindow* ptr_window, double x_coord, double y_coord)
{
#ifdef _DEBUG
	std::cout << "Mouse cursor position: " << x_coord << ", " << y_coord << std::endl;
#endif // DEBUG

}
//update fps
void GLHelper::fps_counter(double interval)
{
	//time elapse from current time to previous time
	double prev_time = glfwGetTime();
	double curr_time = glfwGetTime();

	GLHelper::delta_time = curr_time - prev_time;
	prev_time = curr_time;

	//calculate fps
	double count = 0;
	double start_time = glfwGetTime();

	double elapsed_time = curr_time - start_time;
	count++;

	//update fps every 10 second
	interval = (interval < 0.0) ? 0.0 : interval;
	interval = (interval > 10.0) ? 10.0 : interval;
	if (elapsed_time > interval)
	{
		GLHelper::fps = count / elapsed_time;
		start_time = curr_time;
		count = 0.0;
	}
}
//printing of system specs for debugging
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

	GLint maj_ver, min_ver, dbl_buffer, max_vertices, max_indices, tex_size, max_viewport_x[2], maxVertexAttributes, maxVertexBuffer, maxTex, maxTex_vert, maxTex_frag;
	glGetIntegerv(GL_MAJOR_VERSION, &maj_ver); // Major ver num of OpenGL API
	glGetIntegerv(GL_MINOR_VERSION, &min_ver); // minor ver num of openGL API
	glGetIntegerv(GL_DOUBLEBUFFER, &dbl_buffer); // whether double buffer is enabled
	glGetIntegerv(GL_MAX_ELEMENTS_VERTICES, &max_vertices); // max num of array vertices
	glGetIntegerv(GL_MAX_ELEMENTS_INDICES, &max_indices); // max num of array indices
	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &tex_size); // max texture size
	glGetIntegerv(GL_MAX_VIEWPORT_DIMS, max_viewport_x); // max supported viewport
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &maxVertexAttributes); // max vertex attrib
	glGetIntegerv(GL_MAX_VERTEX_ATTRIB_BINDINGS, &maxVertexBuffer); // max vertex bindings
	glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &maxTex);
	glGetIntegerv(GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS, &maxTex_vert);
	glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &maxTex_frag);

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
	std::cout << "Maximum number of generic vertex attributes: " << maxVertexAttributes << std::endl;
	std::cout << "Maximum number of vertex buffer binding points: " << maxVertexBuffer << std::endl;
}