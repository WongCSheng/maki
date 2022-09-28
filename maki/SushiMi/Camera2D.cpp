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
#include "object.h"
#include "Camera2D.h"
#include "include/glhelper.h"
#include <glm/glm/trigonometric.hpp>
#include <glm/glm/fwd.hpp>
/*--------------------------------------------------------------------------- */

/*global variables*/
GLboolean first_person_cam = GL_FALSE;
Camera2D Camera2D::camera2d;

/*  _________________________________________________________________________ */
/*! Camera2D::init(GLFWwindow* pWindow, GLApp::GLObject* ptr)
@param GLFWwindow* pWindow, Object* ptr
@return none

Assign pgo to camera and compute aspect ratio, initialize as free camera.
*/
void Camera2D::init(GLFWwindow* pWindow, Object* ptr)
{
	// assign address of object of type GLApp::GLObject with name "Camera" in objects
	pgo = &Object::objects.at("Camera");

	// compute camera window's aspect ratio
	GLsizei fb_width, fb_height;
	glfwGetFramebufferSize(pWindow, &fb_width, &fb_height);
	ar = static_cast<GLfloat>(fb_width) / static_cast<GLfloat>(fb_height);

	// compute camera's up and right vectors
	up = { -sin(pgo->orientation.x / 180.f * static_cast<GLfloat>(PI)), cos(pgo->orientation.x / 180.f * static_cast<GLfloat>(PI)) };
	right = { cos(pgo->orientation.x / 180.f * static_cast<GLfloat>(PI)), sin(pgo->orientation.x / 180.f * static_cast<GLfloat>(PI)) };

	// at startup, camera must be initialized to free camera
	view_xform =
	{
		{1, 0, 0},
		{0, 1, 0},
		{-pgo->position.x, -pgo->position.y, 1}
	};

	GLfloat cam_W = ar * GLHelper::height;
	GLfloat cam_H = ar * GLHelper::width;
	// compute other matrices
	camwin_to_ndc_xform =
	{
		{2 / cam_W, 0, 0},
		{0, 2 / cam_H, 0},
		{0, 0, 1}
	};
	world_to_ndc_xform = camwin_to_ndc_xform * view_xform;
}

/*  _________________________________________________________________________ */
/*! Camera2D::update(GLFWwindow*)
@param GLFWwindow*
@return none

Update camera's ratio, orientation, position, up and right vectors, zoom and transformation matrices
*/
void Camera2D::update(GLFWwindow* pWindow)
{
	ar = (GLfloat)GLHelper::width / (GLfloat)GLHelper::height;
	// update POV using keypress
	if (camtype_flag == GL_TRUE)
	{
		if (first_person_cam == GL_FALSE)
		{
			first_person_cam = GL_TRUE;
		}
		else if (first_person_cam == GL_TRUE)
		{
			first_person_cam = GL_FALSE;
		}
		camtype_flag = GL_FALSE;
	}

	if (first_person_cam == GL_TRUE)
	{
		view_xform = { {right.x,up.x,0.f},
						{right.y,up.y,0.f},
						{glm::dot(-glm::normalize(right),pgo->position),glm::dot(-glm::normalize(up),pgo->position),1.f}
		};
	}
	else if (first_person_cam == GL_FALSE)
	{
		view_xform = { {1.f,0.f,0.f},
						{0.f,1.f,0.f},
						{-pgo->position.x,-pgo->position.y,1.f}
		};
	}
	if (left_turn_flag == GL_TRUE)
	{
		pgo->orientation.x += pgo->orientation.y;
	}
	if (right_turn_flag == GL_TRUE)
	{
		pgo->orientation.x -= pgo->orientation.y;
	}
	// update camera's up and right vectors

	up = { -sinf(glm::radians(pgo->orientation.x)),
			cosf(glm::radians(pgo->orientation.x)) };

	right = { cosf(glm::radians(pgo->orientation.x)),
				sinf(glm::radians(pgo->orientation.x)) };

	// update camera's position
	if (move_flag == GL_TRUE)
	{
		pgo->position += (linear_speed * glm::normalize(up));//displace the camera
	}

	// implement camera's zoom effect (if required)
	if (zoom_flag == GL_TRUE)
	{
		if (height <= min_height)
		{
			height_chg_dir = 1;
		}
		else if (height >= max_height)
		{
			height_chg_dir = -1;
		}
		height += (height_chg_dir * height_chg_val);
	}


	// compute window-to-NDC transformation matrix
	// compute other matrices like rotation,scaling and translation
	camwin_to_ndc_xform = { {2.0f / (height * ar),0.f,0.f},
							{0.f,2.f / height,0.f},
							{0.f,0.f,1.f}
	};
	GLfloat radians = glm::radians(camera2d.pgo->orientation.x);

	glm::mat3 rot_mat
	{
			{cos(radians), sin(radians), 0},
			{-sin(radians), cos(radians), 0},
			{0, 0, 1}
	};

	glm::mat3 scale_mat
	{
		{camera2d.pgo->scaling.x, 0, 0},
		{0, camera2d.pgo->scaling.y, 0},
		{0, 0, 1}
	};

	glm::mat3 trans_mat
	{
		{1, 0, 0},
		{0, 1, 0},
		{camera2d.pgo->position.x, camera2d.pgo->position.y, 1}
	};
	glm::mat3 model_mtx = trans_mat * rot_mat * scale_mat;
	camera2d.pgo->mdl_to_ndc_xform = world_to_ndc_xform * model_mtx;
	// compute world-to-NDC transformation matrix
	world_to_ndc_xform = camwin_to_ndc_xform * view_xform;
}