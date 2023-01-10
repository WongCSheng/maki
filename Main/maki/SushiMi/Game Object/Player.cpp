#include "Player.h"
#include "../Engine/Components/Transform/sTransform.h"
#include "../Engine/Animation/Animation2D.h"
#include "../Engine/Texture/Sprite.h"
struct fakemat4
{
	glm::mat4 data;
};
Player::Player()
{
	sp = new Sprite("../textures/spritesheet/spritesheet.png");
	sp->transformation = new Transform();
	sp->transformation->position = glm::vec2(500, 500);
	sp->transformation->scale = glm::vec2(150, 150);

	sp->Add_animation("../textures/spritesheet/Idle.txt");
	sp->Add_animation("../textures/spritesheet/Run.txt");

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

fakemat4* Player::Transformation()
{
	fakemat4* temp = new fakemat4{ sp->transformation->Get() };
	return temp;
}

void Player::draw(double deltatime)
{
	sp->draw(deltatime, *current_anim);
}
