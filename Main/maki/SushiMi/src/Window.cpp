/*                                                                   includes
----------------------------------------------------------------------------- */
#include "Window.h"
#include "../../imgui/imgui.h"
#include "../Engine/Serialiser/JSONSerializer.h"
#include "../Editors/imfilebrowser.h"
#include "../Headers/SceneManager.h"
#include "../Game Object/Player.h"
//#include "../Engine/Texture/Sprite.h"
#include "../Engine/Shaders/ShaderLibrary.h"
#include "../Engine/Camera/Camera2D.h"
#include "../Headers/SceneManager.h"

namespace Core
{
	/*                                                             input key states
	----------------------------------------------------------------------------- */
	static bool keystate_left = false;
	static bool keystate_right = false;
	static bool keystate_up = false;
	static bool keystate_down = false;
	static bool keystate_R = false;
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
			
		}
		else if (GLFW_RELEASE == action)
		{
			keystate_left = true;
			keystate_right = true;
			keystate_up = true;
			keystate_down = true;
			keystate_R = true;
		}
	}

	Window::Window(int width, int height)
		:m_width(width),
		m_height(height)

	{
		glfwInit();

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_MAXIMIZED, true);
		window_ptr = glfwCreateWindow(width, height, "SushiMi Engine", NULL, NULL);
		if (window_ptr == nullptr)
		{
			std::cout << "erorr initilize glfw" << std::endl;
			return;
		}

		glfwMakeContextCurrent(window_ptr);
		std::cout << glewGetErrorString(glewInit());
			
		/*if (glewInit())
		{
			std::cout << "erorr initilize glew" << std::endl;
			return;
		}*/
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


		JSONSerializer::LevelLoadPath = "../Data/generated.json"; //initialise Bami position
		player = JSONSerializer::Deserialize(*JSONSerializer::LevelLoadPathPtr);
		starttime = 0;
		endtime = 0;
		delta = 0;



		Shaders = std::make_unique<ShaderLibrary>();
		camera = std::make_unique<Camera>(0, 0);

		//player = new Player();

		/*sp = new Sprite("../textures/level1.jpg");
		sp->transformation.scale = glm::vec2(2000, 2000);
		sp->transformation.position = glm::vec2(0);*/

		/*Editor::LevelEditor::AddToFactory(CoreSystem)*/
		SceneManager::loadTile(); //scene manager

		//the moving ingredient
		ingredient = new Sprite(Editor::LevelEditor::texpath);
		ingredient->transformation.scale = glm::vec2(100, 100);
		ingredient->transformation.position = glm::vec2(15, 20);

		a = nullptr;

		
	}

	Window::~Window()
	{
		SceneManager::destroyTile();
		//JSONSerializer::Serialize(player, "../Data/generated.json");
		delete player;
		delete sp; //16 bytes 
		delete ingredient;
		glfwTerminate();
	}

	void Window::Input()
	{

		//if (ImGui::IsMouseReleased(MOUSEEVENTF_LEFTDOWN))
		//{
		//	//place_obj = true;
		//	//if (place_obj)
		//	//{
		//		std::cout << "placing obj at x: " << ingredient->transformation.position.x << "and y: " << ingredient->transformation.position.y << std::endl;
		//		//place_obj = false;
		//	//}
		//}

		if (glfwGetKey(window_ptr, GLFW_KEY_ESCAPE))
		{
			glfwSetWindowShouldClose(window_ptr, true);
		}

		if (ImGui::IsKeyPressed(GLFW_KEY_RIGHT))
		{
			keystate_right = true;
			//std::cout << "you are pressing right" << std::endl;
			if (keystate_right)
			{
				player->move_right();
				keystate_right = false;
			}
		}

		else if (ImGui::IsKeyPressed(GLFW_KEY_LEFT))
		{
			keystate_left = true;
			//player only move on one press
			//holding key or let go key, player stop
			if (keystate_left)
			{			
				player->move_left();
				keystate_left = false;
			}
		}

		else if (ImGui::IsKeyPressed(GLFW_KEY_UP))
		{
			keystate_up = true;

			if (keystate_up)
			{
				player->move_up();
				keystate_up = false;
			}

		}


		else if (ImGui::IsKeyPressed(GLFW_KEY_DOWN))
		{
			keystate_down = true;
			if (keystate_down)
			{
				player->move_down();
				keystate_down = false;
			}
		}

		/*
			restart key "R" resets the level
		*/
		if (ImGui::IsKeyPressed(GLFW_KEY_R))
		{
			if (keystate_R)
			{
				//restart
				std::cout << "restarting level" << std::endl;
				player->restart();
				std::cout << "player is moved back to x: " << player->playerpos_restart.x << " and y: " <<player->playerpos_restart.y << std::endl;
				
				keystate_R = false;
			}

		}

		if (ImGui::IsKeyReleased(GLFW_KEY_DOWN)) keystate_down = true;
		if (ImGui::IsKeyReleased(GLFW_KEY_UP)) keystate_up = true;
		if (ImGui::IsKeyReleased(GLFW_KEY_LEFT)) keystate_left = true;
		if (ImGui::IsKeyReleased(GLFW_KEY_RIGHT)) keystate_right = true;
		if (ImGui::IsKeyReleased(GLFW_KEY_R)) keystate_R = true;

		
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

			starttime = glfwGetTime();

			

			pseudomain::update();
			pseudomain::draw(); //swap buffers and glfwpollevents are already done here, do not call again below

			//for each frame 
			Resize();
			Input();

			glClearColor(0.39f, 0.58f, 0.92f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			
			/*Editor::LevelEditor::AddToFactory(CoreSystem)*/

			// all drawing goes here ..
			Shaders->Textured_Shader()->use();
			Shaders->Textured_Shader()->Send_Mat4("projection", camera->Get_Projection());

			/*Shaders->Textured_Shader()->Send_Mat4("model_matrx", sp->transformation.Get());
			sp->draw();*/

			Shaders->Textured_Shader()->Send_Mat4("model_matrx", ingredient->transformation.Get());
			ingredient->draw();

			Shaders->Textured_Shader()->Send_Mat4("model_matrx", player->Transformation());
			player->draw(delta);

			SceneManager::drawTile();

			//display object at imgui cursor
			Core::Editor::LevelEditor::imguiObjectCursor();


			endtime = glfwGetTime();
			delta = (endtime - starttime) / 2;
		}
		glfwSwapBuffers(window_ptr);
		glfwPollEvents();
		
	}
	void Window::ImGuiToObjContainer(ObjectFactory* c)
	{

		//Editor::LevelEditor::AddToFactory(ObjectFactory)
	}
}