#include <iostream>
//using namespace std;

#include "Window.h"
/*                                                   type declarations
----------------------------------------------------------------------------- */
#include "../Headers/ImGui_Header.h"
//#include "../Engine/Core/Core.h"
#include "../Editors/imfilebrowser.h"
#include "../Editors/LevelEditor.h"
#include "../Headers/Log.h"
#include "../Engine/Audio/AudioEngine.h"
/*                                                      function declarations
----------------------------------------------------------------------------- */

//void cleanup();
void main()
{
	// Enable run-time memory check for debug builds.
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	//Core::MainSystem* CoreSystem = new Core::MainSystem();

	Window* window = new Window(800, 600);
	glfwInit();
	pseudomain::init();
	window->Mainloop(); //already does while (!windowshould close)

	/*while (!glfwWindowShouldClose(Window::window_ptr))
	{
		update();
		draw();
	}*/
	
	delete window;
	pseudomain::cleanup();
	//CoreSystem->clear();
}

void pseudomain::update()
{
	glfwPollEvents();

	GLHelper::update_time(1.0);
	Editor::LevelEditor::imguiGraphicsTest();


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

void pseudomain::init() {

	
	// Part 1: set window size
	/*if (!GLHelper::init(1680, 1050, "Maki Game Engine")) {
		std::cout << "Unable to create OpenGL context" << std::endl;
		std::exit(EXIT_FAILURE);
	}*/

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
	//glfwMakeContextCurrent();

	// Part 3
	Editor::LevelEditor::imguiEditorInit();



	//load audio files
	AudioManager.LoadMusic("BGM.wav");
	AudioManager.LoadSound("WalkSFX.wav");

	//play bgm
	AudioManager.PlayMusic("BGM.wav");
	LogOutput(LogLevel::LOG_LEVEL_WARN, "test");//this is for testing, u can create your own warning msg when u use
}


void pseudomain::draw()
{

	//imGUI Game Editor
	Editor::LevelEditor::imguiEditorDraw();

	glfwSwapBuffers(Window::window_ptr);
	// Part 2: swap buffers: front <-> back
	glfwPollEvents();
}


void pseudomain::cleanup()
{
	AudioManager.UnloadMusic("BGM.wav");
	AudioManager.UnloadMusic("WalkSFX.wav");
	GLHelper::cleanup();
	Editor::LevelEditor::imguiShutDown();
	
}