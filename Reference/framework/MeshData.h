#ifndef MESH_DATA_H
#define MESH_DATA_H

#include <GL\glew.h>
#include "Vertex.h"

#include <vector>

class MeshData
{
public:
	MeshData(std::vector<Vertex> vertex_buffer_data, std::vector<GLuint> index_buffer_data);
	~MeshData();

	std::vector<Vertex>& GetVertexBufferData(void);
	std::vector<GLuint>& GetIndexBufferData(void);

private:
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
};

#endif