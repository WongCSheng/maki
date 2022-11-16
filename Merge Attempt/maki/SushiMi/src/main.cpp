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
#include "../Engine/System/Graphics/glapp.h"
#include "../Engine/Core/Core.h"
#include "../Window/GameWindow.h"
#include "../Headers/ImGui_Header.h"
#include "../Editors/LevelEditor.h"

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
	// Part 1
	init();

	// Part 2
	while (!glfwWindowShouldClose(GLHelper::ptr_window)) {
		// Part 2a
		update();

		// Part 2b
		draw();
	}
	//glfwSetKeyCallback(GLHelper::ptr_window, Input::key_callback);

	// Part 3
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
static void update() {
	// Part 1
	glfwPollEvents();

	// Part 2
	GLHelper::update_time(1.0);

	// Part 3
	GLApp::update();

	////imgui
	////New Frame
	//ImGui_ImplOpenGL3_NewFrame();
	//ImGui_ImplGlfw_NewFrame();
	//ImGui::NewFrame();

	////Render
	//ImGui::Render();
	//ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


}

/*  _________________________________________________________________________ */
/*! draw
@param none
@return none

Call application to draw and then swap front and back frame buffers ...
Uses GLHelper::GLFWWindow* to get handle to OpenGL context.
*/
static void draw() {
	// Part 1
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
	// Part 1: set window size
	if (!GLHelper::init(1680, 1050, "Maki Game Engine")) {
		std::cout << "Unable to create OpenGL context" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(MessageCallback, 0);

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
	//AudioManager.LoadMusic("BGM.wav");
	//AudioManager.LoadSound("WalkSFX.wav");
	//play bgm
	//AudioManager.PlayMusic("BGM.wav");
	LogOutput(LogLevel::LOG_LEVEL_WARN, "test");
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
	//AudioManager.UnloadMusic("BGM.wav");
	//AudioManager.UnloadMusic("WalkSFX.wav");

	////imgui
	//Shutdown
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}