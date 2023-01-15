/*                                                                   includes
----------------------------------------------------------------------------- */
#include "Window.h"
#include "../../imgui/imgui.h"
#include "../Engine/Serialiser/JSONSerializer.h"
#include "../Editors/imfilebrowser.h"
#include "../Headers/SceneManager.h"
#include "../Game Object/Player.h"
#include "../Engine/Texture/Sprite.h"
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

	//SceneManager* scnmanager = new SceneManager(); //this is dangerous!! write it in a function so that the new is deleted!!

	/*					key  callback function  , helper function for controlling input
		----------------------------------------------------------------------------- */
	void keyCallBack(GLFWwindow* pwin, int key, int scancode, int action, int mod)
	{
		/*                                                             input key states
		----------------------------------------------------------------------------- */
		static bool keystate_left = false;
		static bool keystate_right = false;
		static bool keystate_up = false;
		static bool keystate_down = false;
		static bool keystate_R = false;

		Player* player;

		if (GLFW_PRESS == action)
		{
			keystate_left = (key == GLFW_KEY_LEFT) ? true : false;
			keystate_right = (key == GLFW_KEY_RIGHT) ? true : false;
			keystate_up = (key == GLFW_KEY_UP) ? true : false;
			keystate_down = (key == GLFW_KEY_DOWN) ? true : false;
			keystate_R = (key == GLFW_KEY_R) ? true : false;

		}
		else if (GLFW_REPEAT == action)
		{
			keystate_left = false;
			keystate_right = false;
			keystate_up = false;
			keystate_down = false;
			keystate_R = false;
		}

		else if (GLFW_RELEASE == action)
		{
			keystate_left = false;
			keystate_right = false;
			keystate_up = false;
			keystate_down = false;
			keystate_R = false;
		}
	}

	Window::Window(int width, int height)
		:m_width(width),
		m_height(height)

	{
		window_ptr = glfwCreateWindow(width, height, "SushiMi Engine", NULL, NULL);
		if (window_ptr == nullptr)
		{
			std::cout << "erorr initilize glfw" << std::endl;
			return;
		}

		glfwInit();

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_MAXIMIZED, true);


		JSONSerializer::LevelLoadPath = "../Data/generated.json"; //initialise Bami position
		player = JSONSerializer::Deserialize(*JSONSerializer::LevelLoadPathPtr);
		starttime = 0;
		endtime = 0;
		delta = 0;

		if (glewInit())
		{
			std::cout << "erorr initilize glew" << std::endl;
			return;
		}

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		Shaders = std::make_unique<ShaderLibrary>();
		camera = std::make_unique<Camera>(0, 0);

		//player = new Player();

		sp = new Sprite("../textures/level1.jpg");
		sp->transformation.scale = glm::vec2(2000, 2000);
		sp->transformation.position = glm::vec2(0);

		SceneManager::loadTile(); //scene manager

		//the moving ingredient
		sp1 = new Sprite(Editor::LevelEditor::texpath);
		sp1->transformation.scale = glm::vec2(100, 100);
		sp1->transformation.position = glm::vec2(15, 20);
	}

	Window::~Window()
	{
		SceneManager::destroyTile();
		//JSONSerializer::Serialize(player, "../Data/generated.json");
		delete player;
		delete sp; //16 bytes 
		delete sp1;
		glfwTerminate();
	}

	void Window::Input()
	{

		if (glfwGetKey(window_ptr, GLFW_KEY_ESCAPE))
		{
			glfwSetWindowShouldClose(window_ptr, true);
		}

		if (ImGui::IsKeyPressed(GLFW_KEY_RIGHT))
		{
			if (keystate_right)
			{
				player->stop();
			}
			player->move_right();
			keystate_right = false;
		}

		else if (ImGui::IsKeyPressed(GLFW_KEY_LEFT))
		{
			//player only move on one press
			//holding key or let go key, player stop
			if (keystate_left)
			{
				player->stop();
			}
			player->move_left();
			keystate_left = false;
		}

		else if (ImGui::IsKeyPressed(GLFW_KEY_UP))
		{
			if (keystate_up)
			{
				if (ImGui::IsKeyReleased(GLFW_KEY_UP))
				{
					player->stop();
				}
				player->move_up();
				//player->move_right();
				keystate_up = false;
			}
			player->move_up();
			keystate_up = false;
		}


		else if (ImGui::IsKeyPressed(GLFW_KEY_DOWN))
		{
			if (keystate_down)
			{
				if (ImGui::IsKeyReleased(GLFW_KEY_DOWN))
				{
					player->stop();
				}
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
				if (ImGui::IsKeyPressed(GLFW_KEY_R))
				{
					//restart
					std::cout << "restarting level" << std::endl;
					player->restart();
					std::cout << "player is moved back to x: " << Player::playerpos_restart.x << " and y: " << Player::playerpos_restart.y << std::endl;
				}
				keystate_R = false;
			}
		}
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
		starttime = glfwGetTime();

		//display object at imgui cursor
		Core::Editor::LevelEditor::imguiObjectCursor();

		pseudomain::update();
		pseudomain::draw(); //swap buffers and glfwpollevents are already done here, do not call again below
		//for each frame 
		Resize();
		Input();

		glClearColor(0.39f, 0.58f, 0.92f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// all drawing goes here ..
		Shaders->Textured_Shader()->use();
		Shaders->Textured_Shader()->Send_Mat4("projection", camera->Get_Projection());

		Shaders->Textured_Shader()->Send_Mat4("model_matrx", sp->transformation.Get());
		sp->draw();

		Shaders->Textured_Shader()->Send_Mat4("model_matrx", sp1->transformation.Get());
		sp1->draw();

		Shaders->Textured_Shader()->Send_Mat4("model_matrx", player->Transformation());
		player->draw(delta);

		SceneManager::drawTile();

		endtime = glfwGetTime();
		delta = (endtime - starttime) / 2;
		glfwSwapBuffers(window_ptr);
		glfwPollEvents();
	}
}