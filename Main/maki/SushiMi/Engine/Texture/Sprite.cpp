#include "Sprite.h"
/*!
@file		Sprite.cpp
@author		louishetong.wang@digipen.edu
@date		20/11/2022

@brief		Drawing of the sprite and animating of it is here
*//*__________________________________________________________________________*/
#include <../glew/include/GL/glew.h>

Sprite::Sprite(const char* filename)
{
	auto tex_sys = TextureSystem::GetInstance();
	texture = tex_sys->Generate(filename);

	auto rect_sys = Core::Renderer::GetInstance();
	rectangle = rect_sys->Generate();
}

Sprite::~Sprite()
{
	auto tex_sys = TextureSystem::GetInstance();
	tex_sys->Delete(texture);

	auto rect_sys = Core::Renderer::GetInstance();
	rect_sys->Delete(rectangle);


	for (auto& o : anims)
		delete o;
}

void Sprite::draw()
{
	glBindTexture(GL_TEXTURE_2D, texture.ID);
	glBindVertexArray(rectangle.VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Sprite::draw(double deltatime, AnimationType type)
{

	if (anims[type])
	{
		anims[type]->play(texture, rectangle, deltatime);
	}

	glBindTexture(GL_TEXTURE_2D, texture.ID);
	glBindVertexArray(rectangle.VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Sprite::Add_animation(const char* filename)
{
	auto anim = new Animation2D(filename);

	anims.push_back(anim);
}
