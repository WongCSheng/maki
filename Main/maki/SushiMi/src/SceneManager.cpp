#include "../Headers/SceneManager.h"
#include "../Engine//Serialiser/JSONSerializer.h"
#include "../Engine/Shaders/ShaderLibrary.h"

namespace Core
{
	SceneManager::SceneManager()
	{
		tile = nullptr;
		rows = cols = tileHeight = tileWidth = 0;
	}

	SceneManager::~SceneManager()
	{

	}

	void SceneManager::Init()
	{

	}

	void SceneManager::Update(const double dt)
	{

	}

	void SceneManager::RegisterComponent(std::unordered_map<std::string, Object::GameObject*> ObjectContainer)
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

	void SceneManager::loadTile(int x, int y)
	{
		tile->transformation.Position = glm::vec2(x, y);
		tile->transformation.Scale = glm::vec2(150, 150);
	}

	void SceneManager::loadObj(int x, int y)
	{
		obj->transformation.Position = glm::vec2(x, y);
		obj->transformation.Scale = glm::vec2(150, 150);
	}

	void SceneManager::drawTile()
	{
		Shaders->Textured_Shader()->Send_Mat4("model_matrx", tile->transformation.Get());
		tile->draw();
	}

	void SceneManager::drawObj()
	{
		Shaders->Textured_Shader()->Send_Mat4("model_matrx", obj->transformation.Get());
		obj->draw();
	}

	void SceneManager::destroyTile()
	{
		delete tile;
	}
	void SceneManager::destroyObj()
	{
		delete obj;
	}
}