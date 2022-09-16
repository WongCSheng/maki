#ifndef MESH_RENDERER_H
#define MESH_RENDERER_H

#include "Component.h"

class Material;
class MeshFilter;
class GeometryPassShader;
class MeshRenderer :
	public Component
{
public:
	MeshRenderer();
	virtual ~MeshRenderer();

	void Validate();
	// Draw with texture
	void Draw(GeometryPassShader* gPassShader);
	// Draw without texture
	void DrawMeshOnly();

	MeshFilter *meshFilter;
	Material *material;
};

#endif