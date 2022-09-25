#include "object.h"
#include "Camera2D.h"
#include "include/glapp.h"
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
/*! GLApp::GLObject::update(GLdouble delta_time)
@param GLDouble delta_time
@return none

All the transformation matrix scale,rot, trans and model to ndc transformation.
*/
void Object::update(GLdouble delta_time)
{

	gfxMatrix3 scale_mat;
	scale_mat.a[0] = scaling.x;
	scale_mat.a[1] = 0;
	scale_mat.a[2] = 0;
	scale_mat.a[3] = 0;
	scale_mat.a[4] = scaling.y;
	scale_mat.a[5] = 0;
	scale_mat.a[6] = 0;
	scale_mat.a[7] = 0;
	scale_mat.a[8] = 1;

	orientation.x += orientation.y * static_cast<GLfloat>(GLHelper::delta_time);
	const GLfloat radians = orientation.x / 180.f * static_cast<GLfloat>(PI);

	gfxMatrix3 rot_mat;
	rot_mat.a[0] = cos(radians);
	rot_mat.a[1] = sin(radians);
	rot_mat.a[3] = -sin(radians);
	rot_mat.a[4] = cos(radians);
	rot_mat.a[2] = rot_mat.a[5] = rot_mat.a[6] = rot_mat.a[7] = rot_mat.a[8] = 0;

	gfxMatrix3 trans_mat;
	trans_mat.a[0] = 1;
	trans_mat.a[1] = 0;
	trans_mat.a[2] = 0;
	trans_mat.a[3] = 0;
	trans_mat.a[4] = 1;
	trans_mat.a[5] = 0;
	trans_mat.a[6] = position.x;
	trans_mat.a[7] = position.y;
	trans_mat.a[0] = 1;


	mdl_to_ndc_xform = Camera2D::camera2d.world_to_ndc_xform * (trans_mat * rot_mat * scale_mat);

}