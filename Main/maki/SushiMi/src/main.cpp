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
#include "../Engine/Core/Core.h"
#include "Window.h"
#include "../Headers/ImGui_Header.h"
#include "../Editors/imfilebrowser.h"
#include "../Editors/LevelEditor.h"
#include "../Engine/System/TextureSystem.h"
#include "../Engine/Audio/AudioEngine.h"
#include "../Engine/Serialiser/JSONSerializer.h"
#include "../Engine/Factory/Factory.h"
#include "../Engine/TileMap/Map.h"

//#include "../Mono/Mono.h"
#include <memory> 
#include <crtdbg.h> 

//	testing
#include "../Headers/Log.h"

/*                                                   type declarations
----------------------------------------------------------------------------- */


static Core::MainSystem* CoreSystem;
static Core::Object::GameObject* TestObj;


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
	
	//_CrtSetBreakAlloc(11379); //use this to detect memory leaks, replace the number with mem leak location

	#endif

	//systems that were new and not deleted
	CoreSystem = new Core::MainSystem();
	TestObj = new Core::Object::GameObject();

	Core::pseudomain::init();
	/*map init*/
	std::string level_file = "../TileMap/level1.txt";
	Core::Map::initMap(level_file);
	CoreSystem->windowsystem->Mainloop();

	delete TestObj;
	Core::pseudomain::cleanup();
}

/*  _________________________________________________________________________ */
/*! update
@param none
@return none

Uses GLHelper::GLFWWindow* to get handle to OpenGL context.
For now, there are no objects to animate nor keyboard, mouse button click,
mouse movement, and mouse scroller events to be processed.
*/
void Core::pseudomain::update() 
{
	glfwPollEvents();

	GLHelper::update_time(1.0);
	Editor::LevelEditor::imguiGraphicsTest();

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
void Core::pseudomain::draw() 
{
	//imGUI Game Editor

//#ifdef Editor_debug
	Editor::LevelEditor::imguiEditorDraw();
//#endif

	// Part 2: swap buffers: front <-> back
	glfwSwapBuffers(Window::window_ptr);
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
void Core::pseudomain::init() {

	CoreSystem->Init();
	CoreSystem->objfactory->Init();
	TestObj->Init();

	CoreSystem->objfactory->DeserializeObjects("../Assets/test.json");

	/*testing if object container is working*/
	Core::DeserializeEntity("../Data/Menu.json", ObjectFactory::ObjectContainer);
	std::cout << "what is inside obj container:" << std::endl;
	for (auto& x : ObjectFactory::ObjectContainer)
	{
		std::cout << x.first << std::endl; //should print out menu.json
		//std::cout << x.second->characteristics->GetID(); // should print the transform ID saved into container
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
	glfwMakeContextCurrent(Window::window_ptr);

	// Part 3
	//Editor::LevelEditor::imguiEditorInit(); //shifted into mainsystem
	CoreSystem->leveleditorsystem->imguiEditorInit();

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
void Core::pseudomain::cleanup() {

	GLHelper::cleanup();
	//unload music
	AudioManager.UnloadMusic("BGM.wav");
	AudioManager.UnloadMusic("WalkSFX.wav");
	AudioManager.UnloadMusic("BGM.wav");

	////imgui Shutdown
	Editor::LevelEditor::imguiShutDown();

	CoreSystem->clear();
	delete CoreSystem;
}