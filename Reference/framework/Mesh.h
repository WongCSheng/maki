#ifndef MESH_H
#define MESH_H


#include <GL\glew.h>

#include <vector>
#include "Vertex.h"
#include "assimp\Importer.hpp"
#include "assimp\mesh.h"
#include "assimp\postprocess.h"
#include "assimp\scene.h"
#include "assimp\material.h"
#include "assimp\material.inl"

class Material;
class Texture;
class GeometryPassShader;
class Mesh
{
public:
	Mesh();
	~Mesh();

	bool LoadMesh(const std::string &Filename);
	
	// Render with material
	void Render(GeometryPassShader* gPassShader);
	// Render only
	void RenderMeshOnly();

	Material* material;
	bool handlesMaterial;

private:
	bool InitFromScene(const aiScene* pScene, const std::string &Filename);
	void InitMesh(unsigned int Index, const aiMesh* paiMesh);
	bool InitMaterials(const aiScene* scene, const std::string &Filename);
	void Clear();

#define INVALID_MATERIAL 0xFFFFFFFF

	struct MeshEntry {
		MeshEntry();
		~MeshEntry();

		bool Init(const std::vector<Vertex>& Vertices, const std::vector<unsigned int>& Indices);
		void StoreDataInAttributeList(const std::vector<Vertex>& Vertices);
		void bindIndicesBuffer(const std::vector<unsigned int>& Indices);

		GLuint VAO;
		GLuint VB;
		GLuint IB;
		unsigned int NumIndices;
		unsigned int MaterialIndex;
	};

	std::vector<MeshEntry> Entries;
	//std::vector<Texture*> Textures;
};

#endif