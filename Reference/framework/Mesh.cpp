#include "Mesh.h"

#include <iostream>
#include "Matrix4f.h"

#include "Texture.h"
#include <assert.h>
#include "assimp\ai_assert.h"
#include "Asset.h"
#include "Material.h"
#include "Shader\GeometryPassShader.h"

Mesh::MeshEntry::MeshEntry()
{
	VAO = 0;
	VB = 0;
	IB = 0;
	NumIndices = 0;
	MaterialIndex = 0;
};

Mesh::MeshEntry::~MeshEntry()
{
	if (VAO != 0)
	{
		glDeleteVertexArrays(1, &VAO);
	}
	if (VB != 0)
	{
		glDeleteBuffers(1, &VB);
	}
	if (IB != 0)
	{
		glDeleteBuffers(1, &IB);
	}
}

bool Mesh::MeshEntry::Init(const std::vector<Vertex>& Vertices, const std::vector<unsigned int>& Indices)
{
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);

	NumIndices = Indices.size();

	StoreDataInAttributeList(Vertices);

	bindIndicesBuffer(Indices);

	//bindInstanceBuffer();

	glBindVertexArray(0);

	return true;
}


void Mesh::MeshEntry::StoreDataInAttributeList(const std::vector<Vertex>& Vertices)
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

void Mesh::MeshEntry::bindIndicesBuffer(const std::vector<unsigned int>& Indices)
{
	glGenBuffers(1, &IB);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, Indices.size() * sizeof(GLuint), &Indices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

Mesh::Mesh(void) :
handlesMaterial(true)
{	
	material = new Material();
}

Mesh::~Mesh(void)
{
	if (material != NULL)
	{
		delete material;
		material = NULL;
	}
	Clear();
}

bool Mesh::LoadMesh(const std::string &Filename)
{
	Clear();

	bool Ret = false;
	Assimp::Importer Importer;

	const aiScene* pScene = Importer.ReadFile(Filename.c_str(), aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
	
	if (pScene) {
		Ret = InitFromScene(pScene, Filename);
	} 
	else {
		printf("Error parsing '%s': '%s' \n", Filename.c_str(), Importer.GetErrorString());
	}

	return Ret;
}

bool Mesh::InitFromScene(const aiScene* pScene, const std::string &Filename)
{
	Entries.resize(pScene->mNumMeshes);
	material->diffuseTextures.resize(pScene->mNumMaterials);
	material->diffuseColors.resize(pScene->mNumMaterials);
	material->diffuseOnly.resize(pScene->mNumMaterials);
	material->normalTextures.resize(pScene->mNumMaterials);

	for (unsigned int i = 0; i < Entries.size(); ++i)
	{
		const aiMesh* paiMesh = pScene->mMeshes[i];
		InitMesh(i, paiMesh);
	}

	return InitMaterials(pScene, Filename);
}

void Mesh::InitMesh(unsigned int Index, const aiMesh* paiMesh)
{
	Entries[Index].MaterialIndex = paiMesh->mMaterialIndex;

	std::vector<Vertex> Vertices;
	std::vector<unsigned int> Indices;

	const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);

	for (unsigned int i = 0; i < paiMesh->mNumVertices; i++) {
		const aiVector3D* pPos = &(paiMesh->mVertices[i]);
		const aiVector3D* pNormal = &(paiMesh->mNormals[i]);
		const aiVector3D* pTexCoord = paiMesh->HasTextureCoords(0) ? &(paiMesh->mTextureCoords[0][i]) : &Zero3D;
		const aiVector3D* pTangent = &(paiMesh->mTangents[i]);
		const aiVector3D* pBitangent = &(paiMesh->mBitangents[i]);

		Vertex v;
		v.pos = Vector3(pPos->x, pPos->y, pPos->z);
		v.texCoord = TexCoord(pTexCoord->x, pTexCoord->y);
		v.normal = Vector3(pNormal->x, pNormal->y, pNormal->z);
		v.tangent = Vector3(pTangent->x, pTangent->y, pTangent->z);
		v.bitangent = Vector3(pBitangent->x, pBitangent->y, pBitangent->z);

		Vertices.push_back(v);
	}

	for (unsigned int i = 0; i < paiMesh->mNumFaces; i++) {
		const aiFace& Face = paiMesh->mFaces[i];
		assert(Face.mNumIndices == 3);
		Indices.push_back(Face.mIndices[0]);
		Indices.push_back(Face.mIndices[1]);
		Indices.push_back(Face.mIndices[2]);
	}

	Entries[Index].Init(Vertices, Indices);
}

bool Mesh::InitMaterials(const aiScene *pScene, const std::string &Filename)
{
	// Extract the directory part from the file name
	std::string::size_type SlashIndex = Filename.find_last_of("/");
	std::string Dir;

	if (SlashIndex == std::string::npos) {
		Dir = ".";
	}
	else if (SlashIndex == 0) {
		Dir = "/";
	}
	else {
		Dir = Filename.substr(0, SlashIndex) + '/';
	}

	bool Ret = true;
	for (unsigned int i = 0; i < pScene->mNumMaterials; i++)
	{
		const aiMaterial* pMaterial = pScene->mMaterials[i];

		// Get material properties
		aiColor3D diff(0.f, 0.f, 0.f);
		aiColor3D ambient(0.f, 0.f, 0.f);
		aiColor3D spec(0.f, 0.f, 0.f);
		pMaterial->Get(AI_MATKEY_COLOR_DIFFUSE, diff);
		pMaterial->Get(AI_MATKEY_COLOR_AMBIENT, ambient);
		pMaterial->Get(AI_MATKEY_COLOR_SPECULAR, spec);

		material->diffuseColors[i].x = diff.r;
		material->diffuseColors[i].y = diff.g;
		material->diffuseColors[i].z = diff.b;

		material->diffuseTextures[i] = NULL;
		material->normalTextures[i] = NULL;
		if (pMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0)
		{
			aiString Path;

			if (pMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &Path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS)
			{	
				std::string FullPath = Dir + (std::string)Path.data;
				material->diffuseTextures[i] = new Texture(GL_TEXTURE_2D, FullPath.c_str());

				if (!material->diffuseTextures[i]->load())
				{
					printf("Error loading texture '%s' \n", FullPath.c_str());
					delete material->diffuseTextures[i];
					material->diffuseTextures[i] = NULL;
					Ret = false;
				}
			}
		}

		/*if (pMaterial->GetTextureCount(aiTextureType_NORMALS) > 0)
		{
			aiString Path;

			if (pMaterial->GetTexture(aiTextureType_NORMALS, 0, &Path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS)
			{
				std::string FullPath = Dir + (std::string)Path.data;
				material->normalTextures[i] = new Texture(GL_TEXTURE_2D, FullPath.c_str());

				if (!material->normalTextures[i]->load())
				{
					printf("Error loading texture '%s' \n", FullPath.c_str());
					delete material->normalTextures[i];
					material->normalTextures[i] = NULL;
					Ret = false;
				}
			}
		}*/

		if (!material->diffuseTextures[i])
		{
			//material->diffuseTextures[i] = new Texture(GL_TEXTURE_2D, "Resources//white.tga");
			material->diffuseOnly[i] = true;

			//Ret = false;
		}

		//if (!material->normalTextures[i])
		//{
		//	material->normalMapEnable = false;
		//	//Ret = false;
		//}
		//else
		//{
		//	material->normalMapEnable = true;
		//}
	}

	return Ret;
}

//void Mesh::bindInstanceBuffer()
//{
//	//Generate instance buffer
//	glGenBuffers(1, &Buffers[INSTANCE_BUFFER]);
//
//	//Bind instance buffer
//	glBindBuffer(GL_ARRAY_BUFFER, Buffers[INSTANCE_BUFFER]);
//
//	for (unsigned int i = 0; i < 4; i++)
//	{
//		glEnableVertexAttribArray(5 + i);
//		glVertexAttribPointer(5 + i, 4, GL_FLOAT, GL_FALSE, sizeof(Matrix4f), (const GLvoid*)(sizeof(GLfloat)* i * 4));
//		glVertexAttribDivisor(5 + i, 1);
//	}
//
//	// Unbind instance buffer
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//}

void Mesh::Render(GeometryPassShader* gPassShader)
{
	/*glBindVertexArray(VAO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Buffers[INDEX_BUFFER]);

	glDrawElements(GL_TRIANGLES, IndexSize, GL_UNSIGNED_INT, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindVertexArray(0);*/

	for (unsigned i = 0; i < Entries.size(); ++i)
	{
		glBindVertexArray(Entries[i].VAO);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Entries[i].IB);

		const unsigned int MaterialIndex = Entries[i].MaterialIndex;

		if (MaterialIndex < material->diffuseTextures.size() && material->diffuseTextures[MaterialIndex] && !material->diffuseOnly[MaterialIndex])
		{
			material->diffuseTextures[MaterialIndex]->Bind(GL_TEXTURE0);
			gPassShader->load_DiffuseColorOnly(false);
		}
		else if (gPassShader != NULL)
		{
			gPassShader->load_DiffuseColor(material->diffuseColors[MaterialIndex]);
			gPassShader->load_DiffuseColorOnly(true);
		}

		gPassShader->load_NormalMapEnable(false);

		glDrawElements(GL_TRIANGLES, Entries[i].NumIndices, GL_UNSIGNED_INT, 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		glBindVertexArray(0);
	}
}

void Mesh::RenderMeshOnly()
{
	for (unsigned i = 0; i < Entries.size(); ++i)
	{
		glBindVertexArray(Entries[i].VAO);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Entries[i].IB);

		glDrawElements(GL_TRIANGLES, Entries[i].NumIndices, GL_UNSIGNED_INT, 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		glBindVertexArray(0);
	}
}

void Mesh::Clear(void)
{
	/*for (unsigned int i = 0; i < Textures.size(); i++) 
	{
		if (Textures[i] != 0)
		{
			delete Textures[i];
			Textures[i] = 0;
		}
	}*/
}