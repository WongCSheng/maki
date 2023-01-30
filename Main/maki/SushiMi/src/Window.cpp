/*
File: Transform.cpp
Author:		
email:		
co-Author:  Chong Rui Xuan Aurelia 
email:		fei.x@digipen.edu
Description: 
*/

/*                                                                   includes
----------------------------------------------------------------------------- */
#include "Window.h"
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
	static bool keystate_paused = false;
	static bool place_obj = false;
	Player* player;

	//SceneManager* scnmanager = new SceneManager(); //this is dangerous!! write it in a function so that the new is deleted!!

	/*					key  callback function  , helper function for controlling input
		----------------------------------------------------------------------------- */
	void keyCallBack(GLFWwindow* pwin, int key, int scancode, int action, int mod)
	{
		if (GLFW_REPEAT == action)
		{
			keystate_left = false;
			keystate_right = false;
			keystate_up = false;
			keystate_down = false;
			keystate_R = false;
			keystate_M = false;
			keystate_paused = false;
			
		}
		else if (GLFW_RELEASE == action)
		{
			keystate_left = true;
			keystate_right = true;
			keystate_up = true;
			keystate_down = true;
			keystate_R = true;
			keystate_M = true;
			keystate_paused = true;
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
		std::cout << glewGetErrorString(glewInit()) << std::endl ;  //it says "No error"
			
		/*if (glewInit())
		{
			std::cout << "erorr initilize glew" << std::endl;
			return;
		}*/
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


		Core::LevelLoadPath = "../Data/generated.json"; //initialise Bami position
		player = Core::Deserialize(*Core::LevelLoadPathPtr);

		starttime = 0;
		endtime = 0;
		delta = 0;

		Shaders = std::make_unique<ShaderLibrary>();
		camera = std::make_unique<Camera>(0, 0);
		SceneManager::pause_overlay = new Sprite("../textures/pause.png");
		int screenwidth = 0, screenheight = 0;
		glfwGetWindowSize(Window::window_ptr, &screenwidth, &screenheight);
		gameIsPaused = false;
		isMenuState = true;
		isWalk = false;


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
		SceneManager::destroyTile();
		SceneManager::destroyIngr();
		SceneManager::destroyTrap();
		SceneManager::destroyGoal1();
		SceneManager::destroyGoal2();
		SceneManager::destroyPauseOverlay();
		//JSONSerializer::Serialize(player, "../Data/generated.json");
		delete player;
		delete sp; //16 bytes
		delete obj;
		glfwTerminate();
		Editor::LevelEditor::imguiDestroyObj();
	}

	void Window::Input()
	{
		Sprite::menu->transformation.Position = glm::vec2(0, 0);
		Sprite::menu->transformation.Scale = glm::vec2(1920, 1080);
		//player input
		if (ImGui::IsKeyPressed(GLFW_KEY_M))
		{
			keystate_M = true;
			std::cout << "you are pressing menu" << std::endl;
			if (keystate_M)
			{
				//clear all player
				isMenuState == true;
				keystate_M = false;
			}
		}

		if (ImGui::IsMouseReleased(0))
		{
			//place_obj = true;
			//if (place_obj)
			//{
				//std::cout << "placing obj at x: " << ingredient->transformation.position.x << "and y: " << ingredient->transformation.position.y << std::endl;
				//place_obj = false;
			//}
		}
		if (gameIsPaused == false)
		{
			if (ImGui::IsKeyPressed(GLFW_KEY_ESCAPE))
			{
				keystate_paused = true;
				if (keystate_paused)
				{
					gameIsPaused = true;
					std::cout << "game paused, pause screen showing" << std::endl;
					
					SceneManager::loadPauseOverlay(0, 0);
					
					keystate_paused = false;
				}
			}
		}
		//if press escape again, close pause screen
		else if (gameIsPaused == true)
		{
			if (ImGui::IsKeyPressed(GLFW_KEY_ESCAPE))
			{
				keystate_paused = true;
				if (keystate_paused)
				{
					gameIsPaused = false;
					std::cout << "game resume, no morepause screen" << std::endl;
					int screenwidth = 0, screenheight = 0;
					glfwGetWindowSize(Window::window_ptr, &screenwidth, &screenheight);
					SceneManager::pause_overlay->transformation.Position.x = screenwidth;
					SceneManager::pause_overlay->transformation.Position.y = screenheight;
					keystate_paused = false;

				}
			}

		}
		if (ImGui::IsMouseReleased(0) && isMenuState == true)
		{
			double xpos = 0, ypos = 0;
			glfwGetCursorPos(Window::window_ptr, &xpos, &ypos);
			
			//std::cout << "clicking button at x: " << xpos << " and y: " << ypos << std::endl;

			//MENU BUTTON - START (PLAY GAME) 
			if (xpos > 275 && xpos < 811 && ypos > 349 && ypos < 487)
			{
				isMenuState = false;
				std::cout << "exit main menu" << std::endl;
				int screenwidth = 0, screenheight = 0;
				glfwGetWindowSize(Window::window_ptr, &screenwidth, &screenheight);
				Sprite::menu->transformation.Position.x += screenwidth;
				Sprite::menu->transformation.Position.y += screenheight;

			}
			//MENU BUTTON - QUIT
			if (xpos > 275 && ypos > 890 && xpos < 811 && ypos < 1010)
			{
				glfwSetWindowShouldClose(window_ptr, true);
			}

		}
		if (ImGui::IsMouseReleased(0) && gameIsPaused == true)
		{
			double xpos = 0, ypos = 0;
			glfwGetCursorPos(Window::window_ptr, &xpos, &ypos);

			//std::cout << "clicking button at x: " << xpos << " and y: " << ypos << std::endl;

			//PAUSE THE GAME BUTTON
			if (xpos > 600 && ypos > 460 && xpos < 1310 && ypos <560)
			{
			gameIsPaused = false;
			std::cout << "game resume, no more pause screen" << std::endl;
			int screenwidth = 0, screenheight = 0;
			glfwGetWindowSize(Window::window_ptr, &screenwidth, &screenheight);
			SceneManager::pause_overlay->transformation.Position.x = screenwidth;
			SceneManager::pause_overlay->transformation.Position.y = screenheight;

			}
			//RETURN TO MAIN MENU
			if (xpos > 600 && ypos > 585 && xpos < 1310 && ypos < 687)
			{
				isMenuState = true;
				player->restart();
				player->playerpos.x = player->playerpos_restart.x;
				player->playerpos.y = player->playerpos_restart.y;
				gameIsPaused = false;
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


		//player input
		if ((ImGui::IsKeyPressed(GLFW_KEY_RIGHT)|| ImGui::IsKeyPressed(GLFW_KEY_D)) && gameIsPaused == false)
		{
			keystate_right = true;
			std::cout << "you are pressing right" << std::endl;
			if (keystate_right)
			{
				Map::collision_check_right();
				keystate_right = false;
			}
		}

		else if ((ImGui::IsKeyPressed(GLFW_KEY_LEFT) || ImGui::IsKeyPressed(GLFW_KEY_A)) && gameIsPaused == false)
		{
			keystate_left = true;
			//player only move on one press
			//holding key or let go key, player stop
			if (keystate_left)
			{			
				Map::collision_check_left();
				keystate_left = false;
			}
		}

		else if ((ImGui::IsKeyPressed(GLFW_KEY_UP) || ImGui::IsKeyPressed(GLFW_KEY_W)) && gameIsPaused == false)
		{
			keystate_up = true;

			if (keystate_up)
			{
				Map::collision_check_up();
				isWalk = true;
				keystate_up = false;
				
			}

		}


		else if ((ImGui::IsKeyPressed(GLFW_KEY_DOWN) || ImGui::IsKeyPressed(GLFW_KEY_S)) && gameIsPaused == false)
		{
			keystate_down = true;
			if (keystate_down)
			{
				Map::collision_check_down();
				keystate_down = false;
			}
		}

		/*
			restart key "R" resets the level
		*/
		if (ImGui::IsKeyPressed(GLFW_KEY_R) && gameIsPaused == false)
		{
			keystate_R = true;
			if (keystate_R)
			{
				//restart

				std::cout << "restarting level" << std::endl;
				player->restart(); //tell graphics to reset sprite pos
				std::cout << "player is moved back to x: " << player->playerpos_restart.x << " and y: " <<player->playerpos_restart.y << std::endl;
				//reset our position variable
				player->playerpos.x = player->playerpos_restart.x;
				player->playerpos.y = player->playerpos_restart.y;
				
				keystate_R = false;
			}

		}

		if (ImGui::IsKeyReleased(GLFW_KEY_DOWN)) keystate_down = true;
		if (ImGui::IsKeyReleased(GLFW_KEY_UP)) keystate_up = true;
		if (ImGui::IsKeyReleased(GLFW_KEY_LEFT)) keystate_left = true;
		if (ImGui::IsKeyReleased(GLFW_KEY_RIGHT)) keystate_right = true;
		if (ImGui::IsKeyReleased(GLFW_KEY_R)) keystate_R = true;
		player->stop();
		
		
		
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

			starttime = glfwGetTime();
			pseudomain::update();

			//for each frame 
			Resize();
			Input();

			glClearColor(0.39f, 0.58f, 0.92f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			Shaders->Textured_Shader()->use();
			/*Editor::LevelEditor::AddToFactory(CoreSystem)*/
			Map::DrawMap();
			
			// all drawing goes here ..
			//Sprite::menu->transformation.Position = glm::vec2(0, 0);
			//Sprite::menu->transformation.Scale = glm::vec2(1000, 800);
			


			Shaders->Textured_Shader()->Send_Mat4("projection", camera->Get_Projection());

			/*Shaders->Textured_Shader()->Send_Mat4("model_matrx", sp->transformation.Get());
			sp->draw();*/

			//the moving ingredient
#if defined(EDITOR) | defined(_EDITOR)
			if (ingredient) {
			//delete ingredient;
			ingredient = nullptr;
			} 
			/*
			ingredient = new Sprite(Editor::LevelEditor::texpath);
			ingredient->transformation.Scale = glm::vec2(100, 100);
			ingredient->transformation.Position = glm::vec2(600,600);
			*/
			//display object at imgui cursor
			Core::Editor::LevelEditor::imguiObjectCursor();
#endif
			/*
			Shaders->Textured_Shader()->Send_Mat4("model_matrx", ingredient->transformation.Get());
			ingredient->draw();
			*/

			Shaders->Textured_Shader()->Send_Mat4("model_matrx", player->Transformation());

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
		
			if (gameIsPaused == false)
			{
			player->draw(delta);

			}
			else if (gameIsPaused == true)
			{
				player->draw(0);

			}
			//Draw Pause Overlay
			if (gameIsPaused == true)
			{
			SceneManager::drawPauseOverlay();

			}

			//Draw Main Menu
			Shaders->Textured_Shader()->Send_Mat4("model_matrx", Sprite::menu->transformation.Get());
			if (isMenuState == true)
			{
				Sprite::menu->draw();

			}
			else if (isMenuState == false)
			{
				//AudioManager.LoadMusic("BGM.wav");
				//AudioManager.PlayMusic("BGM.wav");

			}
			
			if (isWalk == true)
			{
				AudioManager.PlayClip("WalkSFX.wav");
				isWalk = false;
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
			
			endtime = glfwGetTime();
			delta = (endtime - starttime) / 2;
			pseudomain::draw(); //swap buffers and glfwpollevents are already done here, do not call again below

		}


		glfwSwapBuffers(window_ptr);
		glfwPollEvents();
		
	}
	void Window::ImGuiToObjContainer(ObjectFactory* c)
	{

		//Editor::LevelEditor::AddToFactory(ObjectFactory)
	}
}