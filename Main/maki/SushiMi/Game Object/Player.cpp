/*!
@file		player.cpp
@author		louishetong.wang@digipen.edu
@date		20/11/2022

@brief		Creating a player using sprite and adding of animation. movement of player
			, drawing and transformation of player is here too
*//*__________________________________________________________________________*/
#include "Player.h"

Player::Player()
{

	sp = new Sprite("../textures/spritesheet/spritesheet.png");
	sp->transformation.position = glm::vec2(500, 500);
	sp->transformation.scale = glm::vec2(150, 150);

	sp->Add_animation("../textures/spritesheet/Idle.txt");
	sp->Add_animation("../textures/spritesheet/Run.txt");

	current_anim = Idle;
}

Player::~Player()
{
	delete sp;
}

void Player::move_left()
{
	if (sp->transformation.scale.x > 0)
		sp->transformation.scale.x *= 1;

	current_anim = Run;
	sp->transformation.position.x -= 1;
}

void Player::move_right()
{
	if (sp->transformation.scale.x < 0)
		sp->transformation.scale.x *= -1;

	current_anim = Run;
	sp->transformation.position.x += 1;
}

void Player::move_up()
{
	if (sp->transformation.scale.y > 0)
		sp->transformation.scale.y *= 1;

	current_anim = Run;
	sp->transformation.position.y -= 1;
}

void Player::move_down()
{
	if (sp->transformation.scale.y < 0)
		sp->transformation.scale.y *= -1;

	current_anim = Run;
	sp->transformation.position.y += 1;
}

void Player::stop()
{
	current_anim = Idle;
}

glm::mat4 Player::Transformation()
{
	return sp->transformation.Get();
}

void Player::draw(double deltatime)
{
	sp->draw(deltatime, current_anim);
}
