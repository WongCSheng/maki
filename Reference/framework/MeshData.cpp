#include "MeshData.h"


MeshData::MeshData(std::vector<Vertex> vertex_buffer_data, std::vector<GLuint> index_buffer_data)
{
	this->vertex_buffer_data = vertex_buffer_data;
	this->index_buffer_data = index_buffer_data;
}


MeshData::~MeshData()
{
}

std::vector<Vertex>& MeshData::GetVertexBufferData(void)
{
	return vertex_buffer_data;
}

std::vector<GLuint>& MeshData::GetIndexBufferData(void)
{
	return index_buffer_data;
}
