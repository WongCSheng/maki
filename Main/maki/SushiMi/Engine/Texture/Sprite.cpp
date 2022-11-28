#include "Sprite.h"

#include <../glew/include/GL/glew.h>
#include "../Animation/Animation2D.h"
#include "../Engine/Texture/Texture.h"
#include "../Engine/Texture/Rectangle.h"
#include "../Engine/Components/Transform/sTransform.h"

Sprite::Sprite(const char* filename)
{
	auto tex_sys = TextureSystem::GetInstance();
	texture = new Texture(tex_sys->Generate(filename));

	auto rect_sys = RectangleSystem::GetInstance();
	rectangle = new Rect(rect_sys->Generate());
}

Sprite::~Sprite()
{
	auto tex_sys = TextureSystem::GetInstance();
	tex_sys->Delete(*texture);

	auto rect_sys = RectangleSystem::GetInstance();
	rect_sys->Delete(*rectangle);


	for (auto& o : anims)
		delete o;
}

void Sprite::draw(double deltatime, AnimationType& type)
{

	if (anims[type])
	{
		anims[type]->play(*texture, *rectangle, deltatime);
	}

	glBindTexture(GL_TEXTURE_2D, texture->ID);
	glBindVertexArray(rectangle->VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Sprite::Add_animation(const char* filename)
{
	auto anim = new Animation2D(filename);

	anims.push_back(anim);
}
