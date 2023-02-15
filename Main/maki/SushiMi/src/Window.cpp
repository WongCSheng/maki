/*
File: Window.cpp
@author		louishetong.wang@digipen.edu
co-Author:  thea.sea@digipen.edu
co-Author:  Aurelia (fei.x@digipen.edu)
co-Author:  w.chongsheng@digipen.edu

Description: 
*/

/*                                                                   includes
----------------------------------------------------------------------------- */
#include "Window.h"
#include "../Engine/Input/Input.h"
#include "../../imgui/imgui.h"
#include "../Engine/Serialiser/JSONSerializer.h"
#include "../Editors/imfilebrowser.h"
#include "../Headers/SceneManager.h"
#include "../Game Object/Player.h"
#include "../Engine/Components/Texture/Sprite.h"
#include "../Engine/Shaders/ShaderLibrary.h"
#include "../Engine/Camera/Camera2D.h"
#include "../Headers/SceneManager.h"
#include "../Engine/Audio/AudioEngine.h"
#include "../Engine/TileMap/Map.h"
#include "../Engine/Core/Core.h"
#include "../Engine/Serialiser/JSONSerializer.h"
#include "Engine/Font/Font.h"

namespace Core
{
	static Core::MainSystem* CoreSystem;

	/*                                                             game states
	----------------------------------------------------------------------------- */
	enum class GameState {
		LEVEL1,
		MENU

	};


	/*                                                             input key states
	----------------------------------------------------------------------------- */
	static bool keystate_left = false;
	static bool keystate_right = false;
	static bool keystate_up = false;
	static bool keystate_down = false;
	static bool keystate_R = false;
	static bool keystate_M = false;
	static bool keystate_tab = false;
	static bool keystate_space = false;
	static bool keystate_1 = false;
	static bool keystate_2 = false;
	static bool keystate_T = false;
	static bool keystate_escape = false;
	static bool place_obj = false;

	static bool keystate_W = false;
	static bool keystate_A = false;
	static bool keystate_S = false;
	static bool keystate_D = false;

	static bool mouseLeft = false;
	Player* player;

	void mouseCallBack(GLFWwindow* window_ptr, int button, int action, int mod)
	{
		switch (button)
		{
		case GLFW_MOUSE_BUTTON_LEFT:
			mouseLeft = (button == GLFW_MOUSE_BUTTON_LEFT) ? true : false;
				break;
		}

		switch (action)
		{ 
			case GLFW_PRESS:
				mouseLeft = (action == GLFW_PRESS) ? true : false;
				break;
			
			case GLFW_RELEASE:
				mouseLeft = false;
				break;
		}
	}


	//SceneManager* scnmanager = new SceneManager(); //this is dangerous!! write it in a function so that the new is deleted!!

	/*					key  callback function  , helper function for controlling input
		----------------------------------------------------------------------------- */
	void keyCallBack(GLFWwindow* window_ptr, int key, int scancode, int action, int mod)
	{
		if (GLFW_REPEAT == action)
		{
			keystate_left = (key == GLFW_KEY_LEFT) ? true : false;
			keystate_tab = (key == GLFW_KEY_TAB) ? true : false;
			keystate_right = (key == GLFW_KEY_RIGHT) ? true : false;
			keystate_up = (key == GLFW_KEY_UP) ? true : false;
			keystate_down = (key == GLFW_KEY_DOWN) ? true : false;
			keystate_R = (key == GLFW_KEY_R) ? true : false;
			keystate_M = (key == GLFW_KEY_M) ? true : false;
			keystate_escape = (key == GLFW_KEY_ESCAPE) ? true : false;

			
		}
		else if (GLFW_RELEASE == action)
		{
			keystate_left = false;
			keystate_right = false;
			keystate_up = false;
			keystate_down = false;
			keystate_R = false;
			keystate_M = false;
			keystate_escape = false;
			keystate_tab = false;
		}
		else if (GLFW_PRESS == action)
		{
			keystate_M = (key == GLFW_KEY_M) ? true : false;
			keystate_left = (key == GLFW_KEY_LEFT) ? true : false;
			keystate_right = (key == GLFW_KEY_RIGHT) ? true : false;
			keystate_up = (key == GLFW_KEY_UP) ? true : false;;
			keystate_down = (key == GLFW_KEY_DOWN) ? true : false;
			keystate_R = (key == GLFW_KEY_R) ? true : false;
			keystate_M = (key == GLFW_KEY_M) ? true : false;
			keystate_T = (key == GLFW_KEY_T) ? true : false;
			keystate_tab = (key == GLFW_KEY_TAB) ? true : false;
			keystate_escape = (key == GLFW_KEY_ESCAPE) ? true : false;
			keystate_space  = (key == GLFW_KEY_SPACE) ? true : false;


			keystate_1 = (key == GLFW_KEY_1) ? true : false;
			keystate_2 = (key == GLFW_KEY_2) ? true : false;

			keystate_W = (key == GLFW_KEY_W) ? true : false;
			keystate_A = (key == GLFW_KEY_A) ? true : false;
			keystate_S = (key == GLFW_KEY_S) ? true : false;
			keystate_D = (key == GLFW_KEY_D) ? true : false;
			
		}
	}

	Window::Window(int width, int height)
		:m_width(width),
		m_height(height)

	{
		starttime = endtime = delta = 0;

		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_MAXIMIZED, true);

		window_ptr = glfwCreateWindow(width, height, "SushiMi", NULL, NULL);
		if (window_ptr == nullptr)
		{
			std::cout << "erorr initilize glfw" << std::endl;
			return;
		}

		glfwMakeContextCurrent(window_ptr);
		std::cout << "GLEW Error: " << glewGetErrorString(glewInit()) << std::endl;  //it says "No error"

		//initialize key&mouse callback functions
		glfwSetKeyCallback(window_ptr, keyCallBack);
		glfwSetMouseButtonCallback(window_ptr, mouseCallBack);
		/*if (glewInit())
		{
			std::cout << "erorr initilize glew" << std::endl;
			return;
		}*/
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


		Core::LevelLoadPath = "../Data/generated.json"; //initialise Bami position

		starttime = 0;
		endtime = 0;
		delta = 0;

		Shaders = std::make_unique<ShaderLibrary>();
		camera = std::make_unique<Camera>(0, 0);
		
		timetodeletegrid = false;
#ifdef EDITOR
		Editor::LevelEditor::imguiloadedmap = "../TileMap/level1.txt";

#endif


		player = Core::Deserialize(*Core::LevelLoadPathPtr);
#ifndef EDITOR


		SceneManager::howtoplay_overlay1 = new Sprite("../textures/How To Play/HowToPlayBox_1.png");
		SceneManager::howtoplay_overlay2 = new Sprite("../textures/How To Play/HowToPlayBox_2.png");
		SceneManager::howtoplay_overlay3 = new Sprite("../textures/How To Play/HowToPlayBox_3.png");
		SceneManager::howtoplay_overlay4 = new Sprite("../textures/How To Play/HowToPlayBox_4.png");

		SceneManager::frame1 = new Sprite("../Textures/Cutscene/frame1.jpg");
		SceneManager::frame2 = new Sprite("../Textures/Cutscene/frame2.jpg");
		SceneManager::frame3 = new Sprite("../Textures/Cutscene/frame3.jpg");
		SceneManager::frame4 = new Sprite("../Textures/Cutscene/frame4.jpg");
		SceneManager::frame5 = new Sprite("../Textures/Cutscene/frame5.jpg");
		SceneManager::frame6 = new Sprite("../Textures/Cutscene/frame6.jpg");
		SceneManager::frame7 = new Sprite("../Textures/Cutscene/frame7.jpg");
		SceneManager::frame8 = new Sprite("../Textures/Cutscene/frame8.jpg");

		SceneManager::settings_page = new Sprite("../textures/Settings/settings.png");
		SceneManager::credits_page = new Sprite("../textures/Credits/credits.png");

		SceneManager::win_overlay = new Sprite("../textures/Victory.jpg");
		//SceneManager::cover1 = new Sprite("../textures/Tiles/Pods/PodCover_3.png");
		//SceneManager::player_stuck = new Sprite("../textures/Bami/Sinking/BaMi_Sinking_1.png");


		int screenwidth = 0, screenheight = 0;
		glfwGetWindowSize(Window::window_ptr, &screenwidth, &screenheight);
		gameIsPaused = false;
		isMenuState = true;
		isHowToPlay = false;
		isSettings = false;
		isCredits = false;
		isWalk = false;
		isLevel1 = false;
		isLevel2 = false;
		isQuestTab = false;
		isWinCondition = false;
		isPlayerinSinkhole = false;
		loaded = false;
		HowToPlayPage = 0;
		CutscenePage = 0;
#endif // !EDITOR

		//player = new Player();

		/*sp = new Sprite("../textures/level1.jpg");
		sp->transformation.scale = glm::vec2(2000, 2000);
		sp->transformation.position = glm::vec2(0);*/

		/*Editor::LevelEditor::AddToFactory(CoreSystem)*/
		//SceneManager::loadTile(); //scene manager

		////the moving ingredient
		//ingredient = new Sprite(Editor::LevelEditor::texpath);
		//ingredient->transformation.scale = glm::vec2(100, 100);
		//ingredient->transformation.position = glm::vec2(15, 20);

	}

	Window::~Window()
	{
		timetodeletegrid = true;
		Map::ResetMap();
#ifndef EDITOR

		SceneManager::destroyHowToOverlay(); //delete How to play overlay
		SceneManager::destroySettings();
		SceneManager::destroyWinOverlay(); //delete Win Overlay
		SceneManager::destroyCutscene();
		SceneManager::destroyPlayer_Stuck();

		//JSONSerializer::Serialize(player, "../Data/generated.json");
#endif
		delete player;

		glfwTerminate();
		Editor::LevelEditor::imguiDestroyObj();
	}

	void Window::Input()
	{
		//display main menu
		/*Sprite::menu->transformation.Position = glm::vec2(0, 0);
		Sprite::menu->transformation.Scale = glm::vec2(1920, 1080);*/


		//if (ImGui::IsKeyPressed(GLFW_KEY_M) && isMenuState == false)
		//{
		//	keystate_M = true;
		//	std::cout << "you are pressing menu" << std::endl;
		//	if (keystate_M)
		//	{
		//		//clear all player
		//		isLevel1 = false;
		//		isLevel2 = false;
		//		isMenuState = true;
		//		SceneManager::restartLevel();


		//		keystate_M = false;
		//	}
		//}

		/*Hi all, I'm testing here to use our own input system.
		The original code is commented up above, if anything goes wrong can bring them back */

		//std::cout << "value of key is: " << key.IsKeyPressed(M) << std::endl;
		//std::cout << "value of key is: " << key.IsKeyPressed(M) << std::endl;
#ifndef EDITOR

		if (keystate_M)
		{
			isMenuState = true;
			keystate_M = false;
			isLevel1 = false;
			isLevel2 = false;
			loaded = false;

		}

		if (keystate_tab)
		{
			// if i press tab
			// isquestab(false) = true;
			// off the tab state

			// if i pres tab again
			// isquestab(true) = false;
			// off the tab state

			std::cout << "opening quest tab" << std::endl;
			isQuestTab = !isQuestTab;
			keystate_tab = false;
			std::cout << isQuestTab << " <-- boolean state for quest tab\n";
		}


		if (keystate_1)
		{
			keystate_1 = true;
			std::cout << "you have loaded level 1" << std::endl;
			if (keystate_1)
			{

				isMenuState = false;
				isLevel1 = true;
				isLevel2 = false;

				SceneManager::restartLevel();

				//SceneManager::tilecontainer.clear();
				//SceneManager::ingredientcontainer.clear();


				keystate_1 = false;
			}
		}
		if (keystate_2)
		{
			keystate_2 = true;
			std::cout << "you have loaded level 2" << std::endl;
			if (keystate_2)
			{

				isMenuState = false;
				isLevel1 = false;
				isLevel2 = true;
				loaded = false;

				SceneManager::restartLevel();
				//SceneManager::tilecontainer.clear();
				//SceneManager::ingredientcontainer.clear();


				keystate_2 = false;
			}
		}
		if (keystate_T && isMenuState == false)
		{
			keystate_T = true;
			std::cout << "you are in level selection screen" << std::endl;
			if (keystate_T)
			{

				isMenuState = false;
				isLevel1 = false;
				isLevel2 = false;
				isLevelSelection = true;
				SceneManager::restartLevel();

				keystate_T = false;
			}
		}

		if (mouseLeft)
		{
			//place_obj = true;
			//if (place_obj)
			//{
				//std::cout << "placing obj at x: " << ingredient->transformation.position.x << "and y: " << ingredient->transformation.position.y << std::endl;
				//place_obj = false;
			//}
		}

		if (keystate_escape && (isLevel1 || isLevel2) )
		{
			gameIsPaused = !gameIsPaused;
			keystate_escape = false;
			/*if (keystate_escape && (isLevel1 || isLevel2))
			{
				gameIsPaused = true;
				//std::cout << "game paused, pause screen showing" << std::endl;
				keystate_escape = false;
			}
			else if (!keystate_escape && (isLevel1 || isLevel2) )
			{
				gameIsPaused = false;
				keystate_escape = false;
			} */
		}
		//if press escape again, close pause screen
		if (gameIsPaused == false)
		{
				keystate_escape = true;
				if (keystate_escape)
				{
					gameIsPaused = false;
					//std::cout << "game resume, no more pause screen" << std::endl;
					int screenwidth = 0, screenheight = 0;
					glfwGetWindowSize(Window::window_ptr, &screenwidth, &screenheight);
					//SceneManager::pause_overlay->transformation.Position.x = screenwidth;
					//SceneManager::pause_overlay->transformation.Position.y = screenheight;
					keystate_escape = false;

				}

		}
		/**************************************/
		//BUTTONS DISPLAYED AT MAIN MENU
		/**************************************/

		if (mouseLeft && isMenuState == true)
		{
			std::cout << "mouse clicking (windows.cpp)" << std::endl;
			double xpos = 0, ypos = 0;
			glfwGetCursorPos(Window::window_ptr, &xpos, &ypos);

			//std::cout << "clicking button at x: " << xpos << " and y: " << ypos << std::endl;

			//MENU BUTTON - START (PLAY GAME), reference StartButton.json 
			if (xpos > 275 && xpos < (275 + 266) && ypos > 349 && ypos < (349 + 96))
			{

				isMenuState = false;
				isCutscene = true;
				
				//std::cout << "exit main menu" << std::endl;
				int screenwidth = 0, screenheight = 0;
				glfwGetWindowSize(Window::window_ptr, &screenwidth, &screenheight);
				/*Sprite::menu->transformation.Position.x = screenwidth;
				Sprite::menu->transformation.Position.y = screenheight;*/

			}
			//HOW TO PLAY
			if (xpos > 275 && xpos < (275 + 266) && ypos > 520 && ypos < (520 + 96))
			{
				isHowToPlay = true;
				//std::cout << "in how to play screen" << std::endl;
			}
			//SETTINGS
			if (xpos > 275 && xpos < (275 + 266) && ypos > 700 && ypos < (700 + 96))
			{
				isSettings = true;
			}
			//MENU BUTTON - QUIT, reference ExitButton.json
			if (xpos > 275 && xpos < (275 + 266) && ypos > 890 && ypos < (890 + 96))
			{
				glfwSetWindowShouldClose(window_ptr, true);
			}

		}
		/**************************************/
		//BUTTONS DISPLAYED WHEN GAME IS PAUSED
		/**************************************/
		if (mouseLeft && gameIsPaused == true)
		{
			double xpos = 0, ypos = 0;
			glfwGetCursorPos(Window::window_ptr, &xpos, &ypos);

			//std::cout << "clicking button at x: " << xpos << " and y: " << ypos << std::endl;

			//RESUME THE GAME BUTTON
			if (xpos > 600 && ypos > 460 && xpos < 1310 && ypos < 560)
			{
				gameIsPaused = false;
				//std::cout << "game resume, no more pause screen" << std::endl;
				int screenwidth = 0, screenheight = 0;
				glfwGetWindowSize(Window::window_ptr, &screenwidth, &screenheight);
				SceneManager::howtoplay_overlay1->transformation.Position.x = screenwidth;
				SceneManager::howtoplay_overlay1->transformation.Position.y = screenheight;

			}
			//RETURN TO MAIN MENU
			if (xpos > 600 && ypos > 585 && xpos < 1310 && ypos < 687)
			{
				isMenuState = true;
				isLevel1 = false;
				isLevel2 = false;
				SceneManager::restartLevel();
			}
			//QUIT GAME
			if (xpos > 600 && ypos > 714 && xpos < 1310 && ypos < 815)
			{
				glfwSetWindowShouldClose(window_ptr, true);
			}
		}
		//note: escape should be mapped to pause/menu
		//if (glfwGetKey(window_ptr, GLFW_KEY_ESCAPE))
		//{
		//	

		//	//the code below closes the game
		//	//glfwSetWindowShouldClose(window_ptr, true);
		//}
		if ((keystate_right || keystate_D) && gameIsPaused == false && isWinCondition == false && isMenuState == false)
		{
			keystate_right = true;
			if (keystate_right)
			{
				Map::collision_check_right();
				Map::print_map_to_console();

				keystate_right = false;
			}
		}

		else if ((keystate_left || keystate_A) && gameIsPaused == false && isWinCondition == false && isMenuState == false)
		{
			keystate_left = true;
			//player only move on one press
			//holding key or let go key, player stop
			if (keystate_left)
			{
				Map::collision_check_left();
				Map::print_map_to_console();

				keystate_left = false;
			}
		}

		else if ((keystate_up || keystate_W) && gameIsPaused == false && isWinCondition == false && isMenuState == false)
		{
			keystate_up = true;

			if (keystate_up)
			{
				Map::collision_check_up();
				Map::print_map_to_console();
				AudioManager.PlaySFX("WalkSFX.wav");
				//isWalk = true; //play walking sfx
				keystate_up = false;

			}

		}

		else if ( (keystate_down) || (keystate_S) && gameIsPaused == false && isWinCondition == false && isMenuState == false) 
		{
			keystate_down = true;
			if (keystate_down)
			{
				Map::collision_check_down();
				Map::print_map_to_console();

				keystate_down = false;
			}
		}

		/***************************
			restart key "R" resets the level
		*******************************/
		if (keystate_R && (gameIsPaused == false && isWinCondition == false))
		{
			keystate_R = true;
			if (keystate_R)
			{
				//restart
				SceneManager::restartLevel();
				std::cout << "restarting level" << std::endl;
				std::cout << "player is moved back to x: " << player->playerpos_restart.x << " and y: " << player->playerpos_restart.y << std::endl;

				keystate_R = false;
			}

		}
		if(keystate_down || keystate_up || keystate_left || keystate_right == true)
		/*if (ImGui::IsKeyReleased(GLFW_KEY_DOWN)) keystate_down = true;
		if (ImGui::IsKeyReleased(GLFW_KEY_UP)) keystate_up = true;
		if (ImGui::IsKeyReleased(GLFW_KEY_LEFT)) keystate_left = true;
		if (ImGui::IsKeyReleased(GLFW_KEY_RIGHT)) keystate_right = true;
		if (ImGui::IsKeyReleased(GLFW_KEY_R)) keystate_R = true;*/

		//if(keystate_down && keystate_up && keystate_left && keystate_right)
			player->stop();
#endif //editor
	}

	void Window::Resize()
	{
		int width, height;
		glfwGetWindowSize(window_ptr, &width, &height);
		if (width != m_width || height != m_height)
		{
			m_width = width;
			m_height = height;
			glViewport(0, 0, width, height);
			camera->Update_Viewport(width, height);
			printf("resized \n");
		}
	}

	void Window::Mainloop()
	{
		while (!glfwWindowShouldClose(window_ptr))
		{
			/*FOR DEBUGGING PURPOSES*/
			//std::cout << "Player x: " << player->playerpos.x << " , " << "Player y: " << player->playerpos.y << std::endl;
			/*--------------------------*/
			//Font::RenderText(,"This is sample text", 25.0f, 25.0f, 1.0f, glm::vec3(0.5, 0.8f, 0.2f));
			starttime = glfwGetTime();
			pseudomain::update();

			//for each frame 
			Resize();
			Input();

			glClearColor(0.39f, 0.58f, 0.92f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			Shaders->Textured_Shader()->use();
			/*Editor::LevelEditor::AddToFactory(CoreSystem)*/
			//Map::DrawMap(); //shifted into boolean

			// all drawing goes here ..
			//Sprite::menu->transformation.Position = glm::vec2(0, 0);
			//Sprite::menu->transformation.Scale = glm::vec2(1000, 800);



			Shaders->Textured_Shader()->Send_Mat4("projection", camera->Get_Projection());

			/*Shaders->Textured_Shader()->Send_Mat4("model_matrx", sp->transformation.Get());
			sp->draw();*/

			//the moving ingredient
#if defined(EDITOR) | defined(_EDITOR)
			
			/*
			ingredient = new Sprite(Editor::LevelEditor::texpath);
			ingredient->transformation.Scale = glm::vec2(100, 100);
			ingredient->transformation.Position = glm::vec2(600,600);
			*/
			//display object at imgui cursor
			Core::Editor::LevelEditor::imguiObjectCursor();
			/*
			Shaders->Textured_Shader()->Send_Mat4("model_matrx", ingredient->transformation.Get());
			ingredient->draw();
			*/

			if (!loaded)
			{
				if (SceneManager::tilecontainer.size() > 0 && SceneManager::ingredientcontainer.size() > 0)
				{
					Map::ResetMap();
				}

				std::cout << "current level displayed in editor mode is: " << Editor::LevelEditor::imguiloadedmap << std::endl;
				Map::initMap(Editor::LevelEditor::imguiloadedmap);
				Map::LoadMap();
				loaded = true;

			}
			if (loaded = true)
			{
				Shaders->Textured_Shader()->Send_Mat4("model_matrx", player->Transformation());
				player->draw(delta);

			}
			Map::DrawMap();
#endif

			//FOR OBJ CONTAINER DEBUGGING
			// 
			//std::cout << "what is inside obj container:" << std::endl;
			//for (auto& x : CoreSystem->objfactory->ObjectContainer)
			//{
			//	std::cout << x.first << std::endl; //should print out menu.json

			//	Transform* transcomp = static_cast<Transform*>(x.second->GetObjectProperties()->GetComponent(ComponentID::Transform));

			//	//menu->transformation.Position = { 0,0 };
			//	//menu->transformation.Scale = { 50,50 };
			//
			//	//std::cout << x.second->characteristics->GetID(); // should print the transform ID saved into container
			//}
			//std::cout << "end of obj container\n";

			//Sprite::menu->transformation.Position = {0.f,0.f};
			//Sprite::menu->transformation.Scale = { 50,50 };
			//Shaders->Textured_Shader()->Send_Mat4("model_matrx", Sprite::menu->transformation.Get());
#ifndef EDITOR

			if (isCutscene)
			{
				SceneManager::loadCutscene(0, 0);
				SceneManager::drawCutscene();
				if ( (keystate_space) && isMenuState == false )
				{
					keystate_space = true;
					if (keystate_space)
					{
						double xpos = 0, ypos = 0;
						glfwGetCursorPos(Window::window_ptr, &xpos, &ypos);
						//NEXT PAGE
						if (CutscenePage < 8)
						{

							CutscenePage++;

							std::cout << "next page" << std::endl;

						}
						if (CutscenePage == 7)
						{
							isCutscene = false;
							isLevel1 = true;
							CutscenePage = 0;
						}
						keystate_space = false;
					}
					
				}

			}

			//order of rendering
			//step 1: map
			//step 2: pause overlay
			//step 3: main menu
			if (isLevel1 == true)
			{
				isCutscene = false;
				isMenuState = false;
				isLevel2 = false;
				if (!loaded)
				{
					if (SceneManager::tilecontainer.size() > 0 && SceneManager::ingredientcontainer.size() > 0)
					{
						Map::ResetMap();
					}
					
					Map::initMap("../TileMap/level1.txt");

					Map::LoadMap();
					loaded = true;

				}
				
				//draw lv1 tile map
				Map::DrawMap();

				//draw playerpos at lvl 1
				Shaders->Textured_Shader()->Send_Mat4("model_matrx", player->Transformation());

				//std::cout << "goals no " << Window::numQuests << std::endl;


				if (gameIsPaused == false)
				{
					player->draw(delta);

				}
				else if (gameIsPaused == true)
				{
					player->draw(0);
					SceneManager::drawHowToOverlay();

				}
				if (Map::isWin())
				{
					//std::cout << "you win!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
					isWinCondition = true;
				}
			}

			if (isWinCondition == true && isLevel1 == true)
			{
				int screenwidth = 0, screenheight = 0;
				glfwGetWindowSize(Window::window_ptr, &screenwidth, &screenheight);
				SceneManager::loadWinOverlay(static_cast<int>(screenwidth * 0.25), static_cast<int>(screenheight * 0.25));
				SceneManager::drawWinOverlay();
				//stop all player controls
				//press button to undraw level 1, and draw level 2
				if (mouseLeft && isWinCondition == true)
				{
					isLevel1 = false;
					isLevel2 = true;
					isWinCondition = false;
					loaded = false;
				}

			}

			if (isLevel2 == true)
			{
				isCutscene = false;
				isLevel1 = false;
				if (!loaded)
				{
					Map::ResetMap();

					Map::initMap("../TileMap/level2.txt");
					Map::LoadMap();

					loaded = true;
				}
				
				//draw lv2 tile map
				Map::DrawMap(); //this will also set numQuests

				//draw playerpos at lvl 2
				Shaders->Textured_Shader()->Send_Mat4("model_matrx", player->Transformation());

				//std::cout << "goals no " << Window::numQuests << std::endl;

				
				if (gameIsPaused == false)
				{
					if (isPlayerinSinkhole)
					{

					}
					else
						player->draw(delta);

				}
				else if (gameIsPaused == true)
				{
					player->draw(0);
					//SceneManager::drawPauseOverlay();

				}
				if (Map::isWin())
				{
					//std::cout << "you win!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
					isWinCondition = true;
				}
			}

			if (isWinCondition == true && isLevel2 == true)
			{
				int screenwidth = 0, screenheight = 0;
				glfwGetWindowSize(Window::window_ptr, &screenwidth, &screenheight);
				SceneManager::loadWinOverlay(static_cast<int>(screenwidth * 0.25), static_cast<int>(screenheight * 0.25));
				SceneManager::drawWinOverlay();
				//stop all player controls
				//press button to undraw level 1, and draw level 2
				if (Map::isWin())
				{
					//std::cout << "you win!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
					isWinCondition = true;
				}
			}

			//Draw Main Menu
			if (isMenuState == true)
			{
				for (auto& x : CoreSystem->objfactory->ObjectContainer)
				{
					Transform* transcomp = static_cast<Transform*>(x.second->GetObjectProperties()->GetComponent(ComponentID::Transform));
					Sprite* spritecomp = static_cast<Sprite*>(x.second->GetObjectProperties()->GetComponent(ComponentID::Renderer));

					spritecomp->transformation.Position = transcomp->Position;
					spritecomp->transformation.Scale = transcomp->Scale;

					Shaders->Textured_Shader()->Send_Mat4("model_matrx", spritecomp->transformation.Get());
					if (x.first == "Menu") //draw menu
						spritecomp->draw();

					if (x.first == "StartButton")
						spritecomp->draw();

					if (x.first == "HowToPlay")
						spritecomp->draw();

					if (x.first == "SettingsButton")
						spritecomp->draw();

					if (x.first == "ExitButton")
						spritecomp->draw();
				}
			}

			if (gameIsPaused == true)
			{
				for (auto& x : CoreSystem->objfactory->ObjectContainer)
				{
					Transform* transcomp = static_cast<Transform*>(x.second->GetObjectProperties()->GetComponent(ComponentID::Transform));
					Sprite* spritecomp = static_cast<Sprite*>(x.second->GetObjectProperties()->GetComponent(ComponentID::Renderer));

					spritecomp->transformation.Position = transcomp->Position;
					spritecomp->transformation.Scale = transcomp->Scale;

					Shaders->Textured_Shader()->Send_Mat4("model_matrx", spritecomp->transformation.Get());
					if (x.first == "PauseMenu")
						spritecomp->draw();

					if (x.first == "ResumeButton")
						spritecomp->draw();

					if (x.first == "QuitButton")
						spritecomp->draw();

					if (x.first == "MenuButton")
						spritecomp->draw();
				}
			}

			if (isQuestTab == true)
			{
				//std::cout << "Drawing tabmenu\n";
				for (auto& x : CoreSystem->objfactory->ObjectContainer)
				{
					Transform* transcomp = static_cast<Transform*>(x.second->GetObjectProperties()->GetComponent(ComponentID::Transform));
					Sprite* spritecomp = static_cast<Sprite*>(x.second->GetObjectProperties()->GetComponent(ComponentID::Renderer));

					spritecomp->transformation.Position = transcomp->Position;
					spritecomp->transformation.Scale = transcomp->Scale;
					Shaders->Textured_Shader()->Send_Mat4("model_matrx", spritecomp->transformation.Get());

					if (x.first == "TabMenu")
					{
						
						spritecomp->draw();
					}
				}
			}

			if (isWalk == true)
			{
				AudioManager.PlaySFX("WalkSFX.wav");
				isWalk = false;
			}

			if (isHowToPlay == true)
			{
				isMenuState = false; //disable menu buttons
				gameIsPaused = false;
				
				SceneManager::loadHowToOverlay(0, 0);
				SceneManager::drawHowToOverlay();
				if (mouseLeft && isMenuState == false)
				{
					double xpos = 0, ypos = 0;
					glfwGetCursorPos(Window::window_ptr, &xpos, &ypos);
					//NEXT PAGE
					if (HowToPlayPage < 3)
					{
						if (xpos > 1651 && xpos < 1732 && ypos > 820 && ypos < 889)
						{

							HowToPlayPage++;

							std::cout << "next page" << std::endl;

						}
					}
					//PREV PAGE 
					if (HowToPlayPage > 0)
					{
						if (xpos > 1525 && xpos < 1608 && ypos > 820 && ypos < 889)
						{

							HowToPlayPage--;

							std::cout << "previous page" << std::endl;

						}
					}


					//BACK
					
					if (xpos > 151 && xpos < 339 && ypos > 820 && ypos < 889)
					{

						isMenuState = true;
						HowToPlayPage = 0;
						isHowToPlay = false;

						std::cout << "return to main menu" << std::endl;

					}
					

				}

			}

			if (isSettings == true)
			{
				SceneManager::loadSettings();
				SceneManager::drawSettings();
				if (mouseLeft)
				{
					double xpos = 0, ypos = 0;
					glfwGetCursorPos(Window::window_ptr, &xpos, &ypos);

					//PRESS CREDITS
					if (xpos > 814 && xpos < 1047 && ypos > 536 && ypos < 612)
					{
						isCredits = true;
						
					}
					//PRESS BACK
					if (xpos > 814 && xpos < 1047 && ypos > 635 && ypos < 708)
					{
						isSettings = false;
					}
				}
			}

			if (isCredits == true)
			{
				if (mouseLeft)
				{
					double xpos = 0, ypos = 0;
					glfwGetCursorPos(Window::window_ptr, &xpos, &ypos);
					std::cout << "clicking button at x: " << xpos << " and y: " << ypos << std::endl;
					if (xpos > 673 && xpos < 1023 && ypos > 710 && ypos < 817)
					{
						isCredits = false;
					}
				}
			}

			////display object at imgui cursor
			//Core::Editor::LevelEditor::imguiObjectCursor();
#if DEBUG
			for (auto test : Editor::LevelEditor::newobjarr)
			{
				Shaders->Textured_Shader()->Send_Mat4("model_matrx", test.spritepath->transformation.Get());
				test.spritepath->draw();
			}
#endif

#endif

			endtime = glfwGetTime();
			delta = (endtime - starttime) / 2;
			pseudomain::draw(); //swap buffers and glfwpollevents are already done here, do not call again below


		}

		glfwSwapBuffers(window_ptr);
		glfwPollEvents();
		
		//void Window::ImGuiToObjContainer(ObjectFactory* c)
		//{

		//	//Editor::LevelEditor::AddToFactory(ObjectFactory)
		//}
	}
}
