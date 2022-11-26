#pragma once
//#include "../Engine/Components/Transform/sTransform.h"
enum AnimationType;
class Texture;
class Rect;
class Animation2D;
class Transform;
#include <vector>
class Sprite
{
public:
	Sprite(const char* filename);

	~Sprite();

	void draw(double deltatime, AnimationType& type);

	void Add_animation(const char* filename);

	Transform* transformation;

private:
	Texture* texture;
	Rect* rectangle;

	std::vector<Animation2D*> anims;
};