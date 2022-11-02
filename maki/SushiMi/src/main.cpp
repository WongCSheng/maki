/*******************!

SushiMi main file!!

Note: to test out any function, put it in each function in the main loop
eg if you are testing an update function, go into update() and put your function in there

******************/


/*                                                                   includes
----------------------------------------------------------------------------- */
// Extension loader library's header must be included before GLFW's header!!!
#include <../include/common_headers.hpp>
#include <../include/glapp.h>
#include <crtdbg.h> 
#include <memory>
#include <../include/AudioEngine.h>



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

	
	//collision that isnt working
	/*for (auto& e1 : Object::objects)
	{
		if (e1.first == "Bami")
		{
			for (auto& e2 : Object::objects)
			{
				if (e1.first != e2.first)
				{
					e1.second.update(GLHelper::delta_time);
					e2.second.update(GLHelper::delta_time);
					if (Collision::CollisionIntersection_RectRect(e1.second.aabb, e1.second.velocity, e2.second.aabb, e2.second.velocity) == 1)
					{
						std::cout << "Collision detected between " << e1.first << " and " << e2.first << std::endl;
					}
					else
						std::cout << "No collision detected" << std::endl;
				}
			}
		}
		else
			break;
	}*/
	
	
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
	imguiEditorDraw();

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

	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(0);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// Part 2
	GLHelper::print_specs(); //uncommented

	// imgui 
	////Setup IMGUI
	//IMGUI_CHECKVERSION();
	//ImGui::CreateContext();
	//ImGuiIO& io = ImGui::GetIO(); (void)io;
	//ImGui::StyleColorsDark();
	//ImGui_ImplGlfw_InitForOpenGL(GLHelper::ptr_window, true);
	//ImGui_ImplOpenGL3_Init((char*)glGetString(GL_NUM_SHADING_LANGUAGE_VERSIONS));

	glfwMakeContextCurrent(GLHelper::ptr_window);


	// Part 3
	GLApp::init();

	imguiEditorInit();

	//load audio files
	AudioManager.LoadMusic("BGM.wav");
	AudioManager.LoadSound("WalkSFX.wav");
	//play bgm
	AudioManager.PlayMusic("BGM.wav");
	
	//test serialize
	/*using namespace rapidjson;
	using namespace std;

	Document doc;
	doc.SetObject();

	rapidjson::Value temp(rapidjson::kObjectType);
	Serializer serializing;
	temp = serializing.SerializeObjects("../testObject.json", Object::objects);
	doc.AddMember("TestClass", temp, doc.GetAllocator());*/



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

	////imgui
	//Shutdown
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}
