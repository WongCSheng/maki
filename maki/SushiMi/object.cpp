/*!
@file		object.cpp
@author		louishetong.wang@digipen.edu
@date		20/09/2022

This file implements functionality for the object itself. So once the object is
created, next step is to draw the object using the shader program and call DrawElements
to draw the object, then unbind and unuse the shader program.
*//*__________________________________________________________________________*/

/*                                                                   includes
----------------------------------------------------------------------------- */
#include "object.h"
#include "Camera2D.h"
#include "include/glapp.h"
/*--------------------------------------------------------------------------- */

std::map<std::string, Object> Object::objects;

/*  _________________________________________________________________________ */
/*! Object::draw() const
@param
@return none

load shader program, bind VAO, copy color to fragment shader, copy model to vertex shader, call glDrawElements
unbind VAO and unload shader program
*/
void Object::draw() const
{
	// load shader program
	GLApp::shdrpgms[shd_ref->first].Use();

	// bind VAO of object's model
	glBindVertexArray(Model::models[mdl_ref->first].vaoid);

	GLApp::shdrpgms[shd_ref->first].SetUniform("uColor", color);

	// copy model to ndc matrix to uModelToNDC
	GLApp::shdrpgms[shd_ref->first].SetUniform("uModel_to_NDC", mdl_to_ndc_xform);

	// call glDrawElements with appropriate arguments
	glDrawElements(Model::models[mdl_ref->first].primitive_type, Model::models[mdl_ref->first].draw_cnt, GL_UNSIGNED_SHORT, NULL);

	glBindVertexArray(0);
	GLApp::shdrpgms[shd_ref->first].UnUse();
}

/*  _________________________________________________________________________ */
/*! Object::update(GLdouble delta_time)
@param GLDouble delta_time
@return none

All the transformation matrix scale,rot, trans and model to ndc transformation.
*/
void Object::update(GLdouble delta_time)
{
	const glm::mat3 scale_mat
	{
		{scaling.x, 0, 0},
		{0, scaling.y, 0},
		{0, 0, 1}
	};

	orientation.x += orientation.y * static_cast<GLfloat>(GLHelper::delta_time);
	const GLfloat radians = orientation.x / 180.f * static_cast<GLfloat>(PI);

	const glm::mat3 rot_mat
	{
		{cos(radians), sin(radians), 0},
		{-sin(radians), cos(radians), 0},
		{0, 0, 1}
	};
	const glm::mat3 trans_mat
	{
		{1, 0, 0},
		{0, 1, 0},
		{position.x, position.y, 1}
	};


	mdl_to_ndc_xform = Camera2D::camera2d.world_to_ndc_xform * (trans_mat * rot_mat * scale_mat);

}