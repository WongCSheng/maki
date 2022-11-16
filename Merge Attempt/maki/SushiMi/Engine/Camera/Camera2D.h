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
#include "../include/Math.h"
#include "../include/Vector.h"
#include <glm/glm/trigonometric.hpp>
#include "../Headers/Math_Header.h"
#include "../Game Object/GameObject.h"
/*--------------------------------------------------------------------------- */
namespace Core
{
	//forward declaration
	namespace Object
	{
		class GameObject;
	}

	class Camera2D : public Component
	{
	public:
		friend class CameraSystem;
		
		/*  _____________________________________________________________________ */
		/*! Camera2D::init(GLFWwindow* pWindow, Object* ptr)
		@param GLFWwindow* pWindow, Object* ptr
		@return none

		Assign pgo to camera and compute aspect ratio, initialize as free camera.
		*/
		void Init();

		//void Serialise(const std::string name);

		void SetHeight(int value);
		void SetAspectRatio(float value);
		float CalculateAspectRatio(int Height, int Width);

		void SetCamtoNDCMat(gfxMatrix3 value);
		void SetWorldtoNDC(gfxMatrix3 value);
		void SetView_xform(gfxMatrix3 value);
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
		int min_height{}, max_height{};
		// height is increasing if 1 and decreasing if -1
		int height_chg_dir{};
		// increments by which window height is changed per Z key press
		int height_chg_val{};

		// camera speed when button U is pressed
		float linear_speed{};
		float velocity{};
		float vel2{};
		float acceleration{};
		float deceleration{};

		//bool for physics
		bool decelerate{ false };

		// Keyboard button press flags:
		bool camtype_flag{ false }; // button V
		bool zoom_flag{ false }; // button Z
		bool left_turn_flag{ false }; // button H
		bool right_turn_flag{ false }; // button K
		bool move_flag{ false }; // button W
		static Camera2D camera2d;

	private:
		int height{};
		int width{};
		float ar{};

		gfxMatrix3 camwin_to_ndc_xform{};
		gfxMatrix3 world_to_ndc_xform{};
		gfxMatrix3 view_xform{};
	};
}

#endif // !CAMERA2D_H_
