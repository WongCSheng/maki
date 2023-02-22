/*!*****************************************************************************

\file       imguiEditor.cpp
\author     Thea Sea. thea.sea, 2102348
\par        DP email: thea.sea@digipen.edu
\par        Course: CSD2400/GAM200
\date       7-10-2022

\brief
This program implements a Game Engine Editor using ImGui
Modifies and saves each game project into a file upon pressing the save option.

Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

*******************************************************************************/
#define STB_IMAGE_IMPLEMENTATION
#include "../../stb-master/stb_image.h"
#include "LevelEditor.h"
#include "imfilebrowser.h"
#include "../testshader.h"
#include "../src/Window.h"

//std::vector<std::string> ObjVector;
//std::vector<const char*> objectString;
int i = 0;
//unsigned int VBO, VAO;
//unsigned int EBO;
// create a file browser instance
static ImGui::FileBrowser fileDialog;
unsigned int texture1, texture2;
unsigned int ID;
int width, height, nrChannels;
const char* texpath = "../textures/menu.jpg";
std::string path;

//Shader ourShader("../shaders/SushiMi.vert", "../shaders/SushiMi.frag");


void Editor::LevelEditor::imguiEditorInit(void)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(Window::window_ptr, true);
	ImGui_ImplOpenGL3_Init("#version 450");

	//code to fill a vector with the names of all game objects, replace hardcoded 57 with the detected number of game elements
	/*for (int i = 1; i < 57 * 14; i += 14)
	{
		const char* s2 = Scene::ObjVector[i].c_str();
		objectString.push_back(s2);
	}*/
	
	// create a file browser instance
	ImGui::FileBrowser fileDialog;

	// (optional) set browser properties
	fileDialog.SetTitle("ImGui File Explorer");
	//fileDialog.SetPwd("../maki/textures/");
	//fileDialog.SetCurrentTypeFilterIndex(0);

	//std::string vertexCode;
	//std::string fragmentCode;
	//std::ifstream vShaderFile;
	//std::ifstream fShaderFile;
	//// ensure ifstream objects can throw exceptions:
	//vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	//fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	//try
	//{
	//	// open files
	//	vShaderFile.open("../shaders/test.vert");
	//	fShaderFile.open("../shaders/test.frag");
	//	std::stringstream vShaderStream, fShaderStream;
	//	// read file's buffer contents into streams
	//	vShaderStream << vShaderFile.rdbuf();
	//	fShaderStream << fShaderFile.rdbuf();
	//	// close file handlers
	//	vShaderFile.close();
	//	fShaderFile.close();
	//	// convert stream into string
	//	vertexCode = vShaderStream.str();
	//	fragmentCode = fShaderStream.str();
	//}
	//catch (std::ifstream::failure& e)
	//{
	//	std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << e.what() << std::endl;
	//}
	//const char* vShaderCode = vertexCode.c_str();
	//const char* fShaderCode = fragmentCode.c_str();
	//// 2. compile shaders
	//unsigned int vertex, fragment;
	//// vertex shader
	//vertex = glCreateShader(GL_VERTEX_SHADER);
	//glShaderSource(vertex, 1, &vShaderCode, NULL);
	//glCompileShader(vertex);
	////checkCompileErrors(vertex, "VERTEX");
	//// fragment Shader
	//fragment = glCreateShader(GL_FRAGMENT_SHADER);
	//glShaderSource(fragment, 1, &fShaderCode, NULL);
	//glCompileShader(fragment);
	////checkCompileErrors(fragment, "FRAGMENT");
	//// shader Program
	//ID = glCreateProgram();
	//glAttachShader(ID, vertex);
	//glAttachShader(ID, fragment);
	//glLinkProgram(ID);
	////checkCompileErrors(ID, "PROGRAM");
	//// delete the shaders as they're linked into our program now and no longer necessary
	//glDeleteShader(vertex);
	//glDeleteShader(fragment);


	//// Vertices coordinates
	//float vertices[] = {
	//	// positions          // colors           // texture coords
	//	 1.f,  1.f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
	//	 1.f, -1.f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
	//	 -1.f, -1.f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
	//	-1.f,  1.f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
	//};
	//unsigned int indices[] = {
	//0, 1, 3, // first triangle
	//1, 2, 3  // second triangle
	//};

	//// Create reference containers for the Vertex Array Object and the Vertex Buffer Object
	//
	//glGenVertexArrays(1, &VAO);
	//glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);

	//glBindVertexArray(VAO);

	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//// position attribute
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(0);
	//// color attribute
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(1);
	//// texture coord attribute
	//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	//glEnableVertexAttribArray(2);


	//// load and create a texture 
	//// -------------------------
	//
	//
}

void Editor::LevelEditor::imguiGraphicsTest(void)
{
	if (fileDialog.HasSelected())
	{
		std::cout << "Selected filename" << fileDialog.GetSelected().string() << std::endl;
		path = fileDialog.GetSelected().string();
		std::replace(path.begin(), path.end(), '\\', '/');
		texpath = path.c_str();

		fileDialog.ClearSelected();
	}

	//// texture 1
	//// ---------
	//glGenTextures(1, &texture1);
	//glBindTexture(GL_TEXTURE_2D, texture1);
	//// set the texture wrapping parameters
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//// set texture filtering parameters
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//// load image, create texture and generate mipmaps
	//stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
	//// The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.

	//

	//unsigned char* data = stbi_load(texpath, &width, &height, &nrChannels, 0);
	//if (data)
	//{
	//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	//	glGenerateMipmap(GL_TEXTURE_2D);
	//}
	//else
	//{
	//	std::cout << "Failed to load texture" << std::endl;
	//}
	//stbi_image_free(data);
	//// texture 2
	//// ---------
	//glGenTextures(1, &texture2);
	//glBindTexture(GL_TEXTURE_2D, texture2);
	//// set the texture wrapping parameters
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//// set texture filtering parameters
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//// load image, create texture and generate mipmaps
	//const char* b = "../textures/BaMi_Idle1.png";
	//data = stbi_load(b, &width, &height, &nrChannels, 0);
	//if (data)
	//{
	//	// note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
	//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	//	glGenerateMipmap(GL_TEXTURE_2D);
	//}
	//else
	//{
	//	std::cout << "Failed to load texture" << std::endl;
	//}
	//stbi_image_free(data);
	//width = mainclass::size * 1;
	//// tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
	//// -------------------------------------------------------------------------------------------
	//glUseProgram(ID);
	////glUseProgram(texture2);
	////ID.use(); // don't forget to activate/use the shader before setting uniforms!
	//// either set it manually like so:
	////glUniform1i(glGetUniformLocation(ourShader.ID, "texture1"), 0);
	//// or set it via the texture class
	////ourShader.setInt("texture2", 1);
	//glUniform1i(glGetUniformLocation(ID, "texture1"), 0);
	//glUniform1i(glGetUniformLocation(ID, "texture2"), 1);
	////std::cout << ID << std::endl;

	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, texture1);
	//glActiveTexture(GL_TEXTURE1);
	//glBindTexture(GL_TEXTURE_2D, texture2);

	//// render container
	//glUseProgram(ID);
	////ourShader.use();

	//glBindVertexArray(VAO);
	//if (mainclass::drawTexture)
	//{
	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	//}
	//// Exporting variables to shaders
	///*glUseProgram(shaderProgram);
	//glUniform1f(glGetUniformLocation(shaderProgram, "size"), mainclass::size);
	//glUniform4f(glGetUniformLocation(shaderProgram, "color"), mainclass::color[0], mainclass::color[1], mainclass::color[2], mainclass::color[3]);*/

	//// bind textures on corresponding texture units
	///*glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, texture1);
	//glActiveTexture(GL_TEXTURE1);
	//glBindTexture(GL_TEXTURE_2D, texture2);*/


	////std::cout << ID << std::endl;

	//
	//
	////// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
	////// -------------------------------------------------------------------------------
	////glfwSwapBuffers(window);
	////glfwPollEvents();
}

void Editor::LevelEditor::imguiEditorDraw(void)
{
	fileDialog.SetTypeFilters({ ".png", ".jpg" });


	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	ImGui::ShowDemoWindow();
	ImGui::ShowDebugLogWindow();
	

	if (mainclass::drawTexture)
	{
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}

	ImGui::Begin("Object Editor - Imgui Window");
	ImGui::Text("Click to Select Object");
	
	

	ImGui::Text("The selected object is: ");
	//ImGui::Checkbox("Display Texture", &mainclass::drawTexture);
	// Slider that appears in the window
	ImGui::SliderFloat("Size", &mainclass::size, 0.5f, 2.0f);
	// Fancy color editor that appears in the window
	ImGui::ColorEdit4("Color", mainclass::color);

	
	//ImGui::Text(objectString[i]);
	//ImGui::SliderInt("Object Index", &i, 0, objectString.size()-1);
	//ImGui::SliderFloat("x-position", &Object::objects[objectString[i]].position.x, -500.0f, 500.0f);
	//ImGui::SliderFloat("y-position", &Object::objects[objectString[i]].position.y, -500.0f, 500.0f);
	

	//float *arr[3] = { &Object::objects["temp"].color.r, &Object::objects["temp"].color.g, &Object::objects["temp"].color.b/*, Object::objects["Object5"].color.a*/ };

	//RGB colour selection
	//ImGui::ColorEdit3("Color", *arr);

	if (ImGui::Begin("Object Editor - Imgui Window"))
	{
		// open file dialog when user clicks this button
		if (ImGui::Button("Click here to Open File Explorer"))
			fileDialog.Open();
	}
	ImGui::End();
	fileDialog.Display();

	

	if (ImGui::Button("Demo Background"))
	{
		texpath = "../textures/demo.jpg";
	}

	if (ImGui::Button("Level1 Background"))
	{
		texpath = "../textures/level1.jpg";
	}

	if (ImGui::Button("BaMi Art"))
	{
		texpath = "../textures/test.jpg";
	}

	if (ImGui::Button("Return to Main Menu"))
	{
		texpath = "../textures/menu.jpg";
	}


	ImGui::End();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Editor::LevelEditor::imguiShutDown(void)
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}