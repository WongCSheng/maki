#include "object.h"
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
	ShaderProgram::shdrpgms[shd_ref->first].start_shader();

	// bind VAO of object's model
	glBindVertexArray(Model::models[mdl_ref->first].vaoid);

	// copy obj color to uColor
	ShaderProgram::shdrpgms[shd_ref->first].setuniform("uColor", color);

	// copy model to ndc matrix to uModelToNDC
	ShaderProgram::shdrpgms[shd_ref->first].setuniform("uModel_to_NDC", mdl_to_ndc_xform);

	// call glDrawElements with appropriate arguments
	glDrawElements(Model::models[mdl_ref->first].primitive_type, Model::models[mdl_ref->first].draw_cnt, GL_UNSIGNED_SHORT, NULL);

	glBindVertexArray(0);
	ShaderProgram::shdrpgms[shd_ref->first].stop_shader();
}