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
#include <GLFW/glfw3.h>
#include <glm/glm/fwd.hpp>
#include "../include/Math.h"
#include "../include/Vector.h"
#include <glm/glm/trigonometric.hpp>
#include "../Headers/Math_Header.h"
/*--------------------------------------------------------------------------- */
namespace Core{

	//forward declaration
	namespace Object
	{
		class GameObject;
	}

	class Camera2D
	{
	public:
		/*  _____________________________________________________________________ */
		/*! Camera2D::init(GLFWwindow* pWindow, Object* ptr)
		@param GLFWwindow* pWindow, Object* ptr
		@return none

		Assign pgo to camera and compute aspect ratio, initialize as free camera.
		*/
		void init(GLFWwindow*, Object::GameObject* ptr);

		/*  _________________________________________________________________________ */
		/*! Camera2D::update(GLFWwindow*)
		@param GLFWwindow*
		@return none

		Update camera's ratio, orientation, position, up and right vectors, zoom and transformation matrices
		*/
		void update(GLFWwindow*);

		void SetHeight(int value);
		void SetAspectRatio(float value);
		float CalculateAspectRatio(int Height, int Width);
		
		void SetCamtoNDCMat(gfxVector3 value);
		void SetWorldtoNDC(gfxVector3 value);
		void SetView_xform(gfxVector3 value);
		void SetRight(gfxVector2 value);
		void SetUp(gfxVector2 value);
		void Setheight_chg_dir(int value);
		void Setheight_chg_val(int value);
		void SetLinear_speed(float value);
		void SetVelocity(float value);
		void Setvel2(float value);
		void Setacceleration(float value);
		void Setdeceleration(float value);
		//Need find another way to use without strings
		/*template<typename... T>
		void SetCamera(std::pair<std::string, T> ... params);*/

		/*-----------------------Variables declaration------------------------------------------*/
		gfxVector2 right{}, up{};

		//window parameters
		GLint min_height{}, max_height{};
		// height is increasing if 1 and decreasing if -1
		GLint height_chg_dir{};
		// increments by which window height is changed per Z key press
		GLint height_chg_val{};

		// camera speed when button U is pressed
		GLfloat linear_speed{};
		GLfloat velocity{};
		GLfloat vel2{};
		GLfloat acceleration{};
		GLfloat deceleration{};

		//bool for physics
		GLboolean decelerate{ false };

		// Keyboard button press flags:
		GLboolean camtype_flag{ false }; // button V
		GLboolean zoom_flag{ false }; // button Z
		GLboolean left_turn_flag{ false }; // button H
		GLboolean right_turn_flag{ false }; // button K
		GLboolean move_flag{ false }; // button W
		static Camera2D camera2d;

	private:
		GLint height{};
		GLfloat ar{};

		gfxVector3 camwin_to_ndc_xform{};
		gfxVector3 world_to_ndc_xform{};
		gfxVector3 view_xform{};
	};
}

#endif // !CAMERA2D_H_
