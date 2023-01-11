//******************************************************************************/
/*!
\file		Window.cpp
\author 	Thea Sea (45%)
\par    	email: thea.sea@digipen.edu
\co-author	Aurelia Chong (45%)
\par    	email: fei.x@digipen.edu
\co-author	Louis Wang (10%)
\par    	email: louishetong.wang@digipen.edu
\date   	2/8/2022
\brief		This source file contains the main function to call all other functions and implement the game loop.
			It instantiates player and sprites as well.

Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/




/*                                                                   includes
----------------------------------------------------------------------------- */
#include "Window.h"
#include "../../imgui/imgui.h"
#include "../Engine/Serialiser/JSONSerializer.h"
#include "../Headers/SceneManager.h"


/*                                                             input key states
----------------------------------------------------------------------------- */
static bool keystate_left = false;
static bool keystate_right = false;
static bool keystate_up = false;
static bool keystate_down = false;
static bool keystate_R = false;

Player* player;
/*					key  callback function  , helper function for controlling input
	----------------------------------------------------------------------------- */
void keyCallBack(GLFWwindow* pwin, int key, int scancode, int action, int mod)
{
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
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_MAXIMIZED, true);

	window_ptr = glfwCreateWindow(width, height, "ANIMATION ONLY", NULL, NULL);
	if (window_ptr == nullptr)
	{
		std::cout << "erorr initilize glfw" << std::endl;
		return;
	}

	glfwMakeContextCurrent(window_ptr);

	glfwSetKeyCallback(window_ptr, keyCallBack); //callback to the key everytime the key is pressed

	if (glewInit())
	{
		std::cout << "erorr initilize glew" << std::endl;
		return;
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);



	player = JSONSerializer::Deserialize("../Data/generated.json");
	starttime = 0;
	endtime = 0;
	delta = 0;

	Shaders = std::make_unique<ShaderLibrary>();
	camera = std::make_unique<Camera>(0, 0);

	//player = new Player();

	sp = new Sprite("../textures/level1.jpg");
	sp->transformation.scale = glm::vec2(2000, 2000);
	sp->transformation.position = glm::vec2(0);
}

Window::~Window()
{
	JSONSerializer::Serialize(player, "../Data/generated.json");
	delete player;
	delete sp; //16 bytes 
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
			if (ImGui::IsKeyReleased(GLFW_KEY_RIGHT))
			{
				player->stop();
			}
			player->move_right();

			keystate_right = false;
		}
	}

	else if (ImGui::IsKeyPressed(GLFW_KEY_LEFT))
	{
		//player only move on one press
		//holding key or let go key, player stop
		if (keystate_left)
		{
			if (ImGui::IsKeyReleased(GLFW_KEY_LEFT))
			{
				player->stop();
			}
			player->move_left();

			keystate_left = false;
		}
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
		restartLevel();
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
	while (!glfwWindowShouldClose(window_ptr))
	{
		starttime = glfwGetTime();
		pseudomain::update();

		//for each frame 
		Resize();
		Input();
		pseudomain::draw(); //swap buffers and glfwpollevents are already done here, do not call again below
		glClearColor(0.39f, 0.58f, 0.92f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// all drawing goes here ..
		Shaders->Textured_Shader()->use();
		Shaders->Textured_Shader()->Send_Mat4("projection", camera->Get_Projection());

		Shaders->Textured_Shader()->Send_Mat4("model_matrx", sp->transformation.Get());
		sp->draw();

		Shaders->Textured_Shader()->Send_Mat4("model_matrx", player->Transformation());
		player->draw(delta);


		endtime = glfwGetTime();
		delta = (endtime - starttime) / 2;
	}
	glfwSwapBuffers(window_ptr);
	glfwPollEvents();
}

