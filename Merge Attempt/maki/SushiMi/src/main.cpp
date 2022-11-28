//******************************************************************************/
/*!
\file		main.cpp
\author 	Thea Sea
\par    	email: thea.sea@digipen.edu
\date   	2/8/2022
\brief		This source file contains the main function to call all other functions and implement the game loop

Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/




/*                                                                   includes
----------------------------------------------------------------------------- */
// Extension loader library's header must be included before GLFW's header!!!
#include "../Headers/STL_Header.h"
//#include "../../glad/glad/glad.h"
#include "../Engine/System/Graphics/glapp.h"
#include "../Engine/Core/Core.h"
#include "../Window/GameWindow.h"
#include "../Headers/ImGui_Header.h"
#include "../Editors/imfilebrowser.h"
#include "../Editors/LevelEditor.h"
#include "../Engine/Audio/AudioEngine.h"

//#include "../Mono/Mono.h"
#include <memory> 
#include <crtdbg.h> 

//	testing
#include "../Headers/Log.h"

/*                                                   type declarations
----------------------------------------------------------------------------- */



/*                                                      function declarations
----------------------------------------------------------------------------- */
static void draw();
static void update();
static void init();
static void cleanup();

static Core::MainSystem* CoreSystem = new Core::MainSystem();
static Core::Object::GameObject* TestObj = new Core::Object::GameObject();


/*                                                      function definitions
----------------------------------------------------------------------------- */
/*  _________________________________________________________________________ */
/*! main

@param none

@return int

Indicates how the program existed. Normal exit is signaled by a return value of
0. Abnormal termination is signaled by a non-zero return value.
Note that the C++ compiler will insert a return 0 statement if one is missing.
*/
int main() {

	// Enable run-time memory check for debug builds.
	#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	#endif

	glfwInit();
	init();

	// Part 2
	while (!glfwWindowShouldClose(GLHelper::ptr_window)) 
	{
		update();
		draw();
	}
	//glfwSetKeyCallback(GLHelper::ptr_window, Input::key_callback);

	cleanup();
}

/*  _________________________________________________________________________ */
/*! update
@param none
@return none

Uses GLHelper::GLFWWindow* to get handle to OpenGL context.
For now, there are no objects to animate nor keyboard, mouse button click,
mouse movement, and mouse scroller events to be processed.
*/
static void update() 
{
	glfwPollEvents();

	GLHelper::update_time(1.0);
	Editor::LevelEditor::imguiGraphicsTest();

	GLApp::update();

	CoreSystem->objfactory->Update(GLHelper::delta_time);

	CoreSystem->Update(GLHelper::delta_time);

	
}

/*  _________________________________________________________________________ */
/*! draw
@param none
@return none

Call application to draw and then swap front and back frame buffers ...
Uses GLHelper::GLFWWindow* to get handle to OpenGL context.
*/
static void draw() 
{
	GLApp::draw();
	
	//imGUI Game Editor
	Editor::LevelEditor::imguiEditorDraw();
	
	// Part 2: swap buffers: front <-> back
	glfwSwapBuffers(GLHelper::ptr_window);
	glfwPollEvents();
}

void GLAPIENTRY
MessageCallback(GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar* message,
	const void* userParam)
{
	if (type == GL_DEBUG_TYPE_ERROR) {
		fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
			(type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
			type, severity, message);
	}

}


/*  _________________________________________________________________________ */
/*! init
@param none
@return none

The OpenGL context initialization stuff is abstracted away in GLHelper::init.
The specific initialization of OpenGL state and geometry data is
abstracted away in GLApp::init
*/
static void init() {

	CoreSystem->Init();
	CoreSystem->objfactory->Init();
	TestObj->Init();

	CoreSystem->objfactory->SerializeObjects("../Assets/test.json");

	// Part 1: set window size
	if (!GLHelper::init(1680, 1050, "Maki Game Engine")) {
		std::cout << "Unable to create OpenGL context" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(MessageCallback, 0);

	//load GLAD so it configures OpenGL
	//gladLoadGL(); //do not uncomment this, glad header does not work

	glViewport(0, 0, 800, 800);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// Part 2
	GLHelper::print_specs(); //uncommented
	glfwMakeContextCurrent(GLHelper::ptr_window);

	// Part 3
	GLApp::init();
	Editor::LevelEditor::imguiEditorInit();
	
	

	//load audio files
	AudioManager.LoadMusic("BGM.wav");
	AudioManager.LoadSound("WalkSFX.wav");
	//play bgm
	AudioManager.PlayMusic("BGM.wav");

	LogOutput(LogLevel::LOG_LEVEL_WARN, "test");//this is for testing, u can create your own warning msg when u use
}

/*  _________________________________________________________________________ */
/*! cleanup
@param none
@return none

Return allocated resources for window and OpenGL context thro GLFW back
to system.
Return graphics memory claimed through
*/
void cleanup() {
	// Part 1
	GLApp::cleanup();

	// Part 2
	GLHelper::cleanup();
	//unload music
	AudioManager.UnloadMusic("BGM.wav");
	AudioManager.UnloadMusic("WalkSFX.wav");

	////imgui Shutdown
	Editor::LevelEditor::imguiShutDown();

	CoreSystem->clear();
}