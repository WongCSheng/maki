#include "Asset.h"
#include "Mesh.h"
#include "Texture.h"
#include "Skybox.h"

#include <Windows.h>
#include <sstream>
#include <iostream>
#include <filesystem>

Asset* Asset::instance = 0;

#define DIR "Resources//"
#define NATUREPACKDIR "Resources//Models//"

using namespace std;

Asset::Asset() :
skybox(NULL)
{
}

Asset::~Asset()
{
	if (skybox != NULL)
	{
		delete skybox;
		skybox = NULL;
	}
}

void Asset::Init()
{
	InitFromDirectory();

	Mesh* mesh = new Mesh();
	mesh->LoadMesh("Resources//nanosuit.obj");

	models["NANOSUIT"] = mesh;

	/*Mesh* skybox = new Mesh();
	skybox->LoadMesh("Resources//skybox.obj");

	models["SKYBOX"] = skybox;*/

	// Nature pack Trees 61 - 74

	for (int i = 61; i <= 74; ++i)
	{
		std::ostringstream filestream;
		filestream << NATUREPACKDIR << "naturePack_0" << i;
		filestream << ".obj";
		Mesh* tree = new Mesh();
		tree->LoadMesh(filestream.str());
		std::ostringstream modelname;
		modelname << "TREE" << (i - 60);
		models[modelname.str()] = tree;
	}

	Mesh* cube = new Mesh();
	cube->LoadMesh("Resources//cube.obj");
	models["CUBE"] = cube;

	Mesh* boulder = new Mesh();
	boulder->LoadMesh("Resources//boulder1.obj");
	models["BOULDER"] = boulder;

	Mesh* barrel = new Mesh();
	barrel->LoadMesh("Resources//barrel.obj");
	models["BARREL"] = barrel;

	Mesh* sphere = new Mesh();
	sphere->LoadMesh("Resources//sphere.obj");

	models["SPHERE"] = sphere;

	Mesh* plane10x10 = new Mesh();
	plane10x10->LoadMesh("Resources//plane_10x10.obj");
	models["PLANE10X10"] = plane10x10;

	Mesh* quad = new Mesh();
	quad->LoadMesh("Resources//quad.obj");

	models["QUAD"] = quad;

	Mesh* crystal = new Mesh();
	crystal->LoadMesh("Resources//crystal.obj");

	models["CRYSTAL"] = crystal;

	textures["BRICKWALL"] = new Texture(GL_TEXTURE_2D, "Resources//brickwall.jpg");
	textures["BRICKWALL"]->load(false, GL_LINEAR_MIPMAP_NEAREST, GL_LINEAR, GL_REPEAT, GL_REPEAT);

	textures["BRICKWALL_NORMAL"] = new Texture(GL_TEXTURE_2D, "Resources//brickwall_normal.jpg");
	textures["BRICKWALL_NORMAL"]->load(false, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT);

	textures["WOOD"] = new Texture(GL_TEXTURE_2D, "Resources//wood.png");
	textures["WOOD"]->load(false, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT);

	textures["BOULDER"] = new Texture(GL_TEXTURE_2D, "Resources//boulder.png");
	textures["BOULDER"]->load();

	textures["BOULDER_NORMAL"] = new Texture(GL_TEXTURE_2D, "Resources//boulderNormal.png");
	textures["BOULDER_NORMAL"]->load();

	textures["BARREL"] = new Texture(GL_TEXTURE_2D, "Resources//barrel.png");
	textures["BARREL"]->load();

	textures["BARREL_NORMAL"] = new Texture(GL_TEXTURE_2D, "Resources//barrelNormal.png");
	textures["BARREL_NORMAL"]->load();

	textures["BARREL_SPECULAR"] = new Texture(GL_TEXTURE_2D, "Resources//barrelS.png");
	textures["BARREL_SPECULAR"]->load();

	textures["BRICK2"] = new Texture(GL_TEXTURE_2D, "Resources//bricks2.jpg");
	textures["BRICK2"]->load(false, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT);

	textures["BRICK2_NORMAL"] = new Texture(GL_TEXTURE_2D, "Resources//bricks2_normal.jpg");
	textures["BRICK2_NORMAL"]->load(false, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT);

	textures["BRICK2_DISP"] = new Texture(GL_TEXTURE_2D, "Resources//bricks2_disp.jpg");
	textures["BRICK2_DISP"]->load(false, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT);

	textures["CRYSTAL"] = new Texture(GL_TEXTURE_2D, "Resources//crystal.jpg");
	textures["CRYSTAL"]->load();

	vector<const GLchar*> faces;
	faces.push_back("Resources//right.jpg");
	faces.push_back("Resources//left.jpg");
	faces.push_back("Resources//top.jpg");
	faces.push_back("Resources//bottom.jpg");
	faces.push_back("Resources//back.jpg");
	faces.push_back("Resources//front.jpg");
	textures["SKYBOX_TEXTURE"] = new Texture(GL_TEXTURE_CUBE_MAP, "");
	textures["SKYBOX_TEXTURE"]->loadCubemap(faces);

	skybox = new Skybox();
	skybox->LoadSkybox();
}

void Asset::InitFromDirectory()
{
	
}

Mesh* Asset::GetModel(std::string ModelName)
{
	for (auto &m : models)
	{
		if (m.first == ModelName)
		{
			return m.second;
		}
	}
	return NULL;
}

Texture* Asset::GetTexture(std::string TextureName)
{
	for (auto &t : textures)
	{
		if (t.first == TextureName)
		{
			return t.second;
		}
	}
	return NULL;
}

Skybox* Asset::GetSkyboxModel()
{
	return skybox;
}

void Asset::CleanUp()
{
	for (auto &m : models)
	{
		if (m.second != NULL)
		{
			delete m.second;
			m.second = NULL;
		}
	}
	models.clear();

	for (auto &t : textures)
	{
		if (t.second != NULL)
		{
			delete t.second;
			t.second = NULL;
		}
	}
	textures.clear();

	if (skybox != NULL)
	{
		delete skybox;
		skybox = NULL;
	}
}