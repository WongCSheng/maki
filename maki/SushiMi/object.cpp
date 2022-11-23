/*!
@file		object.cpp
@author		louishetong.wang@digipen.edu

@co-author 	Aurelia Chong (
\par		email: fei.x@digipen.edu


@co-author	p.tzechengjennifer@digipen.edu (41%)
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
	if (GLApp::shdrpgms[shd_ref->first].GetHandle() == 1)
	{
		// load shader program
		GLApp::shdrpgms[shd_ref->first].Use();		// this will load the objects

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
	else
	{
		// load shader program
		GLApp::shdrpgms[shd_ref->first].Use();		// this will load 4
		// bind VAO of object's model
		glBindVertexArray(Model::models[mdl_ref->first].vaoid);
		glBindTexture(GL_TEXTURE_2D, 129);
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
	//count time for animation
	double curr_time = glfwGetTime();
	static double prev_time = curr_time;
	static double start_time = glfwGetTime();
	flip = false;

	//for all objects, loop thru all objects in e1 
	for (auto& e1 : Object::objects)
	{
		if (e1.first == "temp") //store object type into container, check btw containers
		{
			for (auto& e2 : Object::objects)
			{
				if (e1.first != e2.first)
				{
					if (Collision::CollisionIntersection_RectRect(e1.second.aabb, e1.second.velocity, e2.second.aabb, e2.second.velocity) == 1)
					{
						//Please uncomment this when testing collision
						std::cout << "Collision detected between " << e1.first << " and " << e2.first << std::endl;
					}
					else if (Collision::CollisionIntersection_CircleRect(e1.second.obb, e1.second.aabb) == 1)
					{
						std::cout << "Collision detected between " << e1.first << " and " << e2.first << std::endl;
					}
					
					else
					std::cout << "No collision detected" << std::endl;
				}
			}
		}
		else
			break;

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
		Object::objects["temp"].scaling.x++;
		Object::objects["temp"].scaling.y++;
	}
	else if (scale_down == GL_TRUE)
	{
		Object::objects["temp"].scaling.x--;
		Object::objects["temp"].scaling.y--;
	}
	const glm::mat3 scale_mat
	{
		{scaling.x, 0, 0},
		{0, scaling.y, 0},
		{0, 0, 1}
	};
	if (rot_left == GL_TRUE)
	{
		Object::objects["ZRect"].orientation.x += Object::objects["ZRect"].orientation.y * 0.2f;
	}
	else if (rot_right == GL_TRUE)
	{
		Object::objects["ZRect"].orientation.x -= Object::objects["ZRect"].orientation.y * 0.2f;
	}
	else
	{
		orientation.x += orientation.y * static_cast<GLfloat>(GLHelper::delta_time);
	}

	// color animation
	if (anim_rainbow) {
		rainbowCount = curr_time - start_time;
		if (!flip) {
			if (rainbowCount < .25)
				Object::objects["anim"].color = { 148, 0, 211 };
			else if (rainbowCount < .5)
				Object::objects["anim"].color = { 75, 0, 130 };
			else if (rainbowCount < .75)
				Object::objects["anim"].color = { 0, 0, 255 };
			else if (rainbowCount < 1)
				Object::objects["anim"].color = { 0, 255, 0 };
			else if (rainbowCount < 1.25)
				Object::objects["anim"].color = { 255, 255, 0 };
			else if (rainbowCount < 1.5)
				Object::objects["anim"].color = { 255, 127, 0 };
			else if (rainbowCount < 1.75)
				Object::objects["anim"].color = { 255, 0 , 0 };
			else {
				prev_time = glfwGetTime();
				curr_time = glfwGetTime();
				prev_time = curr_time;
				start_time = glfwGetTime();
				flip != flip;
			}
		}

		else if (flip) {
			if (rainbowCount < .25)
				Object::objects["anim"].color = { 255, 0 , 0 };
			else if (rainbowCount < .5)
				Object::objects["anim"].color = { 255, 127, 0 };
			else if (rainbowCount < .75)
				Object::objects["anim"].color = { 255, 255, 0 };
			else if (rainbowCount < 1)
				Object::objects["anim"].color = { 0, 255, 0 };
			else if (rainbowCount < 1.25)
				Object::objects["anim"].color = { 0, 0, 255 };
			else if (rainbowCount < 1.5)
				Object::objects["anim"].color = { 75, 0, 130 };
			else if (rainbowCount < 1.75)
				Object::objects["anim"].color = { 148, 0, 211 };
			else {
				prev_time = glfwGetTime();
				curr_time = glfwGetTime();
				prev_time = curr_time;
				start_time = glfwGetTime();
				flip != flip;
			}
		}
	}

	if (anim_bw) {
		bwCount = curr_time - start_time;
		if (bwCount < .5)
			Object::objects["anim"].color = { 0, 0, 0 };
		else if (bwCount < 1)
			Object::objects["anim"].color = { 255, 255 , 255 };
		else {
			prev_time = glfwGetTime();
			curr_time = glfwGetTime();
			prev_time = curr_time;
			start_time = glfwGetTime();
		}

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

	mdl_to_ndc_xform = Camera2D::camera2d.world_to_ndc_xform * (trans_mat * rot_mat * scale_mat);

}



