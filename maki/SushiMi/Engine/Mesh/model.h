#ifndef MODEL_H_
#define MODEL_H_

#include <GL/glew.h>
#include "../Headers/STL_Header.h"
#include <glm/glm/fwd.hpp>
#include <glm/glm/glm.hpp>
#include "../Headers/Math_Header.h"

class Model
{
public:
	GLenum primitive_type{}; // which OpenGL primitive to be rendered?
	GLuint vaoid{}; // handle to VAO
	GLuint draw_cnt{}; // count of vertices for certain type of primitives and a count of indices for other types
	GLuint primitive_cnt{}; // access the number of OGL pimitives contained in an instance of GLModel
							// primitive_type are to be rendered
	/*  _________________________________________________________________________ */
	/*! Model init(std::string)
	@param std::string
	@return Model result

	initialize the 3 different types of models by reading from the filepath and storing the data into a model.
	*/
	Model init(std::string mesh_filepath); // read mesh data from file ...
	static std::map<std::string, Model> models; // singleton
};

#endif // !MODEL_H_
