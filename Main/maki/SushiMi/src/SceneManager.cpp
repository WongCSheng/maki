#include "../Headers/SceneManager.h"
#include "../Engine//Serialiser/JSONSerializer.h"
#include "../Engine/Shaders/ShaderLibrary.h"

namespace Core
{
	SceneManager::SceneManager()
	{
		tile = nullptr;
		ingredient = nullptr;
		trap = nullptr;
		goal = nullptr;
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
		tile->transformation.Scale = glm::vec2(105, 105);
	}

	void SceneManager::loadIngr(int x, int y)
	{

		ingredient->transformation.Position = glm::vec2(x, y);
		ingredient->transformation.Scale = glm::vec2(100, 100);
	}

	void SceneManager::loadTrap(int x, int y)
	{

		trap->transformation.Position = glm::vec2(x, y);
		trap->transformation.Scale = glm::vec2(100, 100);
	}

	void SceneManager::loadGoal(int x, int y)
	{

		goal->transformation.Position = glm::vec2(x, y);
		goal->transformation.Scale = glm::vec2(100, 100);
	}
	/*draw functions*/
	void SceneManager::drawTile()
	{
		Shaders->Textured_Shader()->Send_Mat4("model_matrx", tile->transformation.Get());
		tile->draw();
	}

	void SceneManager::drawIngr()
	{
		Shaders->Textured_Shader()->Send_Mat4("model_matrx", ingredient->transformation.Get());
		ingredient->draw();
	}
	void SceneManager::drawTrap()
	{
		Shaders->Textured_Shader()->Send_Mat4("model_matrx", trap->transformation.Get());
		trap->draw();
	}
	void SceneManager::drawGoal()
	{
		Shaders->Textured_Shader()->Send_Mat4("model_matrx", goal->transformation.Get());
		goal->draw();
	}
	/*destroy functions*/
	void SceneManager::destroyTile()
	{
		delete tile;
	}
	void SceneManager::destroyIngr()
	{
		delete ingredient;
	}
	void SceneManager::destroyTrap()
	{
		delete trap;
	}
	void SceneManager::destroyGoal()
	{
		delete goal;
	}

}