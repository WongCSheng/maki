#include "../Headers/SceneManager.h"
#include "../Engine//Serialiser/JSONSerializer.h"
#include "../Engine/Shaders/ShaderLibrary.h"
#include "../Headers/Main.h"
#include "../Engine/TileMap/Map.h"
#include <Engine/Font/Font.h>
#include "../Engine/GameSave/GameSave.h"
#include "Window.h"
//#include "."
double credits_y = 0;

namespace Core
{
	float alpha = 1.0f;
	std::vector<std::pair<wall_type, Sprite*>> tilecontainer;
	std::vector<std::pair<grid_number, Sprite*>> ingredientcontainer;
	float timer = 0.f;

	/* default black color */
	glm::vec3 color_up{0.f, 0.f, 0.f}; 
	glm::vec3 color_down{ 0.f, 0.f, 0.f };
	glm::vec3 color_left{ 0.f, 0.f, 0.f };
	glm::vec3 color_right{ 0.f, 0.f, 0.f };
	glm::vec3 color_r{ 0.f, 0.f, 0.f };

	//color str default  //red
	glm::vec3 color_str{ 1.f, 0.f, 0.f };

	SceneManager::SceneManager()
	{
		up_key = false;
		down_key = false;
		left_key = false;
		right_key = false;
		r_key = false;
		/*tile = nullptr;
		ingredient1 = nullptr;
		ingredient2 = nullptr;
		trap = nullptr;
		goal1 = nullptr;
		goal2 = nullptr;
		cover1 = nullptr;*/
		howtoplay_overlay1 = nullptr;
		howtoplay_overlay2 = nullptr;
		howtoplay_overlay3 = nullptr;
		howtoplay_overlay4 = nullptr;
		howtoplay_overlay5 = nullptr;
		howtoplay_overlay6 = nullptr;
		frame1 = nullptr;
		frame2 = nullptr;
		frame3 = nullptr;
		frame4 = nullptr;
		frame5 = nullptr;
		frame6 = nullptr;
		frame7 = nullptr;
		frame8 = nullptr;
		win_overlay = nullptr;
		player_stuck = nullptr;
		rows = cols = tileHeight = tileWidth = 0;
		rec = nullptr;
		spacepressed = 0;
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

	void SceneManager::RegisterGameObjects(std::unordered_map<std::string, Object::GameObject*> ObjectContainer)
	{

	}

	void SceneManager::restartLevel()
	{
		particle->transformation.Position = glm::vec2(Player::playerpos.x, Player::playerpos.y);
		if (tilecontainer.size() > 0 && ingredientcontainer.size() > 0 && in_sinkhole.size()>0 && topcontainer.size()>0)
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
		Window::player->current_anim = AnimationType::Idle;
		Window::questProgress = 0;
		amt_of_win_conditions = 0;
		Window::player->resetCount = 0;
		//missing: restart sinkhole, restart sushi plate pods
		Window::isPlayerinSinkhole = false;
		//reset ingredient pos
		/*for (auto& ingredient : ingredientcontainer)
		{
			ingredient.second->restart();
			ingredient.second->count = 0;
		}*/
	}
	//R key for restart
	// update by thea: i've written a new restart function
	//					that just restarts the position, rather than
	//					this one that deletes an old player and "new"s
	//					to create a new one (this is very resource intensive
	//					and prone to memory leaks)

	void SceneManager::loadTopAnimation(int x, int y, const std::pair<animated, Sprite*>& tile)
	{

		tile.second->transformation.Position = glm::vec2(x, y);
		tile.second->transformation.Scale = glm::vec2(getTileWidth() * 1.01f, getTileHeight() * 1.01f);

		topcontainer.push_back(tile);


		std::cout << std::endl;
		//std::cout << "****************** added a tile! tilecontainer size: " << tilecontainer.size() << std::endl;
	}

	void SceneManager::loadTile(int x, int y, const std::pair<wall_type, Sprite*>& tile)
	{

		tile.second->transformation.Position = glm::vec2(x, y);
		tile.second->transformation.Scale = glm::vec2(getTileWidth()*1.01f, getTileHeight() * 1.01f);

		tilecontainer.push_back(tile);


		std::cout << std::endl;
		//std::cout << "****************** added a tile! tilecontainer size: " << tilecontainer.size() << std::endl;
	}

	void SceneManager::loadIngr(int x, int y, int posX, int posY, const std::pair<grid_number, Sprite*>& ingredient)
	{
		if (counter.find(ingredient.first) == counter.end())
		{
			counter[ingredient.first] = 1;
		}
		else
		{
			counter[ingredient.first]++;
		}

		ingredient.second->transformation.Position = glm::vec2(x, y);
		ingredient.second->transformation.Scale = glm::vec2(getTileWidth(), getTileHeight());

		ingredient.second->transformation.grid_pos = { posX, posY };

		//set all counters to 0 first, because soya might be activated twice
		ingredient.second->count = 0;
		ingredient.second->alpha = 1.f;

		Basket input;

		input.IC = counter[ingredient.first];
		input.nametag = ingredient.first;
		input.init_value = ingredient.second->transformation;
		input.spr = ingredient.second;
		input.init_Grid_Pos = { posX, posY };

		if (input.nametag == grid_number::sinkhole)
		{
			in_sinkhole.push_back(input);
		}
		else
		{
			ingredientcontainer.push_back(input);
		}
		std::cout << std::endl;
		//std::cout << "****************** added an ingredient! ingredientcontainer size: " << ingredientcontainer.size() << std::endl;
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

	/* adjust screensize */
	/*
	void SceneManager::loadHowToOverlay(int x, int y)
	{
		//!!! Code has been modified. Refer to drawhowtooverlay function for rendering of how to play pages
		
		/*int screenwidth = 0, screenheight = 0;
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
	*/
	void SceneManager::loadSettings()
	{
		int screenwidth = 0, screenheight = 0;
		glfwGetWindowSize(Window::window_ptr, &screenwidth, &screenheight);
		//settings
		settings_page->transformation.Position = glm::vec2(screenwidth * 0.25, screenheight * 0.25);
		settings_page->transformation.Scale = glm::vec2(screenwidth * 0.47, screenheight * 0.5);

		////credits
		//credits_page->transformation.Position = glm::vec2(0, 0);
		//credits_page->transformation.Scale = glm::vec2(screenwidth, screenheight);
	}
	void SceneManager::loadWinOverlay(int x, int y)
	{
		Window::player->resetCount = 0;
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
		else if (Window::dialogue_style == static_cast<int>(Window::dialogue::MAKI_CITY))
		{
			makicity_dialogue->transformation.Position = glm::vec2(screenwidth * 0.15f, screenheight * 0.7f);
			makicity_dialogue->transformation.Scale = glm::vec2(screenwidth * 0.7f, screenheight * 0.3f);
		}
	}

	void SceneManager::load_Wood_BG()
	{
		int screenwidth = 0, screenheight = 0;
		glfwGetWindowSize(Window::window_ptr, &screenwidth, &screenheight);
		wooden_bg->transformation.Position = glm::vec2(screenwidth * 0.09f, screenheight * 0.08f);
		wooden_bg->transformation.Scale = glm::vec2(screenwidth * 0.867f, screenheight * 0.91f);
	}

	void SceneManager::load_City_BG()
	{
		int screenwidth = 0, screenheight = 0;
		glfwGetWindowSize(Window::window_ptr, &screenwidth, &screenheight);
		city_bg->transformation.Position = glm::vec2(0,0);
		city_bg->transformation.Scale = glm::vec2(screenwidth /** 0.872f*/, screenheight/* * 0.9f*/);
	}

	void SceneManager::load_Bami_End_Room()
	{
		int screenwidth = 0, screenheight = 0;
		glfwGetWindowSize(Window::window_ptr, &screenwidth, &screenheight);
		Ending_Cutscene->transformation.Position = glm::vec2(0, 0);
		Ending_Cutscene->transformation.Scale = glm::vec2(screenwidth, screenheight);
	}

	void SceneManager::load_Are_You_Sure()
	{
		int screenwidth = 0, screenheight = 0;
		glfwGetWindowSize(Window::window_ptr, &screenwidth, &screenheight);
		are_you_sure->transformation.Position = glm::vec2(0, 0);
		are_you_sure->transformation.Scale = glm::vec2(screenwidth, screenheight);
		
	}

	void SceneManager::load_Particle()
	{
		particle->transformation.Scale = glm::vec2(SceneManager::getTileWidth(), SceneManager::getTileHeight());
		switch (particleDisplay)
		{
		case particlePos::isLeftofPlayer:
			particle->transformation.Position = glm::vec2(Player::playerpos.x - SceneManager::getTileWidth(), Player::playerpos.y);
			break;

		case particlePos::isRightofPlayer:
			particle->transformation.Position = glm::vec2(Player::playerpos.x + SceneManager::getTileWidth(), Player::playerpos.y);
			break;

		case particlePos::isAbovePlayer:
			particle->transformation.Position = glm::vec2(Player::playerpos.x, Player::playerpos.y - SceneManager::getTileHeight());
			break;

		case particlePos::isBelowPlayer:
			particle->transformation.Position = glm::vec2(Player::playerpos.x, Player::playerpos.y + SceneManager::getTileHeight());
			break;

		default:
			break;
		}
		
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

	void SceneManager::drawFader(float alpha_)
	{
		/*This one draws the black background completely fine, but it is without the Alpha variable */
		Shaders->Textured_Shader()->Send_Mat4("model_matrx", fader->transformation.Get());

		glUniform1f(glGetUniformLocation(Shaders->Textured_Shader()->get_hdl(), "alpha"), alpha_);
		fader->draw();
	}
	
	void SceneManager::drawBlackOverlay()
	{

		SceneManager::loadRect(0, 0);

		currentAlpha = std::lerp(currentAlpha, targetAlpha, Get_Delta() * 1.2f);
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
			ingredient.spr->timer += ((Get_Delta()));
			if (ingredient.spr->animeMe == true)
			{
				if (ingredient.nametag == grid_number::boxcover)
				{
					if (ingredient.spr->timer < 1.f)
					{
					ingredient.spr->transformation.Position.y = std::lerp(currpos, targetpos, ingredient.spr->timer);
					}
				}
			}
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



			Shaders->Textured_Shader()->Send_Mat4("model_matrx", ingredient.spr->transformation.Get());
			glUniform1f(glGetUniformLocation(Shaders->Textured_Shader()->get_hdl(), "alpha"), ingredient.spr->alpha);
			if (ingredient.spr->isSpriteSheet)
			{
				ingredient.spr->draw((Get_Delta()), ingredient.spr->curr_anim);
			}
			else
			{
				ingredient.spr->draw();
			}

		}

			for (auto& ingredient : ingredientcontainer)
			{
				/*check which sprite has set animation to true*/

					/*check wasabi, soya and tea*/
				if (ingredient.spr->animeMe == true)
				{
					if (ingredient.nametag == grid_number::wasabi)
					{
						if (ingredient.spr->timer > 1.f)
						{
							ingredient.spr->curr_anim = AnimationType::Idle;
							ingredient.spr->alpha -= ((Get_Delta()));
						}
					}
					if (ingredient.nametag == grid_number::tea)
					{
						if (ingredient.spr->timer > 1.f)
						{
							ingredient.spr->curr_anim = AnimationType::Idle;
							ingredient.spr->alpha -= ((Get_Delta()));
						}
					}
					if (ingredient.nametag == grid_number::soya)
					{
						if (ingredient.spr->timer > 1.f)
						{
							ingredient.spr->curr_anim = AnimationType::Idle;
							ingredient.spr->alpha -= ((Get_Delta()));
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

	bool SceneManager::activateSoya(Sprite* soya)
	{
		AudioManager.PlaySFX("Pouring.ogg");
		if (soya->timer < 5.f)
		{
			soya->transformation.Position.x = soya->transformation.Position.x - 30;
			soya->transformation.Position.y = soya->transformation.Position.y - 30;
			soya->curr_anim = AnimationType::Run;
			soya->count++;
			return 1;
		}
		return 0;
	}

	bool SceneManager::activateWasabi(Sprite* wasabi)
	{
		AudioManager.PlaySFX("Squeezing.ogg");
		if (wasabi->timer < 5.f)
		{
			wasabi->transformation.Position.y = wasabi->transformation.Position.y - 100;
			wasabi->curr_anim = AnimationType::Run;
			wasabi->count++;
			return 1;
		}
		return 0;
	}
	void SceneManager::drawTop()
	{
		for (auto& top : topcontainer)
		{
			Shaders->Textured_Shader()->Send_Mat4("model_matrx", top.second->transformation.Get());
			glUniform1f(glGetUniformLocation(Shaders->Textured_Shader()->get_hdl(), "alpha"), alpha);
			top.second->draw(Get_Delta(), AnimationType::Idle);
		}
	}
	bool SceneManager::activateTea(Sprite* tea)
	{
		AudioManager.PlaySFX("Pouring.ogg");
		if (tea->timer < 5.f)
		{
			tea->transformation.Position.x = tea->transformation.Position.x - 50;
			tea->transformation.Position.y = tea->transformation.Position.y - 50;
			tea->curr_anim = AnimationType::Run;
			tea->count++;
			return 1;
		}
		return 0;
	}

	void SceneManager::drawInsideSinkHole()
	{
		for (auto& sink : in_sinkhole)
		{
			if (sink.nametag != grid_number::sinkhole)
			{
				Shaders->Textured_Shader()->Send_Mat4("model_matrx", sink.spr->transformation.Get());
				glUniform1f(glGetUniformLocation(Shaders->Textured_Shader()->get_hdl(), "alpha"), alpha);

				if (sink.spr->isSpriteSheet)
				{
					sink.spr->draw(Get_Delta(), sink.spr->curr_anim);
				}
				else
				{
					sink.spr->draw();
				}
			}
		}
	}
	
	void SceneManager::drawSinkHole()
	{
		for (auto& sink : in_sinkhole)
		{
			if (sink.nametag == grid_number::sinkhole)
			{
				Shaders->Textured_Shader()->Send_Mat4("model_matrx", sink.spr->transformation.Get());
				glUniform1f(glGetUniformLocation(Shaders->Textured_Shader()->get_hdl(), "alpha"), alpha);

				sink.spr->draw();
			}
		}
	}

	void SceneManager::drawPlayer_Stuck()
	{
		Shaders->Textured_Shader()->Send_Mat4("model_matrx", player_stuck->transformation.Get());
		glUniform1f(glGetUniformLocation(Shaders->Textured_Shader()->get_hdl(), "alpha"), alpha);
		player_stuck->draw();
	}

	void SceneManager::drawHowToOverlay(int page)
	{
			/* resize the window before the overlay is drawn. */
			int screenwidth = 0, screenheight = 0;
			glfwGetWindowSize(Window::window_ptr, &screenwidth, &screenheight);
			// object pointer to retreive from object factory container
			Core::Object::GameObject* obj{};
			// retreive how to play overlay from object container using page
			switch (page)
			{
			case 0:
				obj = Core::MainSystem::objfactory->ObjectContainer.at("HowToPlay_overlay_1");
				break;
			case 1:
				obj = Core::MainSystem::objfactory->ObjectContainer.at("HowToPlay_overlay_2");
				break;
			case 2:
				obj = Core::MainSystem::objfactory->ObjectContainer.at("HowToPlay_overlay_3");
				break;
			case 3:
				obj = Core::MainSystem::objfactory->ObjectContainer.at("HowToPlay_overlay_4");
				break;
			case 4:
				obj = Core::MainSystem::objfactory->ObjectContainer.at("HowToPlay_overlay_5");
				break;
			case 5:
				obj = Core::MainSystem::objfactory->ObjectContainer.at("HowToPlay_overlay_6");
				break;
			}

			Transform* transcomp =obj->GetObjectProperties()->GetComponent<Transform>(ComponentID::Transform);
			Sprite* spritecomp =obj->GetObjectProperties()->GetComponent<Sprite>(ComponentID::Renderer);

			spritecomp->transformation.Position = transcomp->Position;
			spritecomp->transformation.Scale = glm::vec2(screenwidth, screenheight); 

			Shaders->Textured_Shader()->Send_Mat4("model_matrx", spritecomp->transformation.Get());
			Shaders->Textured_Shader()->Send_Alpha("alpha", 1.f);
			if (Window::isHowToPlay == true)
			spritecomp->draw();
	}
	void SceneManager::drawSettings()
	{
		
		//if settings only 
		if (Window::isCredits == false)
		{
			Shaders->Textured_Shader()->Send_Mat4("model_matrx", settings_page->transformation.Get());
			Shaders->Textured_Shader()->Send_Alpha("alpha", 1.f);
			settings_page->draw();
			credits_y = 0;

		}
		else //isCredits == true
		{
			int screenwidth = 0, screenheight = 0;
			glfwGetWindowSize(Window::window_ptr, &screenwidth, &screenheight);
			
			//credits
			credits_page->transformation.Scale = glm::vec2(screenwidth, screenheight*3);
			if (credits_y > -screenheight * 2)
			{
				credits_y -= Get_Delta()*70;
				
			}
			
			credits_page->transformation.Position = glm::vec2(0, credits_y);
			//if credits only
			Shaders->Textured_Shader()->Send_Mat4("model_matrx", credits_page->transformation.Get());
			credits_page->draw();
			


		}
	}
	void SceneManager::drawWinOverlay()
	{
		
		Window::player->current_anim = AnimationType::Run;
		Shaders->Textured_Shader()->use();
		Shaders->Textured_Shader()->Send_Mat4("model_matrx", win_overlay->transformation.Get());
		Shaders->Textured_Shader()->Send_Alpha("alpha", 1.f);
		win_overlay->draw();
	}


	void SceneManager::drawTut1( )
	{
		const std::string up = "Up";
		const std::string down = "Down";
		const std::string left = "Left";
		const std::string right = "Right";
		const std::string str = "All ingredients are packed";

		int screenwidth = 0, screenheight = 0;
		glfwGetWindowSize(Window::window_ptr, &screenwidth, &screenheight);

		/*	bool state to toggle the key */
		if(!up_key)
		{	//up_key is true
			//default up_key set to red
			color_up = { 1.f, 0.f, 0.f };

		}
		else
		{
			color_up = { 0.f, 1.f, 0.f };
		}

		if (!down_key) 
		{
			//default up_key set to red
			color_down = { 1.f, 0.f, 0.f };

		}
		else
			color_down = { 0.f, 1.f, 0.f };

		if (!left_key) 
		{
			//default up_key set to red
			color_left = { 1.f, 0.f, 0.f };

		}
		else
			color_left = { 0.f, 1.f, 0.f };

		if (!right_key) 
		{
			//default up_key set to red
			color_right = { 1.f, 0.f, 0.f };

		}
		else
			color_right = { 0.f, 1.f, 0.f };

		
		if (!Map::isWin())
		{
			//when no win, set the string to red color
			color_str = { 1.f, 0.f, 0.f }; //red
		} 
		else if(Map::isWin())
		{
			color_str = { 0.f, 1.f, 0.f }; //green
			//when win condition met, green color
		};
		
		Shaders->Font_Shader()->use();
		Font::RenderText(*Shaders, up, (float)((screenwidth/2)-930), (float)(screenheight-175), .55f, color_up, 1.f);
		Font::RenderText(*Shaders, down, (float)((screenwidth / 2) - 865), (float)(screenheight - 175), .55f, color_down, 1.f);
		Font::RenderText(*Shaders, left, (float)((screenwidth / 2) - 770), (float)(screenheight - 175), .55f, color_left, 1.f);
		Font::RenderText(*Shaders, right, (float)((screenwidth / 2) - 690), (float)(screenheight - 175), .55f, color_right, 1.f);
		Font::RenderText(*Shaders, str, (float)((screenwidth / 2) - 930), (float)(screenheight - 220), .55f, color_str, 1.f);
		Shaders->Textured_Shader()->use();
		
	}

	void SceneManager::drawTut2()
	{
		//if (!r_key)
		//{
		//	//default up_key set to red
		//	color_r = { 1.f, 0.f, 0.f };
		//}
		if (!r_key)
		{
			//default up_key set to red
			color_r = { 1.f, 0.f, 0.f };

		}
		else
		{
			color_r = { 0.f, 1.f, 0.f };
			GameSave::LevelStatusContainer[1].isQuestClear = 1;
		}

		//if(Window::keystate_R)
		//{
		//	color_r= { 0.f, 1.f, 0.f }; //green
		//	r_key = true; //keep color to green after pressed r
		//	
		//}
		const std::string str = "Press   'R'   to  restart";

		int screenwidth, screenheight;
		glfwGetWindowSize(Window::window_ptr, &screenwidth, &screenheight);

		Shaders->Font_Shader()->use();
		Font::RenderText(*Shaders, str, (float)((screenwidth / 2) - 920), (float)(screenheight - 190), .55f, color_r, 1.f);
		Shaders->Textured_Shader()->use();
	}

	/* resets color back to red*/
	void SceneManager::resetColor()
	{
		color_up = { 1.f, 0.f, 0.f };
		color_down = { 1.f, 0.f, 0.f };
		color_left = { 1.f, 0.f, 0.f };
		color_right = { 1.f, 0.f, 0.f };
		color_r = { 1.f, 0.f, 0.f };
	}
	

	void SceneManager::drawEncourage()
	{
		/*random int between 0 to 10*/
		const char* encourgementwords[5] = { "Stay strong", "Keep pushing",
		"Almost there!", "Don't give up!", "Yes you can!"};
		int screenwidth = 0, screenheight = 0;
		glfwGetWindowSize(Window::window_ptr, &screenwidth, &screenheight);
		timer += Get_Delta();
		if (timer > 1.f)
		{
			FcurrentAlpha = std::lerp(FcurrentAlpha, FtargetAlpha, Get_Delta());
		}
		Shaders->Font_Shader()->use();
		Font::RenderText(*Shaders, encourgementwords[Player::resetCount], Player::playerpos.x - 30, screenheight - Player::playerpos.y, .55f, glm::vec3(0.f, 0.f, 0.f), FcurrentAlpha);
	}

	void SceneManager::drawIngrStuck()
	{
		int screenwidth = 0, screenheight = 0;
		glfwGetWindowSize(Window::window_ptr, &screenwidth, &screenheight);
		timer += Get_Delta();
		if (timer > 1.f)
		{
			ScurrentAlpha = std::lerp(ScurrentAlpha, StargetAlpha, Get_Delta());
		}
		Shaders->Font_Shader()->use();
		Font::RenderText(*Shaders, "ingredient is stuck", Player::playerpos.x - 30, screenheight - Player::playerpos.y, .55f, glm::vec3(0.f, 0.f, 0.f), ScurrentAlpha);
	}

	void SceneManager::draw_Are_You_Sure()
	{
		Shaders->Textured_Shader()->Send_Mat4("model_matrx", are_you_sure->transformation.Get());
		Shaders->Textured_Shader()->Send_Alpha("alpha", 1.f);
		are_you_sure->draw();
	}

	void SceneManager::draw_Particle()
	{
		Shaders->Textured_Shader()->Send_Mat4("model_matrx", particle->transformation.Get());
		glUniform1f(glGetUniformLocation(Shaders->Textured_Shader()->get_hdl(), "alpha"), alpha);
		//particle->draw();
		SceneManager::particle->draw((Get_Delta()), SceneManager::particle->curr_anim);
	}

	void SceneManager::drawGiveUp()
	{
		int screenwidth = 0, screenheight = 0;
		glfwGetWindowSize(Window::window_ptr, &screenwidth, &screenheight);
		timer = 0;
		timer += Get_Delta();

		if (timer > 1.f)
		{
			FcurrentAlpha = std::lerp(FcurrentAlpha, FtargetAlpha, Get_Delta());
		}
		Shaders->Font_Shader()->use();
		Font::RenderText(*Shaders, "Getgud -Bami 2023", Player::playerpos.x - 30, screenheight - Player::playerpos.y, .55f, glm::vec3(0.f, 0.f, 0.f), FcurrentAlpha);

	}

	void SceneManager::drawCutscene(int CutscenePage)
	{
		{
				/* resize the window before the cutscene is drawn. */
			int screenwidth = 0, screenheight = 0;
			glfwGetWindowSize(Window::window_ptr, &screenwidth, &screenheight);
			// object pointer to retreive from object factory container
			Core::Object::GameObject* obj{};

			// retreive cutscenes from object container using page
			switch (CutscenePage)
			{
			case 0:
				obj = Core::MainSystem::objfactory->ObjectContainer.at("Cutscene_frame1");
				break;
			case 1:
				obj = Core::MainSystem::objfactory->ObjectContainer.at("Cutscene_frame2");
				break;
			case 2:
				obj = Core::MainSystem::objfactory->ObjectContainer.at("Cutscene_frame3");
				break;
			case 3:
				obj = Core::MainSystem::objfactory->ObjectContainer.at("Cutscene_frame4");
				break;
			case 4:
				obj = Core::MainSystem::objfactory->ObjectContainer.at("Cutscene_frame5");
				break;
			case 5:
				obj = Core::MainSystem::objfactory->ObjectContainer.at("Cutscene_frame6");
				break;
			case 6:
				obj = Core::MainSystem::objfactory->ObjectContainer.at("Cutscene_frame7");
				break;
			case 7:
				obj = Core::MainSystem::objfactory->ObjectContainer.at("Cutscene_frame8");
				break;
			}

			Transform* transcomp = obj->GetObjectProperties()->GetComponent<Transform>(ComponentID::Transform);
			Sprite* spritecomp = obj->GetObjectProperties()->GetComponent<Sprite>(ComponentID::Renderer);

			spritecomp->transformation.Position = transcomp->Position;
			spritecomp->transformation.Scale = glm::vec2(screenwidth, screenheight);

			Shaders->Textured_Shader()->Send_Mat4("model_matrx", spritecomp->transformation.Get());
			glUniform1f(glGetUniformLocation(Shaders->Textured_Shader()->get_hdl(), "alpha"), alpha);
			spritecomp->draw();
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
		Shaders->Textured_Shader()->use();
		Shaders->Textured_Shader()->Send_Alpha("alpha", 1.f);
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
		else if (Window::dialogue_style == static_cast<int>(Window::dialogue::MAKI_CITY))
		{
			Shaders->Textured_Shader()->Send_Mat4("model_matrx", makicity_dialogue->transformation.Get());
			makicity_dialogue->draw();
		}
		
	}

	void SceneManager::draw_Wood_BG()
	{
		Shaders->Textured_Shader()->Send_Alpha("alpha", 1.f);
		Shaders->Textured_Shader()->Send_Mat4("model_matrx", wooden_bg->transformation.Get());
		wooden_bg->draw();
	}

	void SceneManager::draw_City_BG()
	{
		Shaders->Textured_Shader()->Send_Alpha("alpha", 1.f);
		Shaders->Textured_Shader()->Send_Mat4("model_matrx", city_bg->transformation.Get());
		city_bg->draw();
	}

	void SceneManager::draw_Bami_End_Room()
	{
		Shaders->Textured_Shader()->Send_Alpha("alpha", 1.f);
		Shaders->Textured_Shader()->Send_Mat4("model_matrx", Ending_Cutscene->transformation.Get());
		Ending_Cutscene->draw((Get_Delta()), SceneManager::Ending_Cutscene->curr_anim);
		
	}

	void SceneManager::loadRect(int x, int y)
	{
		rec->transformation.Position = glm::vec2(x, y);
		rec->transformation.Scale = glm::vec2(1920, 1200);
	}

	void SceneManager::loadFader(int x, int y)
	{
		fader->transformation.Position = glm::vec2(x, y);
		fader->transformation.Scale = glm::vec2(1920, 1200);
	}

	void SceneManager::FadeIn()
	{
		targetAlpha = 1.0f;
		FtargetAlpha = 1.0f;
		StargetAlpha = 1.0f;
	}

	void SceneManager::FadeOut()
	{
		targetAlpha = 0.0f;
		FtargetAlpha = 0.0f;
		StargetAlpha = 0.0f;
	}

	void SceneManager::set_target_pos(Sprite* boxcover)
	{
		targetpos = boxcover->target_pos;
	}

	void SceneManager::set_curr_pos(Sprite* boxcover)
	{
		currpos = boxcover->curr_pos;
	}

	/*destroy functions*/
	void SceneManager::destroyTile()
	{
		if (tilecontainer.size() > 0)
		{
			for (auto &it : tilecontainer)
			{
				delete it.second;
			}
		}

		tilecontainer.clear();
	}

	void SceneManager::destroyIngr()
	{
		if (ingredientcontainer.size() > 0)
		{
			for (auto &it : ingredientcontainer)
			{
				delete it.spr;
			}
		}

		ingredientcontainer.clear();
	}
	
	void SceneManager::destroyInsideSinkHole()
	{
		if (in_sinkhole.size() > 0)
		{
			for (auto &it : in_sinkhole)
			{
				delete it.spr;
			}
		}

		in_sinkhole.clear();
	}

	void SceneManager::destroyTop()
	{
		if (topcontainer.size() > 0)
		{
			for (auto& it : topcontainer)
			{
				delete it.second;
			}
		}

		topcontainer.clear();
	}

	void SceneManager::destroyHowToOverlay()
	{
		delete howtoplay_overlay1;
		delete howtoplay_overlay2;
		delete howtoplay_overlay3;
		delete howtoplay_overlay4;
		delete howtoplay_overlay5;
		delete howtoplay_overlay6;
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

	void SceneManager::destroy_fading()
	{
		delete fader;
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
		//delete level_select;
	}

	void SceneManager::destroy_Dialogue()
	{
		delete riceplain_dialogue;
		delete gunkan_dialogue;
		delete fishingvillage_dialogue;
		delete makicity_dialogue;
	}

	void SceneManager::destroy_Wood_BG()
	{
		delete wooden_bg;
	}

	void SceneManager::destroy_City_BG()
	{
		delete city_bg;
	}

	void SceneManager::destroy_Bami_End_Room()
	{
		delete Ending_Cutscene;
	}

	void SceneManager::destroy_Are_You_Sure()
	{
		delete are_you_sure;
	}

	void SceneManager::destroy_Particle()
	{
		delete particle;
	}

	void SceneManager::setTileDimension(unsigned int Width, unsigned int Height)
	{
		tileWidth = Width;
		tileHeight = Height;
	}
	
	void SceneManager::destroyPlayer_Stuck()
	{
		delete player_stuck;
	}

}