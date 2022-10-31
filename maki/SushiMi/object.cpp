/*!
@file		object.cpp
@author		louishetong.wang@digipen.edu
@co-author	fei.x@digiprn.edu
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
#include "Physics.h"
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
	if (GLApp::shdrpgms[shd_ref->first].GetHandle() == 0)
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
	else if (GLApp::shdrpgms[shd_ref->first].GetHandle() == 1)
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


}

/*  _________________________________________________________________________ */
/*! Object::update(GLdouble delta_time)
@param GLDouble delta_time
@return none

All the transformation matrix scale,rot, trans and model to ndc transformation.
*/
void Object::update(GLdouble delta_time)
{
	
	for (auto& e1 : Object::objects)
	{
		for (auto& e2 : Object::objects)
		{
			if (e1.first != e2.first)
			{
				if (Collision::CollisionIntersection_RectRect(e1.second.aabb, e1.second.velocity, e2.second.aabb, e2.second.velocity) == 1)
				{
					std::cout << "Collision detected between " << e1.first << " and " << e2.first << std::endl;
				}
				//std::cout << "No collision detected" << std::endl;
			}
		}
	}

	//updating aabb box for object collision
	for (auto& e1 : Object::objects)
	{
		e1.second.aabb.min.x = e1.second.position.x - (e1.second.scaling.x / 2); //calculating bottom left min.x
		e1.second.aabb.min.y = e1.second.position.y - (e1.second.scaling.y / 2); //calculating bottom left min.y
		e1.second.aabb.max.x = e1.second.position.x + (e1.second.scaling.x / 2); //calculating top right max.x
		e1.second.aabb.max.y = e1.second.position.y + (e1.second.scaling.y / 2); //calculating top right max.y

	}
	
	if (scale_up == GL_TRUE)
	{
		Object::objects["Object6"].scaling.x++;
		Object::objects["Object6"].scaling.y++;
	}
	else if (scale_down == GL_TRUE)
	{
		Object::objects["Object6"].scaling.x--;
		Object::objects["Object6"].scaling.y--;
	}
	const glm::mat3 scale_mat
	{
		{scaling.x, 0, 0},
		{0, scaling.y, 0},
		{0, 0, 1}
	};
	if (rot_left == GL_TRUE)
	{
		Object::objects["Object6"].orientation.x += Object::objects["Object6"].orientation.y * 0.2f;
	}
	else if (rot_right == GL_TRUE)
	{
		Object::objects["Object6"].orientation.x -= Object::objects["Object6"].orientation.y * 0.2f;
	}
	else
	{
		orientation.x += orientation.y * static_cast<GLfloat>(GLHelper::delta_time);
	}

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
	
	//updatePosition(Object::objects["Object5"]);
	
	//apply acceleration
	// Updating the velocity and position according to acceleration is done by using the following:
	// step1: v1 = a*t + v0        //This is done when the UP or DOWN key is pressed 
	// step2: Pos1 = 1/2 * a*t*t + v0*t + Pos0
	// step3: Pos1 = v1t + Pos0
	//Object::objects["Object5"].position += applyGravity(Object::objects["Object5"].mass) * (float)delta_time;

	//float acceleration = applyAccel(Object::objects["Object5"].mass);	 //	stores acceleration
	//gfxVector2 preVel = Object::objects["Object5"].velocity;			 //	stores previous velocity/v0
	//glm::vec2 prePos = Object::objects["Object5"].position;				 //	stores previous position/p0

	//		/*update velocity based on previous velocity*/
	//Object::objects["Object5"].velocity.x = (acceleration * delta_time) + preVel.x; //step1 .x
	//Object::objects["Object5"].velocity.y = (acceleration * delta_time) + preVel.y; //step1 .y

	///*update position based on velocity & previous position*/
	//Object::objects["Object5"].position.x =	(1/2 * acceleration * delta_time * delta_time) +
	//											(Object::objects["Object5"].velocity.x * delta_time) +
	//												prePos.x;						//step2	.x	

	//Object::objects["Object5"].position.y = (1/2 * acceleration * delta_time * delta_time) +
	//												(Object::objects["Object5"].velocity.y * delta_time) +
	//													 prePos.y;					//step2	.y
	//
	//glm::vec2 displacement = Object::objects["Object5"].position - Object::objects["Object5"].initialPos;
	
	

	mdl_to_ndc_xform = Camera2D::camera2d.world_to_ndc_xform * (trans_mat * rot_mat * scale_mat);
	
}