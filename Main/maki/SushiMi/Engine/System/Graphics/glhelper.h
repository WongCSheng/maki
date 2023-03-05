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
#include "../Headers/STL_Header.h"
#include "../Window/GameWindow.h"

/*  _________________________________________________________________________ */
struct GLHelper
{

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

	static void update_time(double fps_calc_interval);

};

#endif /* GLHELPER_H */

