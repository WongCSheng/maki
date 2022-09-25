/* !
@file		glhelper.h
@author		pghali@digipen.edu
@co-author  louishetong.wang@digipen.edu
@date		8/06/2022

This file contains the declaration of namespace Helper that encapsulates the
functionality required to create an OpenGL context using GLFW; use GLEW
to load OpenGL extensions; initialize OpenGL state; and finally initialize
the OpenGL application by calling initalization functions associated with
objects participating in the application.

*//*__________________________________________________________________________*/

/*                                                                      guard
----------------------------------------------------------------------------- */
#ifndef GLHELPER_H
#define GLHELPER_H

/*                                                                   includes
----------------------------------------------------------------------------- */
#include <GL/glew.h> // for access to OpenGL API declarations 
#include <GLFW/glfw3.h>
#include <string>
#include <../include/glapp.h>

/*  _________________________________________________________________________ */
struct GLHelper
	/*! GLHelper structure to encapsulate initialization stuff ...
	*/
{
	/*  _________________________________________________________________________ */
	/*! init

	@param GLint width
	@param GLint height
	Dimensions of window requested by program

	@param std::string title_str
	String printed to window's title bar

	@return bool
	true if OpenGL context and GLEW were successfully initialized.
	false otherwise.

	Uses GLFW to create OpenGL context. GLFW's initialization follows from here:
	http://www.glfw.org/docs/latest/quick.html
	a window of size width x height pixels
	and its associated OpenGL context that matches a core profile that is
	compatible with OpenGL 4.5 and doesn't support "old" OpenGL, has 32-bit RGBA,
	double-buffered color buffer, 24-bit depth buffer and 8-bit stencil buffer
	with each buffer of size width x height pixels
	*/
	static bool init(GLint w, GLint h, std::string t);
	/*  _________________________________________________________________________ */
	/*! cleanup

	@param none

	@return none

	For now, there are no resources allocated by the application program.
	The only task is to have GLFW return resources back to the system and
	gracefully terminate.
	*/
	static void cleanup();

	// callbacks ...
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
	static void error_cb(int error, char const* description);
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
	static void fbsize_cb(GLFWwindow* ptr_win, int width, int height);
	// I/O callbacks ...
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
	static void key_cb(GLFWwindow* pwin, int key, int scancode, int action, int mod);
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
	static void mousebutton_cb(GLFWwindow* pwin, int button, int action, int mod);
	/*  _________________________________________________________________________*/
	/*! mousescroll_cb

	@param GLFWwindow*
	Handle to window that is receiving event

	@param double
	Scroll offset along X-axis

	@param double
	Scroll offset along Y-axis

	@return none

	This function is called when the user scrolls, whether with a mouse wheel or
	touchpad gesture. Although the function receives 2D scroll offsets, a simple
	mouse scroll wheel, being vertical, provides offsets only along the Y-axis.
	*/
	static void mousescroll_cb(GLFWwindow* pwin, double xoffset, double yoffset);
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
	static void mousepos_cb(GLFWwindow* pwin, double xpos, double ypos);
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
	static void update_time(double fpsCalcInt = 1.0);

	static GLint width, height;
	static GLdouble fps;
	static GLdouble delta_time; // time taken to complete most recent game loop
	static std::string title;
	static GLFWwindow* ptr_window;
	/*  _________________________________________________________________________ */
	/*! print_specs()

	@param none

	@return none

	To print the specs of vendors, versions etc
	*/
	static void print_specs();
};

#endif /* GLHELPER_H */

