#ifndef MESH_FILTER_H
#define MESH_FILTER_H

#include "Component.h"

class Mesh;
class MeshFilter :
	public Component
{
public:
	MeshFilter();
	virtual ~MeshFilter();

	void Set(Mesh* mesh);
	Mesh* GetMesh(void);

private:
	Mesh* mesh;
};

#endif