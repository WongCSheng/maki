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
#include "../Components/Texture/Texture.h"
#include "../System/SystemFrame.h"

namespace Core
{
	class TextureSystem : public SystemFrame
	{
	public:
		static TextureSystem* GetInstance() {
			static TextureSystem texturesystem;
			return &texturesystem;
		}

		void Init();
		void Update(const double dt);
		void RegisterComponent(std::unordered_map<std::string, Object::GameObject*> ObjectContainer);

		Texture Generate(Texture* tex);

		void Delete(Texture& obj);

		void Shutdown();

		std::unordered_map<std::string, Texture> database;
	private:
		TextureSystem();
		//static TextureSystem* _instance;
	};
}
