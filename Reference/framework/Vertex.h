#ifndef VERTEX_H
#define VERTEX_H

#include "Vector3.h"

struct TexCoord
{
	float u, v;
	TexCoord(float u = 0, float v = 0) { Set(u, v); }

	void Set(float u, float v) { this->u = u; this->v = v; }

	TexCoord operator-(const TexCoord& rhs) 
	{ 
		return TexCoord(this->u - rhs.u, this->v - rhs.v); 
	} //Vector subtraction
};


struct Vertex
{
	Vector3 pos;
	Vector3 normal;
	TexCoord texCoord;
	Vector3 tangent;
	Vector3 bitangent;

	Vertex(void)
	{
	};
};

//void CalcNormals(const unsigned int* pIndices, unsigned int IndexCount, Vertex* pVertices, unsigned int VertexCount)
//{
//	for (unsigned int i = 0; i < IndexCount; i += 3) {
//		unsigned int Index0 = pIndices[i];
//		unsigned int Index1 = pIndices[i + 1];
//		unsigned int Index2 = pIndices[i + 2];
//		Vector3f v1 = pVertices[Index1].m_pos - pVertices[Index0].m_pos;
//		Vector3f v2 = pVertices[Index2].m_pos - pVertices[Index0].m_pos;
//		Vector3f Normal = v1.Cross(v2);
//		Normal.Normalize();
//
//		pVertices[Index0].m_normal += Normal;
//		pVertices[Index1].m_normal += Normal;
//		pVertices[Index2].m_normal += Normal;
//	}
//
//	for (unsigned int i = 0; i < VertexCount; i++) {
//		pVertices[i].m_normal.Normalize();
//	}
//}
#endif