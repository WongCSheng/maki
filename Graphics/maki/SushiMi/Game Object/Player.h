#pragma once

#include "../Engine/Texture/Sprite.h"
class Player
{
public:
	Player();

	~Player();

	void move_left();

	void move_right();

	void move_up();

	void move_down();


	void stop();

	glm::mat4 Transformation();

	void draw(double deltatime);


private:
	Sprite* sp;
	AnimationType current_anim;
};