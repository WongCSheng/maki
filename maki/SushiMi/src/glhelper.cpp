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
#include <../include/glhelper.h>
#include "../object.h"
#include <../Camera2D.h>
#include <../object.h>
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
/*! init

@param GLint width
@param GLint height
@param std::string title_str

@return bool
true if OpenGL context and GLEW were successfully initialized.
false otherwise.

Uses GLFW to create OpenGL context with a window of size width x height pixels.
*/
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
	glfwSetKeyCallback(GLHelper::ptr_window, GLHelper::key_cb);
	glfwSetMouseButtonCallback(GLHelper::ptr_window, GLHelper::mousebutton_cb);
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
/*! key_cb

@param GLFWwindow*
Handle to window that is receiving event

@param int
the keyboard key that was pressed or released

@parm int
Platform-specific scancode of the key

@parm int
GLFW_PRESS, GLFW_REPEAT or GLFW_RELEASE
action will be GLFW_KEY_UNKNOWN if GLFW lacks a key token for it,
for example E-mail and Play keys.

@parm int
bit-field describing which modifier keys (shift, alt, control)
were held down

@return none

This function is called when keyboard buttons are pressed.
When the ESC key is pressed, the close flag of the window is set.
*/
void GLHelper::key_cb(GLFWwindow* pwin, int key, int scancode, int action, int mod) {
	
	/* for object physics implementation*/
	if (GLFW_PRESS == action && key == GLFW_KEY_RIGHT)
	{
		Object::objects["BaMi"].position.x += 50.0f;
		std::cout << "Physics: Moving a circle object right" << std::endl;
	}
	if (GLFW_PRESS == action && key == GLFW_KEY_LEFT)
	{
		Object::objects["BaMi"].position.x -= 50.0f;
		std::cout << "Physics: Moving a circle object left" << std::endl;
	}
	if (GLFW_PRESS == action && key == GLFW_KEY_DOWN)
	{
		Object::objects["BaMi"].position.y -= 50.0f;
		std::cout << "Physics: Moving a circle object down" << std::endl;
	}
	if (GLFW_PRESS == action && key == GLFW_KEY_UP)
	{
		Object::objects["BaMi"].position.y += 50.0f;
		std::cout << "Physics: Moving a circle object up" << std::endl;
	}

	/* for object6's rotation implementation*/
	/* the lower right rectangle*/
	// press J to rotate right faster, press K to rotate left
	if (GLFW_PRESS == action && key == GLFW_KEY_J)
	{
		Object::objects["Object6"].rot_left = GL_TRUE;
	}
	if (GLFW_PRESS == action && key == GLFW_KEY_K)
	{
		Object::objects["Object6"].rot_right = GL_TRUE;
	}

	/* for object6's scaling implementation*/
	// Press M to scale upm press N to scale down
	if (GLFW_PRESS == action && key == GLFW_KEY_M)
	{
		Object::objects["Object6"].scale_up = GL_TRUE;
	}
	if (GLFW_PRESS == action && key == GLFW_KEY_N)
	{
		Object::objects["Object6"].scale_down = GL_TRUE;
	}

	//for camera physics
	if (GLFW_PRESS == action && key == GLFW_KEY_V)
	{
		Camera2D::camera2d.camtype_flag = GL_TRUE;
	}
	if (GLFW_PRESS == action && key == GLFW_KEY_Z)
	{
		Camera2D::camera2d.zoom_flag = GL_TRUE;
	}
	if (GLFW_PRESS == action && key == GLFW_KEY_A)
	{
		Camera2D::camera2d.left_turn_flag = GL_TRUE;
	}
	if (GLFW_PRESS == action && key == GLFW_KEY_D)
	{
		Camera2D::camera2d.right_turn_flag = GL_TRUE;
	}
	if (GLFW_PRESS == action && key == GLFW_KEY_W)
	{
		Camera2D::camera2d.move_flag = GL_TRUE;
		Camera2D::camera2d.decelerate = GL_FALSE;
		if (GLFW_RELEASE == action)
		{
			Camera2D::camera2d.decelerate = GL_TRUE;
		}
	}
	
	else if (GLFW_RELEASE == action)
	{
		Camera2D::camera2d.camtype_flag = GL_FALSE;
		Camera2D::camera2d.zoom_flag = GL_FALSE;
		Camera2D::camera2d.left_turn_flag = GL_FALSE;
		Camera2D::camera2d.right_turn_flag = GL_FALSE;
		Camera2D::camera2d.move_flag = GL_FALSE;
		Object::objects["Object6"].rot_left = GL_FALSE;
		Object::objects["Object6"].rot_right = GL_FALSE;
		Object::objects["Object6"].scale_up = GL_FALSE;
		Object::objects["Object6"].scale_down = GL_FALSE;
	}

	

}

/*  _________________________________________________________________________*/
/*! mousebutton_cb

@param GLFWwindow*
Handle to window that is receiving event

@param int
the mouse button that was pressed or released
GLFW_MOUSE_BUTTON_LEFT and GLFW_MOUSE_BUTTON_RIGHT specifying left and right
mouse buttons are most useful

@parm int
action is either GLFW_PRESS or GLFW_RELEASE

@parm int
bit-field describing which modifier keys (shift, alt, control)
were held down

@return none

This function is called when mouse buttons are pressed.
*/
void GLHelper::mousebutton_cb(GLFWwindow* pwin, int button, int action, int mod) {

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
void GLHelper::mousepos_cb(GLFWwindow* pwin, double xpos, double ypos) {
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
void GLHelper::error_cb(int error, char const* description) {
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
void GLHelper::fbsize_cb(GLFWwindow* ptr_win, int width, int height) {
#ifdef _DEBUG
	std::cout << "fbsize_cb getting called!!!" << std::endl;
#endif
	// use the entire framebuffer as drawing region
	glViewport(0, 0, width, height);
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

	// update fps at least every 10 seconds ...
	fps_calc_interval = (fps_calc_interval < 0.0) ? 0.0 : fps_calc_interval;
	fps_calc_interval = (fps_calc_interval > 10.0) ? 10.0 : fps_calc_interval;
	if (elapsed_time > fps_calc_interval) {
		GLHelper::fps = count / elapsed_time;
		start_time = curr_time;
		count = 0.0;
	}
}
