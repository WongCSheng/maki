#include "TextureSystem.h"
/*!
@file		Texture.cpp
@author		louishetong.wang@digipen.edu
@date		20/11/2022

@brief		Generating of texture using stbi and mimap. Delete of texture is here too.
*//*__________________________________________________________________________*/
#include <../stb-master/stb_image.h>

namespace Core
{
	TextureSystem* TextureSystem::_instance{};

	TextureSystem* TextureSystem::GetInstance()
	{
		if (_instance == nullptr) _instance = new TextureSystem();

		return _instance;
	}

	TextureSystem::TextureSystem()
	{
		_instance = nullptr;
	}


	Texture TextureSystem::Generate(const char* filename)
	{		
		
		Texture result;
		int width, height, numcomponents;
		unsigned char* data;
		unsigned int textureID = 0;
		//mini Asset Manager -Thea
		//check if the texture has already been loaded, 
		auto iter = database.find(filename);
		if (iter != database.end()) {
			return iter->second; //if it already has been loaded, dont load again
		}
		else
		{
			glGenTextures(1, &textureID);
			data = stbi_load(filename, &width, &height, &numcomponents, STBI_rgb_alpha);
			result.Texwidth = width;
			result.Texheight = height;
			result.TextureID = textureID;
			if (data)
			{
				glBindTexture(GL_TEXTURE_2D, textureID);
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
				glGenerateMipmap(GL_TEXTURE_2D);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
				// ********* texture minimize & maxmize operation
				// to solve pixlation problem
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //GL_LINEAR_MIPMAP_NEAREST
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			}
			else
			{
				std::cout << "failed to load image : " << filename << std::endl;
				std::cout << "============================================" << std::endl;
			}
			stbi_image_free(data);
			database[filename] = result;
			return result;
		}
		
	}

	void TextureSystem::Delete(Texture& obj)
	{
		/*if (obj.data)
		{
			stbi_image_free(obj.data);
		}*/
		glDeleteTextures(1, &obj.TextureID);
	}

	void TextureSystem::Init()
	{

	}

	void TextureSystem::Update(const double dt)
	{

	}

	void TextureSystem::RegisterComponent(std::unordered_map<std::string, Object::GameObject*> ObjectContainer)
	{
		
	}
	void TextureSystem::Shutdown()
	{
		for (auto[name, tex] : database)
		{
			Delete(tex);
		}
	}

}
