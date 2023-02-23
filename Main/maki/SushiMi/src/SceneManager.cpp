#include "../Headers/SceneManager.h"
#include "../Engine//Serialiser/JSONSerializer.h"
#include "../Engine/Shaders/ShaderLibrary.h"
#include "../Engine/TileMap/Map.h"

namespace Core
{
	float alpha = 1.0f;
	std::vector<std::pair<wall_type, Sprite*>> tilecontainer;
	std::vector<std::pair<grid_number, Sprite*>> ingredientcontainer;

	SceneManager::SceneManager()
	{
		/*tile = nullptr;
		ingredient1 = nullptr;
		ingredient2 = nullptr;
		trap = nullptr;
		goal1 = nullptr;
		goal2 = nullptr;
		cover1 = nullptr;*/
		howtoplay_overlay1 = nullptr;
		win_overlay = nullptr;
		player_stuck = nullptr;
		rows = cols = tileHeight = tileWidth = 0;
		SceneManager::starttime = SceneManager::endtime = SceneManager::delta = 0;
		rec = nullptr;
	}

	SceneManager::~SceneManager()
	{

	}

	void SceneManager::Init()
	{

	}

	void SceneManager::Update(const double dt)
	{
		endtime = glfwGetTime();
		delta = (endtime - starttime) / 2;
	}

	void SceneManager::RegisterComponent(std::unordered_map<std::string, Object::GameObject*> ObjectContainer)
	{

	}
	void SceneManager::restartLevel()
	{
		if (tilecontainer.size() > 0 && ingredientcontainer.size() > 0)
		{
			Map::ResetMap();
		}
		Window::loaded = false;
		//SceneManager::tilecontainer.clear();
		//SceneManager::ingredientcontainer.clear();
		Window::player->restart();
		Window::player->playerpos.x = Window::player->playerpos_restart.x;
		Window::player->playerpos.y = Window::player->playerpos_restart.y;
		Window::gameIsPaused = false;
		Window::questProgress = 0;
		amt_of_win_conditions = 0;
		//missing: restart sinkhole, restart sushi plate pods
		Window::isPlayerinSinkhole = false;
		//reset ingredient pos
		for (auto& ingredient : ingredientcontainer)
		{
			ingredient.second->restart();
		}


	}
	//R key for restart
	// update by thea: i've written a new restart function
	//					that just restarts the position, rather than
	//					this one that deletes an old player and "new"s
	//					to create a new one (this is very resource intensive
	//					and prone to memory leaks)



	void SceneManager::loadTile(int x, int y, const std::pair<wall_type, Sprite*>& tile)
	{

		tile.second->transformation.Position = glm::vec2(x, y);
		tile.second->transformation.Scale = glm::vec2(getTileWidth(), getTileHeight());

		tilecontainer.push_back(tile);


		std::cout << std::endl;
		std::cout << "****************** added a tile! tilecontainer size: " << tilecontainer.size() << std::endl;
	}

	void SceneManager::loadIngr(int x, int y, int posX, int posY, const std::pair<grid_number, Sprite*>& ingredient)
	{
		/*
		int width, height;
		glfwGetWindowSize(Window::window_ptr, &width, &height);
		*/
		ingredient.second->transformation.Position = glm::vec2(x, y);
		ingredient.second->transformation.Scale = glm::vec2(getTileWidth(), getTileHeight());

		ingredient.second->transformation.grid_pos = { posX, posY };

		ingredientcontainer.push_back(ingredient);
		std::cout << std::endl;
		std::cout << "****************** added an ingredient! ingredientcontainer size: " << ingredientcontainer.size() << std::endl;
	}

	void SceneManager::loadIngr_initPos(int x, int y, int posX, int posY, const std::pair<grid_number, Sprite*>& ingrposition)
	{
		ingrposition.second->transformation.grid_pos = { x, y };
		ingrposition.second->transformation.Scale = glm::vec2(getTileWidth(), getTileHeight());

		ingrposition.second->transformation.grid_pos = { x, y };

		ingredient_starting_pos.insert(ingrposition);
	}

	/*void SceneManager::loadIngr2(int x, int y)
	{

		ingredient2->transformation.Position = glm::vec2(x, y);
		ingredient2->transformation.Scale = glm::vec2(100, 100);
	}*/

	/*void SceneManager::loadTrap(int x, int y)
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
	}*/

	void SceneManager::loadPlayer_Stuck(int x, int y)
	{
		player_stuck->transformation.Position = glm::vec2(x, y);
		player_stuck->transformation.Scale = glm::vec2(90, 90);
	}

	void SceneManager::loadHowToOverlay(int x, int y)
	{
		int screenwidth = 0, screenheight = 0;
		glfwGetWindowSize(Window::window_ptr, &screenwidth, &screenheight);

		howtoplay_overlay1->transformation.Position = glm::vec2(x, y);
		howtoplay_overlay1->transformation.Scale = glm::vec2(screenwidth, screenheight);
		howtoplay_overlay2->transformation.Position = glm::vec2(x, y);
		howtoplay_overlay2->transformation.Scale = glm::vec2(screenwidth, screenheight);
		howtoplay_overlay3->transformation.Position = glm::vec2(x, y);
		howtoplay_overlay3->transformation.Scale = glm::vec2(screenwidth, screenheight);
		howtoplay_overlay4->transformation.Position = glm::vec2(x, y);
		howtoplay_overlay4->transformation.Scale = glm::vec2(screenwidth, screenheight);
		howtoplay_overlay5->transformation.Position = glm::vec2(x, y);
		howtoplay_overlay5->transformation.Scale = glm::vec2(screenwidth, screenheight);
	}
	void SceneManager::loadSettings()
	{
		int screenwidth = 0, screenheight = 0;
		glfwGetWindowSize(Window::window_ptr, &screenwidth, &screenheight);
		//settings
		settings_page->transformation.Position = glm::vec2(screenwidth * 0.25, screenheight * 0.25);
		settings_page->transformation.Scale = glm::vec2(screenwidth * 0.47, screenheight * 0.5);

		//credits
		credits_page->transformation.Position = glm::vec2(0, 0);
		credits_page->transformation.Scale = glm::vec2(screenwidth, screenheight);
	}
	void SceneManager::loadWinOverlay(int x, int y)
	{
		win_overlay->transformation.Position = glm::vec2(x, y);
		win_overlay->transformation.Scale = glm::vec2(1049, 573);
	}

	void SceneManager::loadCutscene(int x, int y)
	{
		int screenwidth = 0, screenheight = 0;
		glfwGetWindowSize(Window::window_ptr, &screenwidth, &screenheight);

		frame1->transformation.Position = glm::vec2(0, 0);
		frame1->transformation.Scale = glm::vec2(screenwidth, screenheight);

		frame2->transformation.Position = glm::vec2(0, 0);
		frame2->transformation.Scale = glm::vec2(screenwidth, screenheight);


		frame3->transformation.Position = glm::vec2(0, 0);
		frame3->transformation.Scale = glm::vec2(screenwidth, screenheight);


		frame4->transformation.Position = glm::vec2(0, 0);
		frame4->transformation.Scale = glm::vec2(screenwidth, screenheight);


		frame5->transformation.Position = glm::vec2(0, 0);
		frame5->transformation.Scale = glm::vec2(screenwidth, screenheight);


		frame6->transformation.Position = glm::vec2(0, 0);
		frame6->transformation.Scale = glm::vec2(screenwidth, screenheight);


		frame7->transformation.Position = glm::vec2(0, 0);
		frame7->transformation.Scale = glm::vec2(screenwidth, screenheight);


		frame8->transformation.Position = glm::vec2(0, 0);
		frame8->transformation.Scale = glm::vec2(screenwidth, screenheight);

	}

	void SceneManager::loadLevelSelect(int x, int y)
	{
		int screenwidth = 0, screenheight = 0;
		glfwGetWindowSize(Window::window_ptr, &screenwidth, &screenheight);

		level_select->transformation.Position = glm::vec2(0, 0);
		level_select->transformation.Scale = glm::vec2(screenwidth, screenheight);
	}

	void SceneManager::loadRP_Dialogue()
	{
		int screenwidth = 0, screenheight = 0;
		glfwGetWindowSize(Window::window_ptr, &screenwidth, &screenheight);

		if (Window::dialogue_style >= static_cast<int>(Window::dialogue::T1) && Window::dialogue_style <= static_cast<int>(Window::dialogue::L3))
		{
			riceplain_dialogue->transformation.Position = glm::vec2(screenwidth * 0.15f, screenheight * 0.7f);
			riceplain_dialogue->transformation.Scale = glm::vec2(screenwidth * 0.7f, screenheight * 0.3f);

		}
		else if (Window::dialogue_style >= static_cast<int>(Window::dialogue::L4) && Window::dialogue_style <= static_cast<int>(Window::dialogue::L6))
		{
			gunkan_dialogue->transformation.Position = glm::vec2(screenwidth * 0.15f, screenheight * 0.7f);
			gunkan_dialogue->transformation.Scale = glm::vec2(screenwidth * 0.7f, screenheight * 0.3f);
		}
	}
	
	void SceneManager::drawBlackOverlay()
	{
		SceneManager::loadRect(0, 0);

		currentAlpha = std::lerp(currentAlpha, targetAlpha, 0.016f);
		SceneManager::drawRect(currentAlpha);
		/*
		std::cout << "Alpha: " << currentAlpha << std::endl;
		*/
	}

	/*draw functions*/
	void SceneManager::drawTile()
	{
		for (auto& tile : tilecontainer)
		{
			Shaders->Textured_Shader()->Send_Mat4("model_matrx", tile.second->transformation.Get());
			glUniform1f(glGetUniformLocation(Shaders->Textured_Shader()->get_hdl(), "alpha"), alpha);
			tile.second->draw();
		}
	}

	void SceneManager::drawBox()
	{
	}

	void SceneManager::drawIngr()
	{
		for (auto& ingredient : ingredientcontainer)
		{
			Shaders->Textured_Shader()->Send_Mat4("model_matrx", ingredient.second->transformation.Get());
			glUniform1f(glGetUniformLocation(Shaders->Textured_Shader()->get_hdl(), "alpha"), alpha);

			if (ingredient.second->isSpriteSheet)
			{
				ingredient.second->draw(delta, ingredient.second->curr_anim);
			}
			else
			{
				ingredient.second->draw();
			}

		}
	}

	/*void SceneManager::drawIngr1()
	{
		Shaders->Textured_Shader()->Send_Mat4("model_matrx", ingredient1->transformation.Get());
		ingredient1->draw();
	}

	void SceneManager::drawIngr2()
	{
		for (auto& ingredient : ingredientcontainer)
		{
			Shaders->Textured_Shader()->Send_Mat4("model_matrx", ingredient->transformation.Get());
			ingredient->draw();
		}
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
	}*/

	void SceneManager::drawPlayer_Stuck()
	{
		Shaders->Textured_Shader()->Send_Mat4("model_matrx", player_stuck->transformation.Get());
		glUniform1f(glGetUniformLocation(Shaders->Textured_Shader()->get_hdl(), "alpha"), alpha);
		player_stuck->draw();
	}

	void SceneManager::drawHowToOverlay()
	{
		switch (Window::HowToPlayPage)
		{
		case 0:
		{
			Shaders->Textured_Shader()->Send_Mat4("model_matrx", howtoplay_overlay1->transformation.Get());
			glUniform1f(glGetUniformLocation(Shaders->Textured_Shader()->get_hdl(), "alpha"), alpha);
			howtoplay_overlay1->draw();
			break;
		}
		case 1:
		{
			Shaders->Textured_Shader()->Send_Mat4("model_matrx", howtoplay_overlay2->transformation.Get());
			glUniform1f(glGetUniformLocation(Shaders->Textured_Shader()->get_hdl(), "alpha"), alpha);
			howtoplay_overlay2->draw();
			break;
		}
		case 2:
		{
			Shaders->Textured_Shader()->Send_Mat4("model_matrx", howtoplay_overlay3->transformation.Get());
			glUniform1f(glGetUniformLocation(Shaders->Textured_Shader()->get_hdl(), "alpha"), alpha);
			howtoplay_overlay3->draw();
			break;
		}
		case 3:
		{
			Shaders->Textured_Shader()->Send_Mat4("model_matrx", howtoplay_overlay4->transformation.Get());
			glUniform1f(glGetUniformLocation(Shaders->Textured_Shader()->get_hdl(), "alpha"), alpha);
			howtoplay_overlay4->draw();
			break;
		}
		case 4:
		{
			Shaders->Textured_Shader()->Send_Mat4("model_matrx", howtoplay_overlay5->transformation.Get());
			glUniform1f(glGetUniformLocation(Shaders->Textured_Shader()->get_hdl(), "alpha"), alpha);
			howtoplay_overlay5->draw();
			break;
		}
		}
	}
	void SceneManager::drawSettings()
	{
		//if settings only 
		if (Window::isCredits == false)
		{
			Shaders->Textured_Shader()->Send_Mat4("model_matrx", settings_page->transformation.Get());
			glUniform1f(glGetUniformLocation(Shaders->Textured_Shader()->get_hdl(), "alpha"), alpha);
			settings_page->draw();

		}
		else //isCredits == true
		{
			//if credits only
			Shaders->Textured_Shader()->Send_Mat4("model_matrx", credits_page->transformation.Get());
			glUniform1f(glGetUniformLocation(Shaders->Textured_Shader()->get_hdl(), "alpha"), alpha);
			credits_page->draw();

		}
	}
	void SceneManager::drawWinOverlay()
	{
		Shaders->Textured_Shader()->use();
		Shaders->Textured_Shader()->Send_Mat4("model_matrx", win_overlay->transformation.Get());
		glUniform1f(glGetUniformLocation(Shaders->Textured_Shader()->get_hdl(), "alpha"), alpha);
		win_overlay->draw();
	}

	void SceneManager::drawCutscene()
	{
		switch (Window::CutscenePage)
		{
		case 0:
		{
			Shaders->Textured_Shader()->Send_Mat4("model_matrx", frame1->transformation.Get());
			glUniform1f(glGetUniformLocation(Shaders->Textured_Shader()->get_hdl(), "alpha"), alpha);
			frame1->draw();
			break;
		}
		case 1:
		{
			Shaders->Textured_Shader()->Send_Mat4("model_matrx", frame2->transformation.Get());
			glUniform1f(glGetUniformLocation(Shaders->Textured_Shader()->get_hdl(), "alpha"), alpha);
			frame2->draw();
			break;
		}
		case 2:
		{
			Shaders->Textured_Shader()->Send_Mat4("model_matrx", frame3->transformation.Get());
			glUniform1f(glGetUniformLocation(Shaders->Textured_Shader()->get_hdl(), "alpha"), alpha);
			frame3->draw();
			break;
		}
		case 3:
		{
			Shaders->Textured_Shader()->Send_Mat4("model_matrx", frame4->transformation.Get());
			glUniform1f(glGetUniformLocation(Shaders->Textured_Shader()->get_hdl(), "alpha"), alpha);
			frame4->draw();
			break;
		}
		case 4:
		{
			Shaders->Textured_Shader()->Send_Mat4("model_matrx", frame5->transformation.Get());
			glUniform1f(glGetUniformLocation(Shaders->Textured_Shader()->get_hdl(), "alpha"), alpha);
			frame5->draw();
			break;
		}
		case 5:
		{
			Shaders->Textured_Shader()->Send_Mat4("model_matrx", frame6->transformation.Get());
			glUniform1f(glGetUniformLocation(Shaders->Textured_Shader()->get_hdl(), "alpha"), alpha);
			frame6->draw();
			break;
		}
		case 6:
		{
			Shaders->Textured_Shader()->Send_Mat4("model_matrx", frame7->transformation.Get());
			glUniform1f(glGetUniformLocation(Shaders->Textured_Shader()->get_hdl(), "alpha"), alpha);
			frame7->draw();
			break;
		}
		case 7:
		{
			Shaders->Textured_Shader()->Send_Mat4("model_matrx", frame8->transformation.Get());
			glUniform1f(glGetUniformLocation(Shaders->Textured_Shader()->get_hdl(), "alpha"), alpha);
			frame8->draw();
			break;
		}

		}
	}

	void SceneManager::drawLevelSelect()
	{
		Shaders->Textured_Shader()->Send_Mat4("model_matrx", level_select->transformation.Get());
		glUniform1f(glGetUniformLocation(Shaders->Textured_Shader()->get_hdl(), "alpha"), alpha);
		level_select->draw();
	}

	void SceneManager::drawRP_Dialogue()
	{
		if (Window::dialogue_style >= static_cast<int>(Window::dialogue::T1) && Window::dialogue_style <= static_cast<int>(Window::dialogue::L3))
		{
			Shaders->Textured_Shader()->Send_Mat4("model_matrx", riceplain_dialogue->transformation.Get());
			riceplain_dialogue->draw();

		}
		else if (Window::dialogue_style >= static_cast<int>(Window::dialogue::L4) && Window::dialogue_style <= static_cast<int>(Window::dialogue::L6))
		{
			Shaders->Textured_Shader()->Send_Mat4("model_matrx", gunkan_dialogue->transformation.Get());
			gunkan_dialogue->draw();
		}
	}

	void SceneManager::loadRect(int x, int y)
	{
		rec->transformation.Position = glm::vec2(x, y);
		rec->transformation.Scale = glm::vec2(1920, 1200);
	}

	void SceneManager::drawRect(float alpha)
	{
		/*This one draws the black background completely fine, but it is without the Alpha variable */
		Shaders->Textured_Shader()->Send_Mat4("model_matrx", rec->transformation.Get());

		glUniform1f(glGetUniformLocation(Shaders->Textured_Shader()->get_hdl(), "alpha"), alpha);
		rec->draw();
		/*
		Shaders->Alpha_Shader()->use();
		float alpha = 1.f;
		Shaders->Alpha_Shader()->Send_Mat4("model_matrx", rec->transformation.Get());
		glUniform1f(glGetUniformLocation(Shaders->Alpha_Shader()->get_hdl(), "alpha"), alpha);
		rec->draw();
		*/


	}
	constexpr float OPAQUE_ALPHA = 1.0f;
	constexpr float TRANSPARENT_ALPHA = 0.0f;
	constexpr float FADE_SPEED = .8f;
	void SceneManager::FadeIn()
	{
		SceneManager::loadRect(0, 0);
		/*fading works!!!!*/
		float targetAlpha = 0.0f;
		targetAlpha = 1.0f;
		alpha = std::lerp(alpha, targetAlpha, (1.0f / 60.0f) * FADE_SPEED);

		SceneManager::drawRect(alpha);
	}
	void SceneManager::FadeOut()
	{
		targetAlpha = 0.0f;
	}

	/*destroy functions*/
	void SceneManager::destroyTile()
	{
		if (tilecontainer.size() != 0)
		{
			for (auto it : tilecontainer)
			{
				delete it.second;
			}
		}

		tilecontainer.clear();
	}
	void SceneManager::destroyIngr()
	{
		if (ingredientcontainer.size() != 0)
		{
			for (auto it : ingredientcontainer)
			{
				delete it.second;
			}
		}

		ingredientcontainer.clear();
	}
	/*void SceneManager::destroyTrap()
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
	}*/

	/*void SceneManager::destroyCover1()
	{
		delete cover1;
	}

	void SceneManager::destroyCover2()
	{
	}*/

	void SceneManager::destroyHowToOverlay()
	{
		delete howtoplay_overlay1;
		delete howtoplay_overlay2;
		delete howtoplay_overlay3;
		delete howtoplay_overlay4;
		delete howtoplay_overlay5;
	}

	void SceneManager::destroySettings()
	{
		delete settings_page;
		delete credits_page;
	}

	void SceneManager::destroyWinOverlay()
	{
		delete win_overlay;
	}

	void SceneManager::destroyCutscene()
	{
		delete frame1;
		delete frame2;
		delete frame3;
		delete frame4;
		delete frame5;
		delete frame6;
		delete frame7;
		delete frame8;
	}

	void SceneManager::destroyLevelSelect()
	{
		delete level_select;
	}

	void SceneManager::destroyRP_Dialogue()
	{
		delete riceplain_dialogue;
		delete gunkan_dialogue;
	}

	void SceneManager::setTileDimension(unsigned int Width, unsigned int Height)
	{
		tileWidth = Width;
		tileHeight = Height;
	}

	unsigned int SceneManager::getTileWidth()
	{
		return tileWidth;
	}

	unsigned int SceneManager::getTileHeight()
	{
		return tileHeight;
	}

	void SceneManager::destroyPlayer_Stuck()
	{
		delete player_stuck;
	}

}