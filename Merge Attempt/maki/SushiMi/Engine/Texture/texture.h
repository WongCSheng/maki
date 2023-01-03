#pragma once

// singlton pattern

class Texture
{
public:
	int width;
	int height;
	unsigned int ID;
};

class TextureSystem
{
public:
	static TextureSystem* GetInstance();

	Texture Generate(const char* filename);

	void Delete(Texture& obj);

private:
	TextureSystem();

	static TextureSystem* _instance;
};