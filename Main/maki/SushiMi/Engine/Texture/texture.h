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
	struct Texture
	{
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
}