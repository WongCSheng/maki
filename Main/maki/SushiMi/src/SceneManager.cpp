#include "../Headers/SceneManager.h"
#include "../Engine//Serialiser/JSONSerializer.h"
#include "../Engine/Shaders/ShaderLibrary.h"

SceneManager::SceneManager()
{
	tile = nullptr;
	rows = cols = tileHeight = tileWidth = 0;
}

SceneManager::~SceneManager()
{

}
//R key for restart
// update by thea: i've written a new restart function
//					that just restarts the position, rather than
//					this one that deletes an old player and "new"s
//					to create a new one (this is very resource intensive
//					and prone to memory leaks)

//void SceneManager::restartLevel()
//{
//	player->~Player(); // destroy player
//	player = new Player(); //respawn player to start position
//}

void SceneManager::loadTile()
{
	tile = new Sprite("../textures/doge.PNG");
	tile->transformation.position = glm::vec2(100, 0);
	tile->transformation.scale = glm::vec2(100, 100);
}

void SceneManager::drawTile()
{
	Shaders->Textured_Shader()->Send_Mat4("model_matrx", tile->transformation.Get());
	tile->draw();
}

void SceneManager::destroyTile()
{
	delete tile;
}
