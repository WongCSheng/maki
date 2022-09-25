#pragma once
#ifndef OBEJCT_H_
#define OBJECT_H_

#include <../Matrix.h>
#include <../Vector.h>
#include <../vector3.h>
#include <GL/glew.h>
#include <map>
#include "include/glslshader.h"
#include "model.h"

class Object
{
public:
	void draw() const;

	void update(GLdouble delta_time);

	glm::vec2 orientation; // orientation.x is angle_disp and
					  // orientation.y is angle_speed both in degrees

	glm::vec2 scaling; // scaling parameters
	glm::vec2 position; // translation vector coordinates

	// compute object's model transform matrix using scaling,
	// rotation, and translation attributes ...
	// this must be computed by the cpu and not by the vertex shader (why?)
	glm::mat3 mdl_to_ndc_xform;

	// which model is this object an instance of?
	// since models are contained in a vector, we keep track of the
	// specific model that was instanced by index into vector container
	std::map<std::string, Model>::iterator mdl_ref;

	// how to draw this instanced model?
	// since shader programs are contained in a vector, we keep track of
	// specific shader program using an index into vector container
	std::map<std::string, GLSLShader>::iterator shd_ref;

	
	glm::vec3 color;
	glm::mat3 mdl_xform; // model transformation

	static std::map<std::string, Object> objects; // singleton
};

#endif // !OBEJCT_H_
