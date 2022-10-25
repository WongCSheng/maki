/*!
@file		model.cpp
@author		louishetong.wang@digipen.edu
@date		20/09/2022

This file implements functionality for the Model. There are 3 models currently
which are circle, square and triangle(The 3 basic shapes for rendering).
So initialization will read the mesh file path, and from the file's prefix determine
which type of model it is, the vertices index, position vertices, create the buffers
with the size of the vertices and store them respectively.
*//*__________________________________________________________________________*/

/*                                                                   includes
----------------------------------------------------------------------------- */
#include "model.h"
#include <glm/glm/fwd.hpp>
#include <glm/glm/glm.hpp>
/*--------------------------------------------------------------------------- */


std::map<std::string, Model> Model::models; // singleton

/*  _________________________________________________________________________ */
/*! Model init(std::string)
@param std::string
@return Model result

initialize the 3 different types of models by reading from the filepath and storing the data into a model.
*/
Model Model::init(std::string mesh_filepath)
{

	std::vector<glm::vec2> pos_vtx;
	std::vector<GLushort> idx_vtx;
	GLushort f;
	GLushort ix, iy, iz;
	GLfloat x, y;
	Model result;
	std::string model_name;
	std::ifstream ifs{ mesh_filepath, std::ios::in };
	if (!ifs)
	{
		std::cout << "ERROR: Unable to open mesh file!" << std::endl;
		exit(EXIT_FAILURE);
	}
	ifs.seekg(0, std::ios::beg);
	while (ifs.peek() != EOF) 	// start reading file from here
	{
		std::string line;
		getline(ifs, line);
		std::istringstream prefix_check{ line };
		char prefix;
		prefix_check >> prefix;	// check prefix
		switch (prefix)
		{
		case 'n':				// n refers to name
			prefix_check >> model_name;
			break;

		case 'v':				// v refers to vertex
			prefix_check >> x >> y;
			pos_vtx.emplace_back(x, y);
			break;
		case 'f':				// f refers to triangle fan
			result.primitive_type = GL_TRIANGLE_FAN;
			if (idx_vtx.size() == 0)
			{
				prefix_check >> ix >> iy >> iz;
				idx_vtx.emplace_back(ix);
				idx_vtx.emplace_back(iy);
				idx_vtx.emplace_back(iz);
			}
			else
			{
				prefix_check >> f;
				idx_vtx.emplace_back(f);
			}
			break;
		case 't':				// t refers to triangle
			result.primitive_type = GL_TRIANGLES;
			prefix_check >> ix >> iy >> iz;
			idx_vtx.emplace_back(ix);
			idx_vtx.emplace_back(iy);
			idx_vtx.emplace_back(iz);
			break;
		case 'l': //linebox for visual display
			result.primitive_type = GL_LINE;
			prefix_check >> ix >> iy >> iz;
			idx_vtx.emplace_back(ix);
			idx_vtx.emplace_back(iy);
			idx_vtx.emplace_back(iz);
		}

	}
	//vbo handler
	GLuint vbo_hdl;
	glCreateBuffers(1, &vbo_hdl);	//create buffer object
	glNamedBufferStorage(vbo_hdl, sizeof(glm::vec2) * pos_vtx.size(), NULL, GL_DYNAMIC_STORAGE_BIT);	//allocate memory with size of glm::vec2 * size of pos_vtx
	glNamedBufferSubData(vbo_hdl, 0, sizeof(glm::vec2) * pos_vtx.size(), pos_vtx.data());	//update a subset, meaning the next set of memory data and fill with .data
	//vao handler
	GLuint vaoid;
	glCreateVertexArrays(1, &vaoid);	//create vertex array object
	glEnableVertexArrayAttrib(vaoid, 0);	//enable/disable attribute array to position 0 in vertex shader.
	glVertexArrayVertexBuffer(vaoid, 0, vbo_hdl, 0, sizeof(glm::vec2));	//bind buffer to vertex buffer bind point(0)
	glVertexArrayAttribFormat(vaoid, 0, 2, GL_FLOAT, GL_FALSE, 0);	//specify organization of vertex arrays(type of data stored, normalized or not etc)
	glVertexArrayAttribBinding(vaoid, 0, 0);	//associate vertex attribute and vertex buffer binding for the object. BIND TOGETHER
	glBindVertexArray(0);	//unbind

	//texture position in attribute index 2 and bind to point 5
	glEnableVertexArrayAttrib(vaoid, 2);
	glVertexArrayVertexBuffer(vaoid, 5, vbo_hdl,0, sizeof(glm::vec2));
	glVertexArrayAttribFormat(vaoid, 2, 2, GL_FLOAT, GL_FALSE, 0);
	glVertexArrayAttribBinding(vaoid, 2, 5);

	//ebo handler: EBO stores indices that openGL uses to decide what vertices to draw TLDR: indexed drawing eg: 0,1,3(1st triangle) 1,2,3(2nd triangle)
	GLuint ebo_hdl;
	glCreateBuffers(1, &ebo_hdl);
	glNamedBufferStorage(ebo_hdl, sizeof(GLushort) * idx_vtx.size(),
		reinterpret_cast<GLvoid*>(idx_vtx.data()),
		GL_DYNAMIC_STORAGE_BIT);
	glVertexArrayElementBuffer(vaoid, ebo_hdl);

	result.vaoid = vaoid;
	result.draw_cnt = static_cast<GLuint>(idx_vtx.size());
	return result;
}

GLuint Model::setup_texobj(std::string pathname)
{
	GLuint width{ 256 }, height{ 256 }, bytes_per_texel{ 4 };

	std::ifstream is;
	//open solution with ios::binary or ios::in
	is.open(pathname, std::ios::binary | std::ios::in);
	// create new heapy memory pointed by ptr_texels with size of bytes
	char* ptr_texels = new char[width * height * bytes_per_texel];
	is.read(ptr_texels, (static_cast<std::streamsize>(width) * height) * bytes_per_texel);

	GLuint texobj_hdl;
	// define and initialize a handle to texture object that will
	// encapsulate two-dimensional textures
	glCreateTextures(GL_TEXTURE_2D, 1, &texobj_hdl);
	// allocate GPU storage for texture image data loaded from file
	glTextureStorage2D(texobj_hdl, 1, GL_RGBA8, width, height);
	// copy image data from client memory to GPU texture buffer memory
	glTextureSubImage2D(texobj_hdl, 0, 0, 0, width, height,
		GL_RGBA, GL_UNSIGNED_BYTE, ptr_texels);
	// client memory not required since image is buffered in GPU memory
	delete[] ptr_texels;
	// nothing more to do - return handle to texture object
	is.close();
	return texobj_hdl;
}