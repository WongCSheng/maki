#ifndef ASSET_H
#define ASSET_H

#include <string>
#include <map>

class Mesh;
class Texture;
class Skybox;
class Asset
{
public:
	static inline Asset& Instance(void)
	{
		if (instance != 0)
		{
			return *instance;
		}

		instance = new Asset();
		return *instance;
	}

	void Init();
	void CleanUp();
	Mesh* GetModel(std::string ModelName);
	Texture* GetTexture(std::string TextureName);
	Skybox* GetSkyboxModel();

private:
	Asset();
	~Asset();

	void InitFromDirectory();

	static Asset* instance;
	std::map<std::string, Mesh*> models;
	std::map<std::string, Texture*> textures;
	Skybox* skybox;
};

#endif