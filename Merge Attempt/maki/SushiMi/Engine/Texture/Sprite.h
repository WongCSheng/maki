#pragma once
#include "../Engine/Components/Transform/sTransform.h"
#include "../Animation/Animation2D.h"


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
	Rect rectangle;

	vector<Animation2D*> anims;
};