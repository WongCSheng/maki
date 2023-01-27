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
namespace Core
{

	Player::Player()
	{

		sp = new Sprite("../textures/spritesheet/spritesheet.png");
		sp->transformation.position = glm::vec2(playerpos.x, playerpos.y);
		sp->transformation.scale = glm::vec2(100, 100);

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

	//Example: my screen can display 19 (W) x 11 (H) tiles
	void Player::move_left()
	{
		if (sp->transformation.scale.x > 0)
			sp->transformation.scale.x *= 1;

		current_anim = Run;

		//Best way: ensure grid is consistent with all window sizes
		//glfwGetWindowSize(Window::window_ptr, &Window::ScreenDimensions::screenwidth, &Window::ScreenDimensions::screenheight);
		//int gridWidth = Window::ScreenDimensions::screenwidth / 19; //columns are 19

		//current hard code way
		int gridWidth = 100;
		playerpos.x -= gridWidth;
		//ensure player does not go out of screen
		if (playerpos.x < 0)
		{
			playerpos.x = 0;
		}
		else
		{
			sp->transformation.position.x -= gridWidth;
			
		}
	}

	void Player::move_right()
	{
		if (sp->transformation.scale.x < 0)
			sp->transformation.scale.x *= -1;

		current_anim = Run;

		//Best way: ensure grid is consistent with all window sizes
		//glfwGetWindowSize(Window::window_ptr, &Window::ScreenDimensions::screenwidth, &Window::ScreenDimensions::screenheight);
		//int gridWidth = Window::ScreenDimensions::screenwidth / 19; //columns are 19

		//current hard code way
		int gridWidth = 100;
		playerpos.x += gridWidth;
		//ensure player does not go out of screen
		if (playerpos.x > 1800)
		{
			playerpos.x = 1800;
		}
		else
		{
			sp->transformation.position.x += gridWidth;
		}
	}

	void Player::move_up()
	{
		if (sp->transformation.scale.y > 0)
			sp->transformation.scale.y *= 1;
		//std::cout << "you are pressing up" << std::endl;

		current_anim = Run;

		//Best way: ensure grid is consistent with all window sizes
		//glfwGetWindowSize(Window::window_ptr, &Window::ScreenDimensions::screenwidth, &Window::ScreenDimensions::screenheight);
		//int gridHeight = Window::ScreenDimensions::screenheight / 11; //rows are 11

		//current hard code way
		int gridHeight = 100;
		Player::playerpos.y -= gridHeight;
		if (playerpos.y < 0)
		{
			playerpos.y = 0;
		}
		else
		{
			sp->transformation.position.y -= gridHeight; //up is negative for some reason
		}
	}

	void Player::move_down()
	{
		if (sp->transformation.scale.y < 0)
			sp->transformation.scale.y *= -1;

		current_anim = Run;

		//Best way: ensure grid is consistent with all window sizes
		//glfwGetWindowSize(Window::window_ptr, &Window::ScreenDimensions::screenwidth, &Window::ScreenDimensions::screenheight);
		//int gridHeight = Window::ScreenDimensions::screenheight / 11; //rows are 11

		//current hard code way
		int gridHeight = 100;
		Player::playerpos.y += gridHeight;
		if (playerpos.y > 900)
		{
			playerpos.y = 900;
		}
		else
		{
			sp->transformation.position.y += gridHeight; //down is positive for some reason
		}

	}

	void Player::restart()
	{
		sp->transformation.position.x = playerpos_restart.x;
		sp->transformation.position.y = playerpos_restart.y;
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
}