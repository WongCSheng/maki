/*!
@file		Sprite.cpp
@author		louishetong.wang@digipen.edu
co-Author:  Aurelia Chong
email:		fei.x@digipen.edu
@date		20/11/2022

@brief		Drawing of the sprite and animating of it is here
*//*__________________________________________________________________________*/
#include "Sprite.h"
#include"../Engine/System/TextureSystem.h"
#include <../glew/include/GL/glew.h>

namespace Core
{
	Sprite::Sprite(const char* filename)
	{
		auto tex_sys = Core::TextureSystem::GetInstance();
		texture = tex_sys->Generate(filename);
		
		/*texture.TextureLoadIn(filename);
		tex_sys->Generate(&texture);*/

		auto rect_sys = Core::Renderer::GetInstance();
		rectangle = rect_sys->Generate();
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

	void Sprite::draw(double deltatime, AnimationType type)
	{

		if (anims[type])
		{
			anims[type]->play(texture, rectangle, deltatime);
		}

		glBindTexture(GL_TEXTURE_2D, texture.TextureID);
		glBindVertexArray(rectangle.VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}

	void Sprite::Add_animation(const char* filename)
	{
		auto anim = new Animation2D(filename);

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