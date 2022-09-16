#ifndef MESH_LOADER_H
#define MESH_LOADER_H

#include "MeshData.h"
#include "Vertex.h"
#include "LoadObject.h"
#include <string>

enum MeshType
{
	OBJ,
	TRIANGLE,
	MAX_TYPE,
};

static MeshData* GenerateTriangle(void)
{
	std::vector<Vertex> v;

	Vertex Vertices[4];
	Vertices[0].pos = Vector3(0.5f, 0.5f, 0.0f);  // Top Right
//	Vertices[0].
	Vertices[1].pos = Vector3(0.5f, -0.5f, 0.0f);  // Bottom Right
	Vertices[2].pos = Vector3(-0.5f, -0.5f, 0.0f);  // Bottom Left
	Vertices[3].pos = Vector3(-0.5f, 0.5f, 0.0f); // Top Left 

	v.push_back(Vertices[0]);
	v.push_back(Vertices[1]);
	v.push_back(Vertices[2]);
	v.push_back(Vertices[3]);

	std::vector<GLuint> i;
	i.push_back(0);
	i.push_back(1);
	i.push_back(3);
	i.push_back(1);
	i.push_back(2);
	i.push_back(3);

	MeshData* data = new MeshData(v, i);
	return data;
}

static MeshData* GenerateObject(std::string filename)
{
	//Read vertices, texcoords & normals from OBJ
	std::vector<Vector3> vertices;
	std::vector<TexCoord> uvs;
	std::vector<Vector3> normals;
	std::vector<Vector3> tangents;
	std::vector<Vector3> bitangents;

	//Loading start
	bool success = LoadOBJ(filename.c_str(), vertices, uvs, normals, tangents, bitangents);

	//If not success
	if (!success)
	{
		return false;
	}

	//Index the vertices, texcoords & normals properly
	std::vector<Vertex> vertex_buffer_data; //IMPORTANT!!! All vertex data is in this vector.
	std::vector<GLuint> index_buffer_data; //IMPROTANT!! Later for all the index buffer object.
	IndexVBO(vertices, uvs, normals, tangents, bitangents, index_buffer_data, vertex_buffer_data);

	MeshData* data = new MeshData(vertex_buffer_data, index_buffer_data);

	return data;
}

#endif