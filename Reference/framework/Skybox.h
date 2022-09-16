#ifndef SKYBOX_H
#define SKYBOX_H

#include <vector>

using std::vector;

class Mesh;
struct Vertex;
class Skybox
{
public:
	Skybox();
	~Skybox();

	bool LoadSkybox();
	void Render();

private:
	unsigned int VAO;
	unsigned int VB;

	bool Init(const std::vector<Vertex>& Vertices);
	void StoreDataInAttributeList(const std::vector<Vertex>& Vertices);
};

#endif