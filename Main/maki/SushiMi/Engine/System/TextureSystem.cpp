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


	Texture TextureSystem::Generate(Texture* tex)
	{		
		glGenTextures(1, &tex->TextureID);

		if (tex->data)
		{
			glBindTexture(GL_TEXTURE_2D, tex->TextureID);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex->Texheight, tex->Texwidth, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex->data);
			std::cout << "Error: " << glGetError() << std::endl;
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
			std::cout << "failed to load image : " << tex->TextureID << std::endl;
			std::cout << "============================================" << std::endl;
			//stbi_image_free(tex->data);
		}

		return *tex;
	}

	void TextureSystem::Delete(Texture& obj)
	{
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
}
