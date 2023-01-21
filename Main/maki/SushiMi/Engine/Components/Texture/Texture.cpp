/*!
@file		Texture.cpp
@author		louishetong.wang@digipen.edu
@date		20/11/2022

@brief		Generating of texture using stbi and mimap. Delete of texture is here too.
*//*__________________________________________________________________________*/
#include <../stb-master/stb_image.h>
#include "../Engine/System/TextureSystem.h"
#include "Texture.h"

namespace Core
{
	void Texture::TextureLoadIn(const char* filename)
	{		
		Texheight = Texwidth = TextureID = 0;

		data = stbi_load(filename, &Texwidth, &Texheight, &num_8_bit_component, STBI_rgb_alpha);
	}

	void Texture::Delete(Texture& obj)
	{
		if (data)
		{
			stbi_image_free(data);
		}

		glDeleteTextures(1, &obj.TextureID);
	}

	void Texture::Init()
	{

	}

	void Texture::Serialise(const std::string name)
	{

	}

	void Texture::Deserialise(const std::string name)
	{

	}

	bool Texture::IsActive()
	{
		return active;
	}

	void Texture::Activate()
	{
		active = true;
	}

	void Texture::Deactivate()
	{
		active = false;
	}

	void Texture::Remove()
	{
		remove = true;
	}
}
