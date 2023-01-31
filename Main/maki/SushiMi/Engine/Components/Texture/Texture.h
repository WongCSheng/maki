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
#include "../Engine/System/SystemFrame.h"
#include "../Component.h"
#include <unordered_map>
#include <iostream>

namespace Core
{
	struct Texture : public Component
	{
		Texture();
		~Texture();
		
		void TextureLoadIn(const char* filename);

		void Delete();

		void Init();
		void Serialize(const std::string name);
		void Deserialize(const std::string name);

		bool IsActive();
		void Activate();
		void Deactivate();
		void Remove();
		
		int Texwidth, Texheight, num_8_bit_component;
		unsigned int TextureID;

		unsigned char* data;
	};
}