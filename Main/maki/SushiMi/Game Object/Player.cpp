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
#include "../Engine/TileMap/Map.h"
#include "../Headers/SceneManager.h"

//static Window win; //create a external window variable to pass through data

 //adjust according to tile-map size

float Core::Map::tile_width = 0;
float Core::Map::tile_height = 0;
namespace Core
{

	Player::Player()
	{

		sp = new Sprite("../textures/spritesheet/spritesheet.png");
		sp->transformation.Position = glm::vec2(playerpos.x, playerpos.y);
		sp->transformation.Scale = glm::vec2(100, 100);

		sp->Add_animation("../textures/spritesheet/Idle.txt");
		sp->Add_animation("../textures/spritesheet/Run.txt");

		current_anim = Idle;
	}

	Player::Player(const char* spriteFilepath, float* spritePos, float* spriteScale, std::vector<std::string> const& animationList) {
		sp = new Sprite(spriteFilepath);
		sp->transformation.Position = glm::vec2(spritePos[0], spritePos[1]);
		sp->transformation.Scale = glm::vec2(spriteScale[0], spriteScale[1]);

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
		if (sp->transformation.Scale.x > 0)
			sp->transformation.Scale.x *= 1;

		current_anim = Run;

		std::cout << "player move left\n";

		//Best way: ensure grid is consistent with all window sizes
		//glfwGetWindowSize(Window::window_ptr, &Window::ScreenDimensions::screenwidth, &Window::ScreenDimensions::screenheight);
		//int gridWidth = Window::ScreenDimensions::screenwidth / 19; //columns are 19

		//current hard code way
		playerpos.x -= Map::tile_width;

		player_grid_pos.x--;
		
		sp->transformation.Position.x -= Map::tile_width;
	}

	void Player::move_right()
	{
		if (sp->transformation.Scale.x < 0)
			sp->transformation.Scale.x *= -1;

		current_anim = Run;

		//Best way: ensure grid is consistent with all window sizes
		//glfwGetWindowSize(Window::window_ptr, &Window::ScreenDimensions::screenwidth, &Window::ScreenDimensions::screenheight);
		//int gridWidth = Window::ScreenDimensions::screenwidth / 19; //columns are 19

		//current hard code way
		playerpos.x += Map::tile_width;

		player_grid_pos.x++;

		sp->transformation.Position.x += Map::tile_width;
	}

	void Player::move_up()
	{
		if (sp->transformation.Scale.y > 0)
			sp->transformation.Scale.y *= 1;
		//std::cout << "you are pressing up" << std::endl;

		current_anim = Run;

		//Best way: ensure grid is consistent with all window sizes
		//glfwGetWindowSize(Window::window_ptr, &Window::ScreenDimensions::screenwidth, &Window::ScreenDimensions::screenheight);
		//int gridHeight = Window::ScreenDimensions::screenheight / 11; //rows are 11

		player_grid_pos.y--;

		//current hard code way
		Player::playerpos.y -= Core::Map::tile_height;
		if (playerpos.y < 0)
		{
			playerpos.y = 0;
		}
		else
		{
			sp->transformation.Position.y -= Core::Map::tile_height; //up is negative for some reason
		}
	}

	void Player::move_down()
	{
		if (sp->transformation.Scale.y < 0)
			sp->transformation.Scale.y *= -1;

		current_anim = Run;

		//Best way: ensure grid is consistent with all window sizes
		//glfwGetWindowSize(Window::window_ptr, &Window::ScreenDimensions::screenwidth, &Window::ScreenDimensions::screenheight);
		//int gridHeight = Window::ScreenDimensions::screenheight / 11; //rows are 11

		player_grid_pos.y++;

		Player::playerpos.y += Core::Map::tile_height;

		sp->transformation.Position.y += Core::Map::tile_height; //down is positive for some reason
	}

	void Player::restart()
	{
		/*DOESNT WORK, TEXTURES WILL GO INTO SHIT

		SceneManager::destroyTile();
		SceneManager::destroyIngr();
		SceneManager::destroyTrap();
		SceneManager::destroyGoal();
		Map::initMap("../TileMap/level1.txt");
		*/
		/*IF PLAYER STUCK IN SINKHOLE*/
		/*if (Map::gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] == 99)
		{
			/*sinkhole goes back to norm*/
			/*doesnt work for now, will figure out
			SceneManager::destroyTrap();
			SceneManager::trap = new Sprite("../textures/Tiles/Trap/Sinkhole0_1.png");

			Map::gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = 4;
			sp->transformation.Position.x = playerpos_restart.x;
			sp->transformation.Position.y = playerpos_restart.y;
			*/
		/*this is working, FOR NOW*/

/*if (Map::gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] == 99)
		{*/ //i commented out this line as its affecting Restart - thea

		//set the initial grid that the player is leaving back to blank 
		Map::gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = 0; 
		sp->transformation.Position.x = playerpos_restart.x;
		sp->transformation.Position.y = playerpos_restart.y;
		Window::player->player_grid_pos.x = Window::player->player_initial_grid_pos.x;
		Window::player->player_grid_pos.y = Window::player->player_initial_grid_pos.y;

		//set the new grid the player is now at to contain player
		Map::gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = 2;
		//}


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