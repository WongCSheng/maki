/*
* File: Renderer.cpp
* Author:
* Description: 
*/
#include "Renderer.h"

namespace Core
{
	Renderer::Renderer()
	{
	}

	Renderer::~Renderer()
	{
	}

	void Renderer::Init()
	{
		/*for (unsigned i = 0; i < entities.size(); ++i)
		{
			Model* mesh = entities[i]->GetComponent<Model>();
			if (mesh != NULL)
			{
				meshes.push_back(mesh);
			}
		}*/

		glfwInit();

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
	}

	/*  _________________________________________________________________________ */
		/*! update
		@param none
		@return none

		Uses GLHelper::GLFWWindow* to get handle to OpenGL context.
		For now, there are no objects to animate nor keyboard, mouse button click,
		mouse movement, and mouse scroller events to be processed.
		*/
	void Renderer::Update(const double dt)
	{
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
	void Renderer::Draw()
	{
		// Part 1
		GLApp::draw();

		//imGUI Game Editor
		Editor::LevelEditor::imguiEditorDraw();

		// Part 2: swap buffers: front <-> back
		glfwSwapBuffers(GLHelper::ptr_window);
		glfwPollEvents();
	}

	/*  _________________________________________________________________________ */
	/*! cleanup
	@param none
	@return none

	Return allocated resources for window and OpenGL context thro GLFW back
	to system.
	Return graphics memory claimed through
	*/
	void Renderer::Cleanup()
	{
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

	void Renderer::RegisterComponent(std::unordered_map<std::string, Object::GameObject*> ObjectContainer)
	{

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
}