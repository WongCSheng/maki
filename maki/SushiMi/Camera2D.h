#pragma once
/*!
@file		Camera2D.h
@author		louishetong.wang@digipen.edu
@date		20/09/2022

This file implements functionality for the 2D Camera. Main functions include the initialization
and the updating of the camera's position,rotation and scaling.
There are a lot of matrices and vectors being used. Was previously using my own created
vector and matrix library but there were many errors so temporarily using glm's vector and
matrix library for now. Links to GLHelper for the keypresses like rotation and zooming in.
*//*__________________________________________________________________________*/
#ifndef CAMERA2D_H_
#define CAMERA2D_H_
/*                                                                   includes
----------------------------------------------------------------------------- */
#include <glm/glm/fwd.hpp>
#include "include/Math.h"
#include "include/Vector.h"
#include <glm/glm/trigonometric.hpp>
#include <GLFW/glfw3.h>
#include "include/Matrix.h"
/*--------------------------------------------------------------------------- */
class Object;

class Camera2D
{
public:
	/*  _____________________________________________________________________ */
	/*! Camera2D::init(GLFWwindow* pWindow, Object* ptr)
	@param GLFWwindow* pWindow, Object* ptr
	@return none

	Assign pgo to camera and compute aspect ratio, initialize as free camera.
	*/
	void init(GLFWwindow*, Object* ptr);

	/*  _________________________________________________________________________ */
	/*! Camera2D::update(GLFWwindow*)
	@param GLFWwindow*
	@return none

	Update camera's ratio, orientation, position, up and right vectors, zoom and transformation matrices
	*/
	void update(GLFWwindow*);

	/*-----------------------Variables declaration------------------------------------------*/
	Object* pgo; // pointer to game obj that embeds the camera
	glm::vec2 right, up;

	//additional parameters for camera
	GLint height{ 1000 };
	GLfloat ar;

	glm::mat3 camwin_to_ndc_xform;
	glm::mat3 world_to_ndc_xform;
	glm::mat3 view_xform;

	//window parameters
	GLint min_height{ 500 }, max_height{ 720 };
	// height is increasing if 1 and decreasing if -1
	GLint height_chg_dir{ 1 };
	// increments by which window height is changed per Z key press
	GLint height_chg_val{ 5 };

	// camera speed when button U is pressed
	GLfloat linear_speed{ 2.f };
	GLfloat velocity{ 500.f };
	GLfloat vel2{ 500.f };
	GLfloat acceleration{ 100.f };
	GLfloat deceleration{ 0.0f };

	//bool for physics
	GLboolean decelerate{ GL_FALSE };

	// Keyboard button press flags:
	GLboolean camtype_flag{ GL_FALSE }; // button V
	GLboolean zoom_flag{ GL_FALSE }; // button Z
	GLboolean left_turn_flag{ GL_FALSE }; // button H
	GLboolean right_turn_flag{ GL_FALSE }; // button K
	GLboolean move_flag{ GL_FALSE }; // button U
	static Camera2D camera2d;

};

#endif // !CAMERA2D_H_
