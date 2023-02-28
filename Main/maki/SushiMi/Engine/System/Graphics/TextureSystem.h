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
#include "../Engine/Components/Texture/Texture.h"
#include "../Scene/SceneManager.h"
#include "../SystemFrame.h"

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

		void addIngrTexture(const std::pair<ingredients, Texture> &ingr);
		void addTileTexture(const std::pair<wall_type, Texture> &tile);

		Texture GetIngrTexture(ingredients order);
		Texture GetTileTexture(wall_type order);

		static bool CheckTileTexture(wall_type check);
		template<enum type>
		static bool CheckIngreTexture(type check);

		void Delete(Texture& obj);

		void Shutdown();
	private:
		TextureSystem();
		//static TextureSystem* _instance;

		static std::unordered_map<wall_type, Texture> wall_tex_container;
		static std::unordered_map<ingredients, Texture> ingr_tex_container;
	};
}
