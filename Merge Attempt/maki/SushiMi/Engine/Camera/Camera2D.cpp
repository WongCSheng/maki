/*!
@file		Camera2D.cpp
@author		louishetong.wang@digipen.edu
@date		20/09/2022

This file implements functionality for the 2D Camera. Main functions include the initialization
and the updating of the camera's position,rotation and scaling.
There are a lot of matrices and vectors being used. Was previously using my own created
vector and matrix library but there were many errors so temporarily using glm's vector and
matrix library for now. Links to GLHelper for the keypresses like rotation and zooming in.
*//*__________________________________________________________________________*/

/*                                                                   includes
----------------------------------------------------------------------------- */
#include "../Game Object/GameObject.h"
#include "Camera2D.h"
/*--------------------------------------------------------------------------- */
-namespace Core
{
	/*global variables*/
	bool first_person_cam = false;

	/*  _________________________________________________________________________ */
	/*! Camera2D::init(GLFWwindow* pWindow, GLApp::GLObject* ptr)
	@param GLFWwindow* pWindow, Object* ptr
	@return none

	Assign pgo to camera and compute aspect ratio, initialize as free camera.
	*/
	void Camera2D::Init()
	{
		
	}

	/*void Camera2D::Serialise(const std::string name)
	{

	}*/

	void Camera2D::SetHeight(int value)
	{
		height = value;
	}

	void Camera2D::SetAspectRatio(float value)
	{
		ar = value;
	}

	float Camera2D::CalculateAspectRatio(int Height, int Width)
	{
		return static_cast<float>(Width / Height);
	}

	void Camera2D::SetCamtoNDCMat(gfxMatrix3 value)
	{
		camwin_to_ndc_xform = value;
	}

	void Camera2D::SetWorldtoNDC(gfxMatrix3 value)
	{
		world_to_ndc_xform = value;
	}

	void Camera2D::SetView_xform(gfxMatrix3 value)
	{
		view_xform = value;
	}

	void Camera2D::SetRight(gfxVector2 value)
	{
		right = value;
	}

	void Camera2D::SetUp(gfxVector2 value)
	{
		up = value;
	}

	void Camera2D::Setheight_chg_dir(int value)
	{
		height_chg_dir = value;
	}

	void Camera2D::Setheight_chg_val(int value)
	{
		height_chg_val = value;
	}

	void Camera2D::SetLinear_speed(float value)
	{
		linear_speed = value;
	}

	void Camera2D::SetVelocity(float value)
	{
		velocity = value;
	}

	void Camera2D::Setvel2(float value)
	{
		vel2 = value;
	}

	void Camera2D::Setacceleration(float value)
	{
		acceleration = value;
	}

	void Camera2D::Setdeceleration(float value)
	{
		deceleration = value;
	}

	//Need find another way to use without strings
	/*template<typename... T>
	void Camera2D::SetCamera(std::pair<std::string, T> ...params)
	{
		switch (params.first)
		{
		case "velocity":
		}
	}*/
}