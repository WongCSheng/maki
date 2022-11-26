#include "Player.h"
#include "../Engine/Components/Transform/sTransform.h"
#include "../Engine/Animation/Animation2D.h"
#include "../Engine/Texture/Sprite.h"
Player::Player()
{
	sp = new Sprite("resources/spritsheet/spritesheet.png");
	sp->transformation->position = glm::vec2(500, 500);
	sp->transformation->scale = glm::vec2(150, 150);

	sp->Add_animation("resources/spritsheet/Idle.txt");
	sp->Add_animation("resources/spritsheet/Run.txt");

	current_anim = new AnimationType(Idle);
}

Player::~Player()
{
	delete sp;
}

void Player::move_left()
{
	if (sp->transformation->scale.x > 0)
		sp->transformation->scale.x *= -1;

	current_anim = new AnimationType(Run);
	sp->transformation->position.x -= 5;
}

void Player::move_right()
{
	if (sp->transformation->scale.x < 0)
		sp->transformation->scale.x *= -1;

	current_anim = new AnimationType(Run);
	sp->transformation->position.x += 5;
}

void Player::stop()
{
	current_anim = new AnimationType(Idle);
}

glm::mat4 Player::Transformation()
{
	return sp->transformation->Get();
}

void Player::draw(double deltatime)
{
	sp->draw(deltatime, *current_anim);
}
