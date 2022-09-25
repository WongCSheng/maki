#pragma once
#include <GLFW/glfw3.h>
#include <glm/glm/fwd.hpp>
#include "include/common_headers.hpp"
#include "object.h"
#include "include/Math.h"
#ifndef CAMERA2D_H_
#define CAMERA2D_H_

class Camera2D
{
public:
	/*  _________________________________________________________________________ */
	/*! GLApp::Camera2D::init(GLFWwindow* pWindow, GLApp::GLObject* ptr)
	@param GLFWwindow* pWindow, GLApp::GLObject* ptr
	@return none

	Assign pgo to camera and compute aspect ratio, initialize as free camera.
	*/
	void init(GLFWwindow*, Object* ptr);

	/*  _________________________________________________________________________ */
	/*! GLApp::Camera2D::update(GLFWwindow*)
	@param GLFWwindow*
	@return none

	Update camera's ratio, orientation, position, up and right vectors, zoom and transformation matrices
	*/
	void update(GLFWwindow*);

	Object* pgo{}; // pointer to game obj that embeds the camera
	gfxVector2 right{}, up{};

	//additional parameters for camera
	GLint height{ 1000 };
	GLfloat ar{};

	gfxMatrix3 camwin_to_ndc_xform{}, world_to_ndc_xform{}, view_xform{};

	//window parameters
	GLint min_height{ 500 }, max_height{ 720 };
	// height is increasing if 1 and decreasing if -1
	GLint height_chg_dir{ 1 };
	// increments by which window height is changed per Z key press
	GLint height_chg_val{ 5 };

	// camera speed when button U is pressed
	GLfloat linear_speed{ 2.f };
	// Keyboard button press flags:
	GLboolean camtype_flag{ GL_FALSE }; // button V
	GLboolean zoom_flag{ GL_FALSE }; // button Z
	GLboolean left_turn_flag{ GL_FALSE }; // button H
	GLboolean right_turn_flag{ GL_FALSE }; // button K
	GLboolean move_flag{ GL_FALSE }; // button U
	static Camera2D camera2d;

};

#endif // !CAMERA2D_H_
