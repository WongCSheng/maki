/*!
@file		Sprite.cpp
@author		louishetong.wang@digipen.edu
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
		texture.TextureLoadIn(filename);
		tex_sys->Generate(&texture);

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

	void Sprite::Serialise(const std::string name)
	{

	}

	void Sprite::Deserialise(const std::string name)
	{

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