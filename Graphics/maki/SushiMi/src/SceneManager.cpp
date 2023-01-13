#include "../Headers/SceneManager.h"

SceneManager::SceneManager()
{
	tile = nullptr;
	rows = cols = tileHeight = tileWidth = 0;
}

SceneManager::~SceneManager()
{

}
//R key for restart
void SceneManager::restartLevel()
{
	player->~Player(); // destroy player
	player = new Player(); //respawn player to start position
}

void SceneManager::loadTile()
{
	tile = new Sprite("../textures/doge.PNG");
	tile->transformation.position = glm::vec2(-100, 0);
	tile->transformation.scale = glm::vec2(150, 150);
}

void SceneManager::drawTile()
{
	tile->draw();
}