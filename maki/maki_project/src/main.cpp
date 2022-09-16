#include <../include/common_headers.hpp>

//GLFWwindow * window;
//int main()
//{
//	//IMGUI_CHECKVERSION();
//	//ImGui::CreateContext();
//	//ImGuiIO& io = ImGui::GetIO(); (void)io;
//	//ImGui::StyleColorsDark();
//	//ImGui_ImplGlfw_InitForOpenGL(window, true);
//	//ImGui_ImplOpenGL3_Init("#version 330");
//
//	////Main while loop
//	//while (!glfwWindowShouldClose(window))
//	//{
//	//	//bg colour
//	//	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
//	//	//clean back buffer, assign new colour
//	//	glClear(GL_COLOR_BUFFER_BIT);
//
//	//	//tell imGui we are working on a new frame now
//	//	ImGui_ImplOpenGL3_NewFrame();
//	//	ImGui_ImplGlfw_NewFrame();
//	//	ImGui::NewFrame();
//
//	//
//
//	//}
//
//	return 0;
//}


/*                                                                   includes
----------------------------------------------------------------------------- */
// Extension loader library's header must be included before GLFW's header!!!
#include <../include/glhelper.h>
#include <../include/glapp.h>
#include <iostream>

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
	// Part 1
	init();

	// Part 2
	while (!glfwWindowShouldClose(GLHelper::ptr_window)) {
		// Part 2a
		update();
		// Part 2b
		draw();
	}

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

	// Part 2: swap buffers: front <-> back
	glfwSwapBuffers(GLHelper::ptr_window);
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
	// Part 1
	if (!GLHelper::init(2400, 1350, "Maki Game Engine")) {
		std::cout << "Unable to create OpenGL context" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	// Part 2
	GLHelper::print_specs(); //uncommented


	// Part 3
	GLApp::init();
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
}
