#include "App.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "Window.h"
#include "../Common/Vector3.h"
#include "gl_BackEnd.h"
#include "Scene.h"
#include "timer.h"
#include "Asset.h"
#include "MainSystem.h"
#include "ShaderStorage.h"

bool App::second = false;
App* App::instance = 0;

App::App() : 
startedTimer(false),
frameRate(60)
{
	timer = new StopWatch();
}


App::~App()
{
	if (timer != NULL)
	{
		delete timer;
		timer = NULL;
	}

	if (scene != NULL)
	{
		delete scene;
		scene = NULL;
	}
}

void App::Start()
{
	GlfwSetup();
	window = Window::getInstance();
	window->SetUp();

	GlewSetup();

	glViewport(0, 0, (window->Width()), (window->Height()));

	glfwSetCursorPos(Window::getInstance()->window, Window::getInstance()->Width() * 0.5, Window::getInstance()->Height() * 0.5);

	printf("GL version: %s\n", glGetString(GL_VERSION));

	ShaderStorage::Instance().InitShaders();

	Asset::Instance().Init();

	scene = new Scene();
	scene->Init();
	
	MainSystem::Instance().RegisterComponents(scene->entities);

	gl_BackEnd* handle = gl_BackEnd::getInstance();
	
	handle->GLBackEndRun(scene);

	StartTimer();
}

void App::Run()
{
	while (true)
	{
		CalculateFPS();

		gl_BackEnd* handle = gl_BackEnd::getInstance();
		handle->GLPollEvents();

		MainSystem::Instance().Update(deltaTime);
		scene->Run(deltaTime);
		TimerShldWait(1000/frameRate);
		if (scene->exit)
		{
			break;
		}
	}

	ShaderStorage::Instance().CleanUpShaders();
	Asset::Instance().CleanUp();

	gl_BackEnd::getInstance()->GLFWBackEndTerminate();
}

void App::GlfwSetup()
{
	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}
}

void App::GlewSetup()
{
	//Glew set up
	glewExperimental = true; //Needed for core profile

	//Initialize GLEW
	GLenum err = glewInit();

	//If GLEW hasn't initialized
	if (err != GLEW_OK)
	{
		std::cout << "Error: %s\n" << glewGetErrorString(err) << std::endl;
	}
}

void App::CalculateFPS(void)
{
	deltaTime = static_cast<float>(timer->getElapsedTime());
	FPS = 1 / deltaTime;

	if (FPS < 58)
		std::cout << FPS << std::endl;
}

void App::StartTimer(void)
{
	if (!startedTimer)
	{
		timer->startTimer();
		startedTimer = true;
	}
}

void App::TimerShldWait(long long time)
{
	timer->waitUntil(time); //Accurately waits at 60fps if stated 60fps and will not go above.
}

void App::Exit()
{

}

double App::DeltaTime(void)
{
	return deltaTime;
}

int App::WindowWidth(void)
{
	return window->Width();
}

int App::WindowHeight(void)
{
	return window->Height();
}