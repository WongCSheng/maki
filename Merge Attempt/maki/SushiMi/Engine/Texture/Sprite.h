/*!
@file		Sprite.h
@author		louishetong.wang@digipen.edu
@date		20/11/2022

@brief		Drawing of the sprite and animating of it is here
*//*__________________________________________________________________________*/
#pragma once
#include "../Engine/Texture/texture.h"
#include "../Engine/Texture/Rectangle.h"
#include "../Engine/Components/Transform/sTransform.h"
#include "../Engine/Animation/Animation2D.h"


class Sprite
{
public:
	Sprite(const char* filename);

	~Sprite();

	void draw();

	void draw(double deltatime, AnimationType type);

	void Add_animation(const char* filename);

	Transform transformation;

private:
	Texture texture;
	Rect rectangle;

	std::vector<Animation2D*> anims;
};