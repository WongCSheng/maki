/*!
@file		Texture.cpp
@author		louishetong.wang@digipen.edu
@date		20/11/2022

@brief		Generating of texture using stbi and mimap. Delete of texture is here too.
*//*__________________________________________________________________________*/
#include "Texture.h"

namespace Core
{
	Texture Texture::Generate(const char* filename)
	{
		int numcomponents;
		unsigned int TextureID;

		glGenTextures(1, &TextureID);

		data = stbi_load(filename, &Texwidth, &Texheight, &numcomponents, STBI_rgb_alpha);

		if (data)
		{
			glBindTexture(GL_TEXTURE_2D, TextureID);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Texwidth, Texheight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
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
			stbi_image_free(data);
		}

		stbi_image_free(data);

		return *this;
	}

	void Texture::Delete(Texture& obj)
	{
		glDeleteTextures(1, &obj.TextureID);
	}

	int Texture::GetWidth() const
	{
		return Texwidth;
	}

	int Texture::GetHeight() const
	{
		return Texheight;
	}

	unsigned int Texture::GetID() const
	{
		return TextureID;
	}
}