/*!
@file		player.cpp
@author		louishetong.wang@digipen.edu
@date		20/11/2022

@brief		Creating a player using sprite and adding of animation. movement of player
			, drawing and transformation of player is here too
*//*__________________________________________________________________________*/
#include "Player.h"
#include "../src/Window.h"
#include "../Engine/System/Graphics/glhelper.h"

//static Window win; //create a external window variable to pass through data

 //adjust according to tile-map size


int screenDimension = 1000;

Player::Player()
{

	sp = new Sprite("../textures/spritesheet/spritesheet.png");
	sp->transformation.position = glm::vec2(Player::playerptr->x, Player::playerptr->y);
	sp->transformation.scale = glm::vec2(150, 150);

	sp->Add_animation("../textures/spritesheet/Idle.txt");
	sp->Add_animation("../textures/spritesheet/Run.txt");

	current_anim = Idle;
}

Player::Player(const char* spriteFilepath, float* spritePos, float* spriteScale, std::vector<std::string> const& animationList) {
	sp = new Sprite(spriteFilepath);
	sp->transformation.position = glm::vec2(spritePos[0], spritePos[1]);
	sp->transformation.scale = glm::vec2(spriteScale[0], spriteScale[1]);

	for (std::string const& animFilepath : animationList) {
		sp->Add_animation(animFilepath.c_str());
	}

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
	int* screenptr = &screenDimension;
	int gridWidth = screenDimension / 6;
	glfwGetWindowSize(Window::window_ptr, screenptr, screenptr);
	sp->transformation.position.x -= gridWidth;
	Player::playerptr->x -= gridWidth;


}

void Player::move_right()
{
	if (sp->transformation.scale.x < 0)
		sp->transformation.scale.x *= -1;

	current_anim = Run;

	int* screenptr = &screenDimension;
	int gridWidth = screenDimension / 6;
	glfwGetWindowSize(Window::window_ptr, screenptr, screenptr);
	sp->transformation.position.x += gridWidth;
	Player::playerptr->x += gridWidth;
}

void Player::move_up()
{
	if (sp->transformation.scale.y > 0)
		sp->transformation.scale.y *= 1;

	current_anim = Run;
	int* screenptr = &screenDimension;
	int gridWidth = screenDimension / 6;
	glfwGetWindowSize(Window::window_ptr, screenptr, screenptr);
	sp->transformation.position.y -= gridWidth;
	Player::playerptr->y -= gridWidth;

}

void Player::move_down()
{
	if (sp->transformation.scale.y < 0)
		sp->transformation.scale.y *= -1;

	current_anim = Run;
	int* screenptr = &screenDimension;
	int gridWidth = screenDimension / 6;
	glfwGetWindowSize(Window::window_ptr, screenptr, screenptr);
	sp->transformation.position.y += gridWidth;
	Player::playerptr->y += gridWidth;

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