#pragma once
/*!
@file		player.h
@author		louishetong.wang@digipen.edu
@date		20/11/2022

@brief		Creating a player using sprite and adding of animation. movement of player
			, drawing and transformation of player is here too
*//*__________________________________________________________________________*/
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