#pragma once
/*!
@file		Texture.h
@author		louishetong.wang@digipen.edu
@date		20/11/2022

@brief		Generating of texture using stbi and mimap. Delete of texture is here too.
*//*__________________________________________________________________________*/
// singlton pattern
#include <../stb-master/stb_image.h>
#include <../glew/include/GL/glew.h>
#include <iostream>

namespace Core
{
	class Texture
	{
	public:
		Texture Generate(const char* filename);

		void Delete(Texture& obj);

		int GetWidth() const;
		int GetHeight() const;
		unsigned int GetID() const;

	private:
		int Texwidth;
		int Texheight;
		unsigned int TextureID;

		unsigned char* data;

		//std::string TextureName; //To be removed in the future for optimisation. We'll use numbers for naming textures instead
	};
}