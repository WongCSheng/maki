/*!
@file		object.h
@author		louishetong.wang@digipen.edu
@date		20/09/2022

This file implements functionality for the object itself. So once the object is
created, next step is to draw the object using the shader program and call DrawElements
to draw the object, then unbind and unuse the shader program.
*//*__________________________________________________________________________*/
#pragma once
#ifndef OBEJCT_H_
#define OBJECT_H_
/*                                                                   includes
----------------------------------------------------------------------------- */
#include "include/common_headers.hpp"
#include "Camera2D.h"
#include <GL/glew.h>
#include <map>
#include "include/glslshader.h"
#include "model.h"
#include "include/collision.h"
#include <glm/glm/fwd.hpp>
#include <glm/glm/trigonometric.hpp>
#include <GLFW/glfw3.h>
/*--------------------------------------------------------------------------- */
class Object
{
public:

	void draw() const;

	void update(GLdouble delta_time);

	glm::vec2 orientation{};	// orientation.x is angle_disp and
							// orientation.y is angle_speed both in degrees

	glm::vec2 scaling{};		// scaling parameters
	glm::vec2 position{};		// translation vector coordinates
	glm::vec2 initialPos{};		//initial position
	gfxVector2 velocity{};
	float dirCurr{};
	Collision::AABB aabb;
	bool status{};
	float mass;						//mass inst for accelerations
	 


	// compute object's model transform matrix using scaling,
	// rotation, and translation attributes
	glm::mat3 mdl_to_ndc_xform{};

	// reference of the model to keep track of which model is it.
	std::map<std::string, Model>::iterator mdl_ref{};

	// draw the specific model using the specific shader
	std::map<std::string, GLSLShader>::iterator shd_ref{};

	static Object* square;
	glm::vec3 color{};
	glm::mat3 mdl_xform{}; // model transformation

	static std::map<std::string, Object> objects; // singleton

	GLboolean rot_right{ GL_FALSE };
	GLboolean rot_left{ GL_FALSE };
	GLboolean scale_up{ GL_FALSE };
	GLboolean scale_down{ GL_FALSE };
};

#endif // !OBEJCT_H_
