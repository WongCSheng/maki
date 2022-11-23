#pragma once
#ifndef SPRITE_H
#define SPRITE_H
#include "../include/texture.h"
#include "../Engine/Animation/Rectangle.h"
#include "../Engine/Animation/Transform.h"
#include "../Engine/Animation/Animation2D.h"


class Sprite
{
public:
	Sprite(const char* filename);

	~Sprite();

	void draw(double deltatime, AnimationType type);

	void Add_animation(const char* filename);

	Transform transformation;

private:
	Texture texture;
	Rectangle rectangle;

	std::vector<Animation2D*> anims;
};
#endif