#include "Skybox.h"
#include <GL\glew.h>

#include "Vector3.h"
#include "Vertex.h"

#define ARRAY_SIZE_IN_ELEMENTS(a) (sizeof(a) / sizeof(a[0]))

Skybox::Skybox() :
VAO(0),
VB(0)
{
}

Skybox::~Skybox()
{
	if (VAO != 0)
	{
		glDeleteVertexArrays(1, &VAO);
	}
	if (VB != 0)
	{
		glDeleteBuffers(1, &VB);
	}
}

bool Skybox::LoadSkybox()
{
	vector<Vertex> vertices;

	Vector3 skyboxVertices[] = {
		// Positions          
		Vector3(-1.0f, 1.0f, -1.0f),
		Vector3(-1.0f, -1.0f, -1.0f),
		Vector3(1.0f, -1.0f, -1.0f),
		Vector3(1.0f, -1.0f, -1.0f),
		Vector3(1.0f, 1.0f, -1.0f),
		Vector3(-1.0f, 1.0f, -1.0f),

		Vector3(-1.0f, -1.0f, 1.0f),
		Vector3(-1.0f, -1.0f, -1.0f),
		Vector3(-1.0f, 1.0f, -1.0f),
		Vector3(-1.0f, 1.0f, -1.0f),
		Vector3(-1.0f, 1.0f, 1.0f),
		Vector3(-1.0f, -1.0f, 1.0f),

		Vector3(1.0f, -1.0f, -1.0f),
		Vector3(1.0f, -1.0f, 1.0f),
		Vector3(1.0f, 1.0f, 1.0f),
		Vector3(1.0f, 1.0f, 1.0f),
		Vector3(1.0f, 1.0f, -1.0f),
		Vector3(1.0f, -1.0f, -1.0f),

		Vector3(-1.0f, -1.0f, 1.0f),
		Vector3(-1.0f, 1.0f, 1.0f),
		Vector3(1.0f, 1.0f, 1.0f),
		Vector3(1.0f, 1.0f, 1.0f),
		Vector3(1.0f, -1.0f, 1.0f),
		Vector3(-1.0f, -1.0f, 1.0f),

		Vector3(-1.0f, 1.0f, -1.0f),
		Vector3(1.0f, 1.0f, -1.0f),
		Vector3(1.0f, 1.0f, 1.0f),
		Vector3(1.0f, 1.0f, 1.0f),
		Vector3(-1.0f, 1.0f, 1.0f),
		Vector3(-1.0f, 1.0f, -1.0f),

		Vector3(-1.0f, -1.0f, -1.0f),
		Vector3(-1.0f, -1.0f, 1.0f),
		Vector3(1.0f, -1.0f, -1.0f),
		Vector3(1.0f, -1.0f, -1.0f),
		Vector3(-1.0f, -1.0f, 1.0f),
		Vector3(1.0f, -1.0f, 1.0f)
	};

	for (int i = 0; i < ARRAY_SIZE_IN_ELEMENTS(skyboxVertices); ++i)
	{
		Vertex v;
		v.pos = skyboxVertices[i];
		vertices.push_back(v);
	}

	Init(vertices);

	return true;
}

void Skybox::Render()
{
	glBindVertexArray(VAO);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	//Make sure the VAO is not changed from the outside. Unbind the VAO
	glBindVertexArray(0);
}

bool Skybox::Init(const std::vector<Vertex>& Vertices)
{
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);

	StoreDataInAttributeList(Vertices);

	//bindInstanceBuffer();

	glBindVertexArray(0);

	return true;
}

void Skybox::StoreDataInAttributeList(const std::vector<Vertex>& Vertices)
{
	glGenBuffers(1, &VB);

	glBindBuffer(GL_ARRAY_BUFFER, VB);

	glBufferData(GL_ARRAY_BUFFER, Vertices.size() * sizeof(Vertex), &Vertices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0); //Position

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(Vector3)); //Normal

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Vector3)+sizeof(Vector3))); //TexCoord

	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Vector3)+sizeof(Vector3)+sizeof(TexCoord))); //Tangent

	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Vector3)+sizeof(Vector3)+sizeof(TexCoord)+sizeof(Vector3))); //BiTangent

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}