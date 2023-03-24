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
	TextureSystem::TextureSystem()
	{
		//_instance = nullptr;
	}


	Texture TextureSystem::Generate(Texture* tex)
	{		
		glGenTextures(1, &tex->TextureID);

		if (tex->data)
		{
			glBindTexture(GL_TEXTURE_2D, tex->TextureID);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex->Texwidth, tex->Texheight, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex->data);
			glGenerateMipmap(GL_TEXTURE_2D);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

			 /********** texture minimize & maxmize operation
			 to solve pixlation problem*/
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //GL_LINEAR_MIPMAP_NEAREST
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}
		else
		{
			std::cout << "failed to load image : " << tex->TextureID << std::endl;
			std::cout << "============================================" << std::endl;
			tex->Delete();
		}

		return *tex;
	}

	void TextureSystem::Delete(Texture& obj)
	{
		obj.Delete();
		glDeleteTextures(1, &obj.TextureID);
	}

	void TextureSystem::Init()
	{

	}

	void TextureSystem::Update(const double )
	{
		
	}

	void TextureSystem::RegisterComponent(std::unordered_map<std::string, Object::GameObject*> ObjectContainer)
	{
		
	}
	void TextureSystem::Shutdown()
	{
		for (auto&[name, tex] : database)
		{
			Delete(tex);
		}
	}

}
