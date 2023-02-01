#include "../Headers/SceneManager.h"
#include "../Engine//Serialiser/JSONSerializer.h"
#include "../Engine/Shaders/ShaderLibrary.h"

namespace Core
{
	SceneManager::SceneManager()
	{
		tile = nullptr;
		ingredient1 = nullptr;
		ingredient2 = nullptr;
		trap = nullptr;
		goal1 = nullptr;
		goal2 = nullptr;
		cover1 = nullptr;
		pause_overlay = nullptr;
		win_overlay = nullptr;
		player_stuck = nullptr;
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

	void SceneManager::loadIngr1(int x, int y)
	{

		ingredient1->transformation.Position = glm::vec2(x, y);
		ingredient1->transformation.Scale = glm::vec2(100, 100);
	}
	void SceneManager::loadIngr2(int x, int y)
	{

		ingredient2->transformation.Position = glm::vec2(x, y);
		ingredient2->transformation.Scale = glm::vec2(100, 100);
	}

	void SceneManager::loadTrap(int x, int y)
	{

		trap->transformation.Position = glm::vec2(x, y);
		trap->transformation.Scale = glm::vec2(100, 100);
	}

	void SceneManager::loadGoal1(int x, int y)
	{

		goal1->transformation.Position = glm::vec2(x, y);
		goal1->transformation.Scale = glm::vec2(100, 100);
	}
	void SceneManager::loadGoal2(int x, int y)
	{

		goal2->transformation.Position = glm::vec2(x, y);
		goal2->transformation.Scale = glm::vec2(100, 100);
	}
	void SceneManager::loadCover1(int x, int y)
	{
		cover1->transformation.Position = glm::vec2(x, y);
		cover1->transformation.Scale = glm::vec2(100, 100);
	}

	void SceneManager::loadPlayer_Stuck(int x, int y)
	{
		player_stuck->transformation.Position = glm::vec2(x, y);
		player_stuck->transformation.Scale = glm::vec2(90, 90);
	}
	
	void SceneManager::loadPauseOverlay(int x, int y)
	{
		int screenwidth = 0, screenheight = 0;
		glfwGetWindowSize(Window::window_ptr, &screenwidth, &screenheight);
		/*x = screenwidth * 0.5;
		y = screenheight * 0.5;*/
		pause_overlay->transformation.Position = glm::vec2(x, y);
		pause_overlay->transformation.Scale = glm::vec2(screenwidth, screenheight);
	}
	void SceneManager::loadWinOverlay(int x, int y)
	{
		win_overlay->transformation.Position = glm::vec2(x, y);
		win_overlay->transformation.Scale = glm::vec2(1049, 573);
	}
	/*draw functions*/
	void SceneManager::drawTile()
	{
		Shaders->Textured_Shader()->Send_Mat4("model_matrx", tile->transformation.Get());
		tile->draw();
	}

	void SceneManager::drawIngr1()
	{
		Shaders->Textured_Shader()->Send_Mat4("model_matrx", ingredient1->transformation.Get());
		ingredient1->draw();
	}
	void SceneManager::drawIngr2()
	{
		Shaders->Textured_Shader()->Send_Mat4("model_matrx", ingredient2->transformation.Get());
		ingredient2->draw();
	}
	void SceneManager::drawTrap()
	{
		Shaders->Textured_Shader()->Send_Mat4("model_matrx", trap->transformation.Get());
		trap->draw();
	}
	void SceneManager::drawGoal1()
	{
		Shaders->Textured_Shader()->Send_Mat4("model_matrx", goal1->transformation.Get());
		goal1->draw();
	}
	void SceneManager::drawGoal2()
	{
		Shaders->Textured_Shader()->Send_Mat4("model_matrx", goal2->transformation.Get());
		goal2->draw();
	}
	void SceneManager::drawCover1()
	{
		Shaders->Textured_Shader()->Send_Mat4("model_matrx", cover1->transformation.Get());
		cover1->draw();
	}

	void SceneManager::drawPlayer_Stuck()
	{
		Shaders->Textured_Shader()->Send_Mat4("model_matrx", player_stuck->transformation.Get());
		player_stuck->draw();
	}
	
	void SceneManager::drawPauseOverlay()
	{
		Shaders->Textured_Shader()->Send_Mat4("model_matrx", pause_overlay->transformation.Get());
		pause_overlay->draw();
	}
	void SceneManager::drawWinOverlay()
	{
		Shaders->Textured_Shader()->Send_Mat4("model_matrx", win_overlay->transformation.Get());
		win_overlay->draw();
	}
	/*destroy functions*/
	void SceneManager::destroyTile()
	{
		delete tile;
	}
	void SceneManager::destroyIngr()
	{
		delete ingredient1;
		delete ingredient2;
	}
	void SceneManager::destroyTrap()
	{
		delete trap;
	}
	void SceneManager::destroyGoal1()
	{
		delete goal1;
	}
	void SceneManager::destroyGoal2()
	{
		delete goal2;
	}

	void SceneManager::destroyCover1()
	{
		delete cover1;
	}

	void SceneManager::destroyCover2()
	{
	}

	void SceneManager::destroyPauseOverlay()
	{
		delete pause_overlay;
	}

	void SceneManager::destroyWinOverlay()
	{
		delete win_overlay;
	}

	void SceneManager::destroyPlayer_Stuck()
	{
		delete player_stuck;
	}

}