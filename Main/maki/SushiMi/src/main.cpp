//******************************************************************************/
/*!
\file		main.cpp
\author 	Thea Sea 50%
\par    	email: thea.sea@digipen.edu
\co-author 	Aurelia Chong 50%
\par    	email: fei.x@digipen.edu

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
#include <WinBase.h>

//	testing
#include "../Headers/Log.h"
#include "Engine/Font/Font.h"


/*                                                   type declarations
----------------------------------------------------------------------------- */


static Core::MainSystem* CoreSystem;
int screenwidth = 0, screenheight = 0;

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
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); //do not remove this line!!!

	//_CrtSetBreakAlloc(1807); //use this to detect memory leaks, replace the number with mem leak location

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

	Editor::LevelEditor::imguiGraphicsTest();

	GLHelper::update_time(1.0);

	CoreSystem->objfactory->Update((Get_Delta()));

	CoreSystem->Update((Get_Delta()));
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
	if (Window::show_fps)
	{
		Shaders->Font_Shader()->use();
		if (GLHelper::fps < 60)
		{

			Font::RenderText(*Shaders, "FPS: " + to_string(GLHelper::fps), screenwidth * 0.95f, screenheight * 0.95f, .5f, glm::vec3(1.f, 0.f, 0.f),1.f);
		}
		else
		{
			Font::RenderText(*Shaders, "FPS: " + to_string(GLHelper::fps), screenwidth * 0.95f, screenheight * 0.95f, .5f, glm::vec3(0.f, 1.f, 0.f), 1.f);
		}
	}
	//imGUI Game Editor



	Editor::LevelEditor::imguiEditorDraw();


	// Part 2: swap buffers: front <-> back
	glfwSwapBuffers(Window::window_ptr);
	glfwPollEvents();
}

void GLAPIENTRY
MessageCallback(GLenum /*source*/,
	GLenum type,
	GLuint /*id*/,
	GLenum /*severity*/,
	GLsizei /*length*/,
	const GLchar* /*message*/,
	const void* /*userParam*/)
{
	if (type == GL_DEBUG_TYPE_ERROR) {
		//fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
			//(type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
			//type, severity, message);
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
	glfwGetWindowSize(Window::window_ptr, &screenwidth, &screenheight);

	CoreSystem->Init();
	CoreSystem->objfactory->Init();
	Font::init();
	CoreSystem->objfactory->DeserializeObjects("../Assets/test.json");
	/*might need this if we using latin characters*/
	std::setlocale(LC_ALL, "en_US.UTF-8");

	//loading the entire main_menu which consists of all the buttons
	Core::DeserializeAll("../Data/mainMenu/MenuAll.json", CoreSystem->objfactory);
	//loading the entire pause_menu which consists of all the buttons
	Core::DeserializeAll("../Data/pauseMenu/PauseMenuAll.json", CoreSystem->objfactory);

	//How to play screens
	DeserializeAll("../Data/mainMenu/HowToPlayScene.json", CoreSystem->objfactory);

	//loading main menu
	Core::DeserializeEntity("../Data/Menu.json", CoreSystem->objfactory);

	/*	Loading QuestTab_base that is going to appear in every level that shows the quest of that level	*/
	Core::DeserializeEntity("../Data/Chop/questBase.json", CoreSystem->objfactory);

	/*	 Loading of Chops (Done)	*/
	Core::DeserializeEntity("../Data/Chop/denied.json", CoreSystem->objfactory);
	Core::DeserializeEntity("../Data/Chop/denied_2.json", CoreSystem->objfactory);
	Core::DeserializeEntity("../Data/Chop/denied_3.json", CoreSystem->objfactory);

	/*	 Loading of Chops (Denied)	*/
	Core::DeserializeEntity("../Data/Chop/done.json", CoreSystem->objfactory);
	Core::DeserializeEntity("../Data/Chop/done_2.json", CoreSystem->objfactory);
	Core::DeserializeEntity("../Data/Chop/done_3.json", CoreSystem->objfactory);

			/*	Loading all ingredients	by level*/
	//tut1
	Core::DeserializeEntity("../Data/Levels/Quest_Tut1.json", CoreSystem->objfactory);

	//tut2
	Core::DeserializeEntity("../Data/Levels/Quest_Tut2.json", CoreSystem->objfactory);

	//Lv1
	Core::DeserializeEntity("../Data/Levels/Quest_Lv1.json", CoreSystem->objfactory);

	//Lv2
	Core::DeserializeEntity("../Data/Levels/Quest_Lv2.json", CoreSystem->objfactory);

	//Lv3
	Core::DeserializeEntity("../Data/Levels/Quest_Lv3.json", CoreSystem->objfactory);

	//lv4
	Core::DeserializeEntity("../Data/Levels/Quest_Lv4.json", CoreSystem->objfactory);

	//Lv5
	Core::DeserializeEntity("../Data/Levels/Quest_Lv5.json", CoreSystem->objfactory);

	//Lv6
	Core::DeserializeEntity("../Data/Levels/Quest_Lv6.json", CoreSystem->objfactory);

	//Lv7
	Core::DeserializeEntity("../Data/Levels/Quest_Lv7.json", CoreSystem->objfactory);

	//Lv8
	Core::DeserializeEntity("../Data/Levels/Quest_Lv8.json", CoreSystem->objfactory);

	//Lv9
	Core::DeserializeEntity("../Data/Levels/Quest_Lv9.json", CoreSystem->objfactory); //json cannot read its filepath on 3rd ingrd

	//Lv10
	Core::DeserializeEntity("../Data/Levels/Quest_Lv10.json", CoreSystem->objfactory);  

	//Lv11
	Core::DeserializeEntity("../Data/Levels/Quest_Lv11.json", CoreSystem->objfactory);

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
	//mixed ingredients
	Core::DeserializeEntity("../Data/Ingredients/Salmon_Wasabi.json", CoreSystem->objfactory);
	Core::DeserializeEntity("../Data/Ingredients/Octopus_Wasabi.json", CoreSystem->objfactory);
	Core::DeserializeEntity("../Data/Ingredients/Tuna_Soya.json", CoreSystem->objfactory);
	Core::DeserializeEntity("../Data/Ingredients/Roes_Soya_Wasabi.json", CoreSystem->objfactory);

	Core::DeserializeEntity("../Data/Ingredients/Wasabi.json", CoreSystem->objfactory);
	Core::DeserializeEntity("../Data/Ingredients/Tea.json", CoreSystem->objfactory);
	Core::DeserializeEntity("../Data/Ingredients/Soya.json", CoreSystem->objfactory);




	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(MessageCallback, 0);

	//load GLAD so it configures OpenGL
	//gladLoadGL(); //do not uncomment this, glad header does not work

	glViewport(0, 0, 1920, 1080); //resize window

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// Part 2
	GLHelper::print_specs(); //uncommented
	glfwMakeContextCurrent(Window::window_ptr);
#if defined(RELEASE)| defined(RELEASE)
	//make fullscreen
	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);
	glfwSetWindowMonitor(Window::window_ptr, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
#endif

	// Part 3
	//Editor::LevelEditor::imguiEditorInit(); //shifted into mainsystem
#if defined(EDITOR) | defined(EDITOR)
	//CoreSystem->leveleditorsystem->imguiEditorInit();
	CoreSystem->AccessSystem<Core::Editor::LevelEditor>(Core::SystemID::LevelEditor)->imguiEditorInit();

#endif

	//load audio files
	AudioManager.LoadMusic("BGM.ogg");
	AudioManager.LoadSFX("Closing container.ogg");
	AudioManager.LoadVoice("YES_1.ogg");
	AudioManager.LoadVoice("Sad_1.ogg");
	AudioManager.LoadVoice("Dialogue_1.ogg");
	AudioManager.LoadVoice("Dialogue_2.ogg");
	AudioManager.LoadVoice("Dialogue_3.ogg");
	AudioManager.LoadVoice("Dialogue_4.ogg");
	AudioManager.LoadVoice("Dialogue_5.ogg");
	AudioManager.LoadVoice("Idle_1.ogg");
	AudioManager.LoadVoice("Curious_3.ogg");
	AudioManager.LoadVoice("Oof_1.ogg");
	AudioManager.LoadSFX("Pouring.ogg");
	AudioManager.LoadSFX("Squeezing.ogg");
	//AssetsManager::GetInstance()->Add_files("../Assets");
	//play bgm
	AudioManager.PlayMusic("BGM.ogg");
	AudioManager.SetMusicVolume(0.7f);

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
	/*AudioManager.UnloadMusic("BGM.ogg");
	AudioManager.UnloadMusic("BGM with Forest Day volume test.ogg");
	AudioManager.UnLoadSFX("Gravel_Drag-Movement_1.ogg");*/
	AudioManager.CleanPlaying();
	AudioManager.Free();

	////imgui Shutdown
#if defined(DEBUG) | defined(_DEBUG)
	Editor::LevelEditor::imguiShutDown();
#endif

	CoreSystem->clear();
	delete CoreSystem;
}