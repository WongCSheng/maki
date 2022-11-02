/*!
@file		model.h
@author		louishetong.wang@digipen.edu
@co-author 	Aurelia Chong(15%)
\par		email: fei.x@digipen.edu
@date		20/09/2022

This file implements functionality for the Model. There are 3 models currently
which are circle, square and triangle(The 3 basic shapes for rendering).
So initialization will read the mesh file path, and from the file's prefix determine
which type of model it is, the vertices index, position vertices, create the buffers
with the size of the vertices and store them respectively.
*//*__________________________________________________________________________*/

#ifndef MODEL_H_
#define MODEL_H_

/*                                                                   includes
----------------------------------------------------------------------------- */
#include "include/Vector.h"
#include <GL/glew.h>
#include <map>
/*--------------------------------------------------------------------------- */
class Model
{
public:
	/*  _____________________________________________________________________ */
	/*! Model init(std::string)
	@param std::string
	@return Model result

	initialize the 3 different types of models by reading from the filepath and storing the data into a model.
	*/
	Model init(std::string mesh_filepath); // read mesh data from file

	GLenum primitive_type{}; // which OpenGL primitive to be rendered?
	GLuint vaoid{}; // handle to VAO
	GLuint draw_cnt{}; // count of vertices for certain type of primitives and a count of indices for other types
	GLuint primitive_cnt{}; // access the number of OGL pimitives contained in an instance of Model
							// primitive_type are to be rendered
	static std::map<std::string, Model> models; // singleton
	GLuint setup_texobj(std::string pathname);
};

#endif // !MODEL_H_
