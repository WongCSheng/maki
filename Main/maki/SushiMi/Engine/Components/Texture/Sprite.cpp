/*!
@file		Sprite.cpp
@author		WOng Louis He Tong 60%
email:		louishetong.wang@digipen.edu
co-Author:  Chong Rui Xuan Aurelia 40%
email:		fei.x@digipen.edu
@date		20/11/2022

@brief		Drawing of the sprite and animating of it is here
*//*__________________________________________________________________________*/
#include "Sprite.h"
#include"../Engine/System/TextureSystem.h"
#include "../Engine/TileMap/Map.h"
#include "../Headers/SceneManager.h"
#include <../glew/include/GL/glew.h>

namespace Core
{
	Sprite::Sprite(const char* filename) : SpriteSize{}, alpha{}, curr_anim{}, isSpriteSheet{}, timer{}
	{
		//mem leak here?
		auto tex_sys = Core::TextureSystem::GetInstance();
		texture.TextureLoadIn(filename);
		tex_sys->Generate(&texture);

		auto rect_sys = Core::Renderer::GetInstance();
		rectangle = rect_sys->Generate();

		//std::cout << "Texture loaded: " << filename << " Texture ID: a" << texture.TextureID << "\n";
	}

	Sprite::~Sprite()
	{
		auto tex_sys = Core::TextureSystem::GetInstance();
		tex_sys->Delete(texture);

		auto rect_sys = Core::Renderer::GetInstance();
		rect_sys->Delete(rectangle);


		for (auto& o : anims)
			delete o;
	}

	void Sprite::draw()
	{
		glBindTexture(GL_TEXTURE_2D, texture.TextureID);
		glBindVertexArray(rectangle.VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}

	void Sprite::drawTest()
	{
		glBindTexture(GL_TEXTURE_2D, texture.TextureID);
		glBindVertexArray(rectangle.VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}

	void Sprite::draw(double deltatime, AnimationType type)
	{

		if (anims[static_cast<int>(type)])
		{
			anims[static_cast<int>(type)]->play(texture, rectangle, deltatime * 10);
		}

		glBindTexture(GL_TEXTURE_2D, texture.TextureID);
		glBindVertexArray(rectangle.VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}

	void Sprite::Add_animation(const char* filename)
	{
		auto anim = new Animation2D(filename);
		anim->set_animation_speed(0.2f);
		anims.push_back(anim);
	}

	void Sprite::Init()
	{

	}

	void Sprite::Serialize(const std::string name)
	{

	}

	
	void Sprite::Deserialize(const rapidjson::Value& jsonObj)
	{
		//checking file exist/no
		if (!jsonObj.HasMember("SpriteSheet"))
		{
			std::cout << "Component of type SpriteSheet cannot be read" << std::endl;
			return;
		}

		isSpriteSheet = jsonObj["SpriteSheet"].GetBool();

		if (!jsonObj.HasMember("SpriteSize") || !jsonObj["SpriteSize"].IsArray() || jsonObj["SpriteSize"].Size() < 2)
		{
			std::cout << "Component of type SpriteSize must have key 'SpriteSize' with an array of size 2" << std::endl;
		}

		const rapidjson::Value& SpriteArr = jsonObj["SpriteSize"]; 

		for (int i = 0; i < 2; i++)
		{

			float value = SpriteArr[i].GetFloat();
			if (i == 0)
				SpriteSize[i] = value; //value of spriteArr from json, sabed into spritesize
			else
				SpriteSize[i] = value; 
		}
		std::cout << "SpriteSize X: " << SpriteSize[0] << "        " << "SpriteSize Y: " << SpriteSize[1] << "\n";

		std::cout << "Deserializing Sprite Component! \n";
	
	}

	void Sprite::restart()
	{
		for (auto& ingredient : SceneManager::ingredientcontainer)
		{
			for (auto& start : SceneManager::ingredient_starting_pos)
			{
				ingredient.second->transformation.Position = start.second->transformation.Position;
			}
		}
		
		/**************
		INGREDIENT 1
		*************/

		//set the initial grid that the ingredient is leaving back to blank 
		//Map::gGrids[SceneManager::ingredient1->ingredient1_Grid_pos.x][SceneManager::ingredient1->ingredient1_Grid_pos.y] = 0;
		//

		////update graphics
		//SceneManager::ingredient1->transformation.Position.x = SceneManager::ingredient1->ingredient1_initial_pos.x; //initial pos is set in Map.cpp
		//SceneManager::ingredient1->transformation.Position.y = SceneManager::ingredient1->ingredient1_initial_pos.y;

		//
		//SceneManager::ingredient1->ingredient1_Grid_pos.x = SceneManager::ingredient1->ingredient1_initial_pos.x ;
		//SceneManager::ingredient1->ingredient1_Grid_pos.y = SceneManager::ingredient1->ingredient1_initial_pos.y;

		////set the new grid the ingredient is now at to contain player
		//Map::gGrids[SceneManager::ingredient1->ingredient1_Grid_pos.x][SceneManager::ingredient1->ingredient1_Grid_pos.y] = 3;
		////}

		///**************
		//INGREDIENT 2
		//*************/

		////set the initial grid that the ingredient is leaving back to blank 
		//Map::gGrids[SceneManager::ingredient2->ingredient2_Grid_pos.x][SceneManager::ingredient2->ingredient2_Grid_pos.y] = 0;


		////update graphics
		//SceneManager::ingredient2->transformation.Position.x = SceneManager::ingredient2->ingredient2_initial_pos.x; //initial pos is set in Map.cpp
		//SceneManager::ingredient2->transformation.Position.y = SceneManager::ingredient2->ingredient2_initial_pos.y;


		//SceneManager::ingredient2->ingredient2_Grid_pos.x = SceneManager::ingredient2->ingredient2_initial_pos.x;
		//SceneManager::ingredient2->ingredient2_Grid_pos.y = SceneManager::ingredient2->ingredient2_initial_pos.y;

		////set the new grid the ingredient is now at to contain player
		//Map::gGrids[SceneManager::ingredient2->ingredient2_Grid_pos.x][SceneManager::ingredient2->ingredient2_Grid_pos.y] = 4;
		////}
	}

	bool Sprite::IsActive()
	{
		return active;
	}

	void Sprite::Activate()
	{
		active = true;
	}

	void Sprite::Deactivate()
	{
		active = false;
	}

	void Sprite::Remove()
	{
		remove = true;
	}
}