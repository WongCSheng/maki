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
		rec = nullptr;
	}

	SceneManager::~SceneManager()
	{

	}

	void SceneManager::Init()
	{
	}

	void SceneManager::Update(const double)
	{

	}

	void SceneManager::RegisterComponent(std::unordered_map<std::string, Object::GameObject*> ObjectContainer)
	{

	}
	void SceneManager::restartLevel()
	{
		if (tilecontainer.size() > 0 && ingredientcontainer.size() > 0 && in_sinkhole.size() > 0)
		{
			Map::ResetMap();
		}
		Window::loaded = false;
		//SceneManager::tilecontainer.clear();
		//SceneManager::ingredientcontainer.clear();
		Window::player->restart();
		Window::player->playerpos.x = static_cast<float>(Window::player->playerpos_restart.x);
		Window::player->playerpos.y = static_cast<float>(Window::player->playerpos_restart.y);
		Window::gameIsPaused = false;
		Window::questProgress = 0;
		amt_of_win_conditions = 0;
		//missing: restart sinkhole, restart sushi plate pods
		Window::isPlayerinSinkhole = false;
		//reset ingredient pos
		for (auto& ingredient : ingredientcontainer)
		{
			ingredient.second->restart();
			ingredient.second->count = 0;
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
		tile.second->transformation.Scale = glm::vec2(getTileWidth() * 1.01f, getTileHeight() * 1.01f);

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

		//set all counters to 0 first, because soya might be activated twice
		ingredient.second->count = 0;
		ingredient.second->alpha = 1.f;

		ingredientcontainer.push_back(ingredient);
		std::cout << std::endl;
		std::cout << "****************** added an ingredient! ingredientcontainer size: " << ingredientcontainer.size() << std::endl;
	}
	/*
	void SceneManager::loadRice(int x, int y, int posX, int posY, const std::pair<Rice, Sprite*>& ingredient)
	{
		ingredient.second->transformation.Position = glm::vec2(x, y);
		ingredient.second->transformation.Scale = glm::vec2(getTileWidth(), getTileHeight());

		ingredient.second->transformation.grid_pos = { posX, posY };
		ricecontainer.push_back(ingredient);
	}
	*/


	void SceneManager::loadIngr_initPos(int x, int y, int /*posX*/, int /*posY*/, const std::pair<grid_number, Sprite*>& ingrposition)
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

	void SceneManager::loadCutscene()
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

		level_select->transformation.Position = glm::vec2(x, y);
		level_select->transformation.Scale = glm::vec2(screenwidth, screenheight);
	}

	void SceneManager::load_Dialogue()
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
		else if (Window::dialogue_style >= static_cast<int>(Window::dialogue::L7) && Window::dialogue_style <= static_cast<int>(Window::dialogue::L9))
		{
			fishingvillage_dialogue->transformation.Position = glm::vec2(screenwidth * 0.15f, screenheight * 0.7f);
			fishingvillage_dialogue->transformation.Scale = glm::vec2(screenwidth * 0.7f, screenheight * 0.3f);
		}
	}

	void SceneManager::load_Wood_BG()
	{
		int screenwidth = 0, screenheight = 0;
		glfwGetWindowSize(Window::window_ptr, &screenwidth, &screenheight);
		wooden_bg->transformation.Position = glm::vec2(screenwidth * 0.09f, screenheight * 0.08f);
		wooden_bg->transformation.Scale = glm::vec2(screenwidth * 0.867f, screenheight * 0.91f);
	}

	void SceneManager::drawRect(float alpha_)
	{
		/*This one draws the black background completely fine, but it is without the Alpha variable */
		Shaders->Textured_Shader()->Send_Mat4("model_matrx", rec->transformation.Get());

		glUniform1f(glGetUniformLocation(Shaders->Textured_Shader()->get_hdl(), "alpha"), alpha_);
		rec->draw();
		/*
		Shaders->Alpha_Shader()->use();
		float alpha = 1.f;
		Shaders->Alpha_Shader()->Send_Mat4("model_matrx", rec->transformation.Get());
		glUniform1f(glGetUniformLocation(Shaders->Alpha_Shader()->get_hdl(), "alpha"), alpha);
		rec->draw();
		*/


	}

	void SceneManager::drawBlackOverlay()
	{
		SceneManager::loadRect(0, 0);

		currentAlpha = std::lerp(currentAlpha, targetAlpha, (Get_Delta()));
		SceneManager::drawRect(currentAlpha);
		//std::cout << "Alpha: " << currentAlpha << std::endl;
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
			ingredient.second->timer += ((Get_Delta()));

			/*
					if (ingredient.second->timer > 2.f && ingredient.first == grid_number::soya)
					{
						if (Map::salmon->status == 1)
						{
							ingredient.second->curr_anim = AnimationType::Idle;
							//ingredient.second->alpha -= Window::GetInstance(0, 0)->getDelta();
							ingredient.second->alpha = 0.5f;
						}
					}
					if (Map::wasabi->timer >2.f && ingredient.first == grid_number::wasabi)
					{

						if (Map::salmon->status == 2)
						{
							ingredient.second->curr_anim = AnimationType::Idle;
							//ingredient.second->alpha -= Window::GetInstance(0, 0)->getDelta();
							ingredient.second->alpha = 0.5f;
						}
					}
					if (ingredient.second->timer > 2.f && ingredient.first == grid_number::tea)
					{

						if (Map::salmon->status == 4)
						{
							ingredient.second->curr_anim = AnimationType::Idle;
							//ingredient.second->alpha -= Window::GetInstance(0, 0)->getDelta();
							ingredient.second->alpha = 0.5f;
						}
					}
					*/

			Shaders->Textured_Shader()->Send_Mat4("model_matrx", ingredient.second->transformation.Get());
			glUniform1f(glGetUniformLocation(Shaders->Textured_Shader()->get_hdl(), "alpha"), ingredient.second->alpha);
			if (ingredient.second->isSpriteSheet)
			{
				ingredient.second->draw((Get_Delta()), ingredient.second->curr_anim);
			}
			else
			{
				ingredient.second->draw();
			}

		}

		if (Map::salmon != nullptr)
		{
			if (Map::wasabi != nullptr)
			{
				if (Map::wasabi->timer > 1.f)
				{
					Map::wasabi->curr_anim = AnimationType::Idle;
					//ingredient.second->alpha -= Window::GetInstance(0, 0)->getDelta();
					if (Map::salmon->status == 2 || Map::salmon->status == 3 || Map::salmon->status == 5 || Map::salmon->status == 6 || Map::salmon->status == 7 || Map::salmon->status == 8)
					{
						Map::wasabi->alpha -= ((Get_Delta()));
					}
				}
			}
			if (Map::tea != nullptr)
			{

				if (Map::tea->timer > 1.f)
				{
					Map::tea->curr_anim = AnimationType::Idle;
					//ingredient.second->alpha -= Window::GetInstance(0, 0)->getDelta();
					if (Map::salmon->status == 4 || Map::salmon->status == 5 || Map::salmon->status == 6 || Map::salmon->status == 7 || Map::salmon->status == 8)
					{
						Map::tea->alpha -= ((Get_Delta()));
					}
				}
			}
			if (Map::soya != nullptr)
			{

				if (Map::soya->timer > 1.f)
				{
					Map::soya->curr_anim = AnimationType::Idle;
					//ingredient.second->alpha -= Window::GetInstance(0, 0)->getDelta();
					if (Map::salmon->status == 1 || Map::salmon->status == 3 || Map::salmon->status == 4 || Map::salmon->status == 6 || Map::salmon->status == 7 || Map::salmon->status == 8)
					{
						Map::soya->alpha -= ((Get_Delta()));
					}
				}
			}
		}


	}
	/*
	void SceneManager::drawRice()
	{
		for (auto& ingredient : ricecontainer)
		{
			Shaders->Textured_Shader()->Send_Mat4("model_matrx", ingredient.second->transformation.Get());
			glUniform1f(glGetUniformLocation(Shaders->Textured_Shader()->get_hdl(), "alpha"), alpha);
			ingredient.second->draw();
		}
	}
	*/


	bool SceneManager::activateSoya()
	{
		if (Map::soya->timer < 5.f)
		{
			Map::soya->transformation.Position.x = Map::soya->transformation.Position.x - 30;
			Map::soya->transformation.Position.y = Map::soya->transformation.Position.y - 30;
			Map::soya->curr_anim = AnimationType::Run;
			Map::soya->count++;
			return 1;
		}
		return 0;
	}

	bool SceneManager::activateWasabi()
	{
		if (Map::wasabi->timer < 5.f)
		{
			Map::wasabi->transformation.Position.y = Map::wasabi->transformation.Position.y - 100;
			Map::wasabi->curr_anim = AnimationType::Run;
			Map::wasabi->count++;
			return 1;
		}
		return 0;
	}
	bool SceneManager::activateTea()
	{
		if (Map::tea->timer < 5.f)
		{
			Map::tea->transformation.Position.x = Map::tea->transformation.Position.x - 50;
			Map::tea->transformation.Position.y = Map::tea->transformation.Position.y - 50;
			Map::tea->curr_anim = AnimationType::Run;
			Map::tea->count++;
			return 1;
		}
		return 0;
	}

	void SceneManager::drawInsideSinkHole()
	{
		for (auto& sink : in_sinkhole)
		{
			Shaders->Textured_Shader()->Send_Mat4("model_matrx", sink.second->transformation.Get());
			glUniform1f(glGetUniformLocation(Shaders->Textured_Shader()->get_hdl(), "alpha"), alpha);

			if (sink.second->isSpriteSheet)
			{
				sink.second->draw((Get_Delta()), sink.second->curr_anim);
			}
			else
			{
				sink.second->draw();
			}

		}
	}

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

	void SceneManager::draw_Dialogue()
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
		else if (Window::dialogue_style >= static_cast<int>(Window::dialogue::L7) && Window::dialogue_style <= static_cast<int>(Window::dialogue::L9))
		{
			Shaders->Textured_Shader()->Send_Mat4("model_matrx", fishingvillage_dialogue->transformation.Get());
			fishingvillage_dialogue->draw();
		}


	}

	void SceneManager::draw_Wood_BG()
	{
		Shaders->Textured_Shader()->Send_Mat4("model_matrx", wooden_bg->transformation.Get());
		wooden_bg->draw();
	}

	void SceneManager::loadRect(int x, int y)
	{
		rec->transformation.Position = glm::vec2(x, y);
		rec->transformation.Scale = glm::vec2(1920, 1200);
	}

	void SceneManager::FadeIn()
	{
		targetAlpha = 1.0f;
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
		/*
		if (ricecontainer.size() != 0)
		{
			for (auto it : ricecontainer)
			{
				delete it.second;
			}
		}
		ricecontainer.clear();
		*/
		ingredientcontainer.clear();
	}

	void SceneManager::destroyInsideSinkHole()
	{
		if (in_sinkhole.size() != 0)
		{
			for (auto it : in_sinkhole)
			{
				delete it.second;
			}
		}

		in_sinkhole.clear();
	}

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

	void SceneManager::destroy_Dialogue()
	{
		delete riceplain_dialogue;
		delete gunkan_dialogue;
		delete fishingvillage_dialogue;
	}

	void SceneManager::destroy_Wood_BG()
	{
		delete wooden_bg;
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