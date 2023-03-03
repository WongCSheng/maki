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
#include "Engine/Font/Font.h"


/*                                                   type declarations
----------------------------------------------------------------------------- */


static Core::MainSystem* CoreSystem;

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

//int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow);


int WINAPI WinMain([[maybe_unused]] HINSTANCE hInstance, [[maybe_unused]] _Inout_ HINSTANCE hPrevInstance,
	[[maybe_unused]] LPSTR lpCmdLine, [[maybe_unused]] int nCmdShow)
{
	
	// Enable run-time memory check for debug builds.
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	
	//_CrtSetBreakAlloc(1231); //use this to detect memory leaks, replace the number with mem leak location

#endif

	//systems that were new and not deleted
	CoreSystem = new Core::MainSystem();

	Core::pseudomain::init();

	/*----------------------------------------------*/

	CoreSystem->AccessSystem<Core::Window>(Core::SystemID::Windows)->Mainloop();
	
	Core::pseudomain::cleanup();

	return 0;
	
}

int main() {

	return WinMain(GetModuleHandle(NULL), NULL, GetCommandLineA(), SW_SHOWNORMAL);

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

	GLHelper::getDelta();

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
	Shaders->Font_Shader()->use();
	if (GLHelper::fps < 60)
	{
		
		Font::RenderText(*Shaders, "FPS: " + to_string(GLHelper::fps), 747.0f, 590.f, .2f, glm::vec3(1.f, 0.f, 0.f));
	}
	else
	{
		Font::RenderText(*Shaders,"FPS: " +  to_string(GLHelper::fps), 747.0f, 590.f, .2f, glm::vec3(0.f, 1.f, 0.f));
	}


	Editor::LevelEditor::imguiEditorDraw();


	// Part 2: swap buffers: front <-> back
	glfwSwapBuffers(Window::window_ptr);
	glfwPollEvents();
}

void GLAPIENTRY
MessageCallback(GLenum /*source*/,
	GLenum type,
	GLuint /*id*/,
	GLenum severity,
	GLsizei /*length*/,
	const GLchar* message,
	const void* /*userParam*/)
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
	Font::init();
	CoreSystem->objfactory->DeserializeObjects("../Assets/test.json");

	Core::DeserializeAll("../Data/mainMenu/MenuAll.json", CoreSystem->objfactory);
	Core::DeserializeAll("../Data/pauseMenu/PauseMenuAll.json", CoreSystem->objfactory);
	//loading main menu
	//Core::DeserializeEntity("../Data/Menu.json", CoreSystem->objfactory);

	/*	Loading QuestTab base	*/
	Core::DeserializeEntity("../Data/Quests/questBase.json", CoreSystem->objfactory); 

	/*	Loading of ingredients	*/
	Core::DeserializeEntity("../Data/Ingredients/Avocado.json", CoreSystem->objfactory);
	Core::DeserializeEntity("../Data/Ingredients/Corn.json", CoreSystem->objfactory);
	Core::DeserializeEntity("../Data/Ingredients/Cucumber.json", CoreSystem->objfactory);
	Core::DeserializeEntity("../Data/Ingredients/Inari.json", CoreSystem->objfactory);
	Core::DeserializeEntity("../Data/Ingredients/Nori.json", CoreSystem->objfactory);
	Core::DeserializeEntity("../Data/Ingredients/Octopus.json", CoreSystem->objfactory);
	Core::DeserializeEntity("../Data/Ingredients/Rice.json", CoreSystem->objfactory);
	Core::DeserializeEntity("../Data/Ingredients/Roes.json", CoreSystem->objfactory);
	Core::DeserializeEntity("../Data/Ingredients/Salmon.json", CoreSystem->objfactory);
	Core::DeserializeEntity("../Data/Ingredients/Tamago.json", CoreSystem->objfactory);
	Core::DeserializeEntity("../Data/Ingredients/Tofu.json", CoreSystem->objfactory);
	Core::DeserializeEntity("../Data/Ingredients/Tuna.json", CoreSystem->objfactory);
	Core::DeserializeEntity("../Data/Ingredients/Wasabi.json", CoreSystem->objfactory);
	Core::DeserializeEntity("../Data/Ingredients/Tea.json", CoreSystem->objfactory);
	Core::DeserializeEntity("../Data/Ingredients/Soya.json", CoreSystem->objfactory);

	/*Loading of quest chop*/
	Core::DeserializeEntity("../Data/Quests/done.json", CoreSystem->objfactory);
	Core::DeserializeEntity("../Data/Quests/denied.json", CoreSystem->objfactory);

	/*Core::DeserializeEntity("../Data/Tut1/QuestTut1.json", CoreSystem->objfactory);
	Core::DeserializeEntity("../Data/Tut2/QuestTut2.json", CoreSystem->objfactory);
	Core::DeserializeEntity("../Data/Lv1/QuestLv1.json", CoreSystem->objfactory);
	Core::DeserializeEntity("../Data/Lv2/QuestLv2.json", CoreSystem->objfactory);
	Core::DeserializeEntity("../Data/Lv3/QuestLv3.json", CoreSystem->objfactory);
	Core::DeserializeEntity("../Data/Lv4/QuestLv4.json", CoreSystem->objfactory);
	Core::DeserializeEntity("../Data/Lv5/QuestLv5.json", CoreSystem->objfactory);
	Core::DeserializeEntity("../Data/Lv6/QuestLv6.json", CoreSystem->objfactory);*/


	////loading image&button paths
	//Core::DeserializeEntity("../Data/StartButton.json", CoreSystem->objfactory);
	//Core::DeserializeEntity("../Data/HowToPlay.json", CoreSystem->objfactory);
	//Core::DeserializeEntity("../Data/SettingsButton.json", CoreSystem->objfactory);
	//Core::DeserializeEntity("../Data/ExitButton.json", CoreSystem->objfactory);

	////loading pause menu & buttons
	/*Core::DeserializeEntity("../Data/PauseMenu.json",CoreSystem->objfactory);
	Core::DeserializeEntity("../Data/ResumeButton.json", CoreSystem->objfactory);
	Core::DeserializeEntity("../Data/QuitButton.json", CoreSystem->objfactory);
	Core::DeserializeEntity("../Data/MenuButton.json", CoreSystem->objfactory);*/


	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(MessageCallback, 0);

	//load GLAD so it configures OpenGL
	//gladLoadGL(); //do not uncomment this, glad header does not work

	glViewport(0, 0, 800, 800); //resize window

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// Part 2
	GLHelper::print_specs(); //uncommented
	glfwMakeContextCurrent(Window::window_ptr);

	// Part 3
	//Editor::LevelEditor::imguiEditorInit(); //shifted into mainsystem
#if defined(EDITOR) | defined(EDITOR)
	//CoreSystem->leveleditorsystem->imguiEditorInit();
	CoreSystem->AccessSystem<Core::Editor::LevelEditor>(Core::SystemID::LevelEditor)->imguiEditorInit();

#endif

	//load audio files
	AudioManager.LoadMusic("BGM.wav");
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
	AudioManager.UnloadMusic("BGM with Forest Day volume test.wav");
	AudioManager.UnLoadSFX("Gravel_Drag-Movement_1.wav");

	////imgui Shutdown
#if defined(DEBUG) | defined(_DEBUG)
	Editor::LevelEditor::imguiShutDown();
#endif

	CoreSystem->clear();
	delete CoreSystem;
}