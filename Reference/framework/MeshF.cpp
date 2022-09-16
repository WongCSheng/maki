#include "MeshF.h"
#include "Mesh.h"
#include "Material.h"
#include "Entity.h"

MeshFilter::MeshFilter()
{
}

MeshFilter::~MeshFilter()
{
}

void MeshFilter::Set(Mesh* mesh)
{
	this->mesh = mesh;
}

Mesh* MeshFilter::GetMesh(void)
{
	return mesh;
}