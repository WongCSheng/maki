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
<<<<<<< HEAD
#include "../../stb-master/stb_image.h"
#include "LevelEditor.h"
#include "imfilebrowser.h"
#include "../testshader.h"

//std::vector<std::string> ObjVector;
//std::vector<const char*> objectString;
int i = 0;
extern unsigned int VBO, VAO;
unsigned int EBO;
// create a file browser instance
static ImGui::FileBrowser fileDialog;
unsigned int texture1/*, texture2*/;
unsigned int ID;
int squareX = 0, squareY = 0, squareZ = 0;

const char* texpath = "../textures/menu.jpg";
std::string path;

//Shader ourShader("../shaders/SushiMi.vert", "../shaders/SushiMi.frag");


void Editor::LevelEditor::imguiEditorInit(void)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(GLHelper::ptr_window, true);
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
	
	fileDialog.SetPwd("../textures");



	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	// ensure ifstream objects can throw exceptions:
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		// open files
		vShaderFile.open("../shaders/test.vert");
		fShaderFile.open("../shaders/test.frag");
		std::stringstream vShaderStream, fShaderStream;
		// read file's buffer contents into streams
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		// close file handlers
		vShaderFile.close();
		fShaderFile.close();
		// convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure& e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << e.what() << std::endl;
	}
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();
	// 2. compile shaders
	unsigned int vertex, fragment;
	// vertex shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	//checkCompileErrors(vertex, "VERTEX");
	// fragment Shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	//checkCompileErrors(fragment, "FRAGMENT");
	// shader Program
	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	//checkCompileErrors(ID, "PROGRAM");
	// delete the shaders as they're linked into our program now and no longer necessary
	glDeleteShader(vertex);
	glDeleteShader(fragment);


	//// Vertex Shader source code
	//const char* vertexShaderSource
	//	= "#version 330 core\n"
	//	"layout (location = 0) in vec3 aPos;\n"
	//	"layout (location = 1) in vec3 aColor;\n"
	//	"layout (location = 2) in vec2 aTexCoord;\n"

	//	"out vec3 ourColor;\n"
	//	"out vec2 TexCoord;\n"

	//	"void main()\n"
	//	"{\n"
	//	"   gl_Position = vec4(aPos, 1.0);\n"
	//	//"   gl_Position = vec4(size * aPos.x, size * aPos.y, size * aPos.z, 1.0);\n"
	//	"   ourColor = aColor;\n"
	//	"   TexCoord = aTexCoord;\n"
	//	"}\0";
	////Fragment Shader source code
	//const char* fragmentShaderSource
	//	= "#version 330 core\n"
	//	"out vec4 FragColor;\n"

	//	"in vec3 ourColor;\n"
	//	"in vec2 TexCoord;\n"

	//	"uniform sampler2D ourTexture;\n"

	//	"void main()\n"
	//	"{\n"
	//	"   FragColor = texture(ourTexture, TexCoord);\n"
	//	"}\n\0";

	//// Create Vertex Shader Object and get its reference
	//GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//// Attach Vertex Shader source to the Vertex Shader Object
	//glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	//// Compile the Vertex Shader into machine code
	//glCompileShader(vertexShader);

	//// Create Fragment Shader Object and get its reference
	//GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//// Attach Fragment Shader source to the Fragment Shader Object
	//glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	//// Compile the Vertex Shader into machine code
	//glCompileShader(fragmentShader);

	//// Create Shader Program Object and get its reference
	//GLuint shaderProgram = glCreateProgram();
	//// Attach the Vertex and Fragment Shaders to the Shader Program
	//glAttachShader(shaderProgram, vertexShader);
	//glAttachShader(shaderProgram, fragmentShader);
	//// Wrap-up/Link all the shaders together into the Shader Program
	//glLinkProgram(shaderProgram);

	//// Delete the now useless Vertex and Fragment Shader objects
	//glDeleteShader(vertexShader);
	//glDeleteShader(fragmentShader);

	// build and compile our shader zprogram
// ------------------------------------

	// Vertices coordinates
	float vertices[] = {
		// positions          // colors           // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
	};
	unsigned int indices[] = {
	0, 1, 3, // first triangle
	1, 2, 3  // second triangle
	};

	// Create reference containers for the Vertex Array Object and the Vertex Buffer Object
	
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	
}

void Editor::LevelEditor::imguiGraphicsTest(void)
{
	//give the directory of the texture to display
	if (fileDialog.HasSelected())
	{
		std::cout << "Selected filename" << fileDialog.GetSelected().string() << std::endl;
		path = fileDialog.GetSelected().string();
		std::replace(path.begin(), path.end(), '\\', '/');
		texpath = path.c_str();

		fileDialog.ClearSelected();
	}
	// input
		// -----
	//processInput(window);

	// render
	// ------
	/*glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);*/
	// texture 1
	// ---------
	
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
	// The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.

	

	unsigned char* data = stbi_load(texpath, &mainclass::width, &mainclass::height, &mainclass::nrChannels, 0);
	if (data)
	{

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, mainclass::width, mainclass::height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	
	// texture 2 (idk why its not loading)
	// ---------
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

	// tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
	// -------------------------------------------------------------------------------------------
	glUseProgram(ID);
	//glUseProgram(texture2);
	//ID.use(); // don't forget to activate/use the shader before setting uniforms!
	// either set it manually like so:
	//glUniform1i(glGetUniformLocation(ourShader.ID, "texture1"), 0);
	// or set it via the texture class
	//ourShader.setInt("texture2", 1);
	glUniform1i(glGetUniformLocation(ID, "texture1"), 0);
	//glUniform1i(glGetUniformLocation(ID, "texture2"), 1);
	//std::cout << ID << std::endl;

	//code works fine commented or uncommented?!
	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, texture1);
	
	//commented out as texture 2 not working
	//glActiveTexture(GL_TEXTURE1);
	//glBindTexture(GL_TEXTURE_2D, texture2);

	// render container
	glUseProgram(ID);
	//ourShader.use();

	glBindVertexArray(VAO);
	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	// Exporting variables to shaders
	/*glUseProgram(shaderProgram);
	glUniform1f(glGetUniformLocation(shaderProgram, "size"), mainclass::size);
	glUniform4f(glGetUniformLocation(shaderProgram, "color"), mainclass::color[0], mainclass::color[1], mainclass::color[2], mainclass::color[3]);*/

	// bind textures on corresponding texture units
	/*glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);*/

	
	//// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
	//// -------------------------------------------------------------------------------
	//glfwSwapBuffers(window);
	//glfwPollEvents();
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
	ImGui::Checkbox("Display Texture", &mainclass::drawTexture);
	// Slider that appears in the window
	ImGui::SliderInt("Size", &mainclass::width, mainclass::width -10, mainclass::width +10);
	//ImGui::SliderInt("Size", &width, 1, 10);
	// Fancy color editor that appears in the window
	ImGui::ColorEdit4("Color", mainclass::color);
	if (mainclass::drawTexture)
	{
		// Draw the triangle using the GL_TRIANGLES primitive
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
	
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

	ImGui::Text("Click below to display a sample scene");

	if (ImGui::Button("Demo Background"))
	{
		texpath = "../textures/demo.jpg";
	}
	if (ImGui::Button("Level 1 Background"))
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
	glDeleteTextures(1, &texture1);
	

	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteBuffers(1, &VAO);
	//glDeleteTextures(1, &texture2);
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}
=======
//#include "../../stb-master/stb_image.h"

#include "LevelEditor.h"
#include "imfilebrowser.h"
#include "../Engine/Shaders/ShaderLibrary.h"
#include "../testshader.h"
#include "../src/Window.h"
#include "../Engine/Serialiser/JSONSerializer.h"
#include "../Engine/Factory/Factory.h"
//#include "../Engine/Core/Core.h"
namespace Core
{
	// Simple helper function to load an image into a OpenGL texture with common settings
	bool LoadTextureFromFile(const char* filename, GLuint* out_texture, int* out_width, int* out_height)
	{
		// Load from file
		int image_width = 0;
		int image_height = 0;
		unsigned char* image_data = stbi_load(filename, &image_width, &image_height, NULL, 4);
		if (image_data == NULL)
			return false;

		// Create a OpenGL texture identifier
		GLuint image_texture;
		glGenTextures(1, &image_texture);
		glBindTexture(GL_TEXTURE_2D, image_texture);

		// Setup filtering parameters for display
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // This is required on WebGL for non power-of-two textures
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Same

		// Upload pixels into texture
	#if defined(GL_UNPACK_ROW_LENGTH) && !defined(__EMSCRIPTEN__)
		glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
	#endif
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
		stbi_image_free(image_data);

		*out_texture = image_texture;
		*out_width = image_width;
		*out_height = image_height;

		return true;
	}
	

	//std::vector<std::string> ObjVector;
	//std::vector<const char*> objectString;
	int i = 0;
	//unsigned int VBO, VAO;
	//unsigned int EBO;
	// create a file browser instance
	static ImGui::FileBrowser fileDialog;
	std::filesystem::path m_curr_path;
	static const std::filesystem::path s_TextureDirectory = "../textures";

	namespace Editor
	{
		void LevelEditor::imguiEditorInit(void)
		{
			IMGUI_CHECKVERSION();
			ImGui::CreateContext();
			ImGuiIO& io = ImGui::GetIO(); (void)io;
			ImGui::StyleColorsDark();
			ImGui_ImplGlfw_InitForOpenGL(Window::window_ptr, true);
			//ImGui_ImplOpenGL3_Init();
			ImGui_ImplOpenGL3_Init("#version 450");
#if defined(EDITOR) | defined(_EDITOR)


			//code to fill a vector with the names of all game objects, replace hardcoded 57 with the detected number of game elements
			/*for (int i = 1; i < 57 * 14; i += 14)
			{
				const char* s2 = Scene::ObjVector[i].c_str();
				objectString.push_back(s2);
			}*/

			// create a file browser instance
			static ImGui::FileBrowser fileDialog;
			

			m_curr_path = s_TextureDirectory;
			// (optional) set browser properties
			fileDialog.SetTitle("ImGui File Explorer");
			//fileDialog.SetPwd("../maki/textures/");
			//fileDialog.SetCurrentTypeFilterIndex(0);
#endif

		}

		void LevelEditor::imguiGraphicsTest(void)
		{
#if defined(EDITOR) | defined(_EDITOR)

			if (fileDialog.HasSelected())
			{
				std::cout << "Selected filename" << fileDialog.GetSelected().string() << std::endl;
				path = fileDialog.GetSelected().string();
				std::replace(path.begin(), path.end(), '\\', '/');
				texpath = path.c_str();

				fileDialog.ClearSelected();
			}
#endif
		}

		void LevelEditor::imguiEditorDraw(void)
		{
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();
#if defined(EDITOR) | defined(_EDITOR)



			fileDialog.SetTypeFilters({ ".png", ".jpg", ".json" });

			//in-Editor viewport view:
			//ImGui::Begin("Screen Viewport FrameBuffer Window");
			//int my_image_width = 0;
			//int my_image_height = 0;
			//GLuint my_image_texture = 0;
			//
			//
			////get texel data
			////IM_ASSERT(ret);
			//ImGui::ImageButton((void*)(intptr_t)my_image_texture, ImVec2(80, 80));
			////get frame buffer
			//ImGui::End(); //end frame buffer



			//DISPLAYING TILES
			if (ImGui::Begin("Tile Selector"))
			{
				//start tile selector
				int my_image_width = 0;
				int my_image_height = 0;
				GLuint my_image_texture = 0;

				//ImGui::BeginTabBar("Hi");

				bool ret = LoadTextureFromFile("../textures/Tiles/Ingredients/Ingredients0_cucumber.png", &my_image_texture, &my_image_width, &my_image_height);
				IM_ASSERT(ret);
				if (ImGui::ImageButton((void*)(intptr_t)my_image_texture, ImVec2(80, 80)))
				{
					std::cout << "button for cucumber is pressed" << std::endl;
					texpath = "../textures/Tiles/Ingredients/Ingredients0_cucumber.png";
				}
				ImGui::SameLine();

				//salmon
				ret = LoadTextureFromFile("../textures/Tiles/Ingredients/Ingredients0_salmon.png", &my_image_texture, &my_image_width, &my_image_height);
				IM_ASSERT(ret);
				if (ImGui::ImageButton((void*)(intptr_t)my_image_texture, ImVec2(80, 80)))
				{
					texpath = "../textures/Tiles/Ingredients/Ingredients0_salmon.png";
				}

				ImGui::SameLine();
				ret = LoadTextureFromFile("../textures/Tiles/Ingredients/Ingredients0_avocado.png", &my_image_texture, &my_image_width, &my_image_height);
				IM_ASSERT(ret);
				if (ImGui::ImageButton((void*)(intptr_t)my_image_texture, ImVec2(80, 80)))
				{
					texpath = "../textures/Tiles/Ingredients/Ingredients0_avocado.png";
				}


				ret = LoadTextureFromFile("../textures/Tiles/Ingredients/Soya_Ingredient.png", &my_image_texture, &my_image_width, &my_image_height);
				IM_ASSERT(ret);
				if (ImGui::ImageButton((void*)(intptr_t)my_image_texture, ImVec2(80, 80)))
				{
					texpath = "../textures/Tiles/Ingredients/Soya_Ingredient.png";
				}

				ImGui::SameLine();
				ret = LoadTextureFromFile("../textures/Tiles/Ingredients/Ingredients1_nori.png", &my_image_texture, &my_image_width, &my_image_height);
				IM_ASSERT(ret);
				if (ImGui::ImageButton((void*)(intptr_t)my_image_texture, ImVec2(80, 80)))
				{
					texpath = "../textures/Tiles/Ingredients/Ingredients1_nori.png";
				}

				ImGui::SameLine();
				ret = LoadTextureFromFile("../textures/Tiles/Ingredients/Ingredients0_tuna.png", &my_image_texture, &my_image_width, &my_image_height);
				IM_ASSERT(ret);
				if (ImGui::ImageButton((void*)(intptr_t)my_image_texture, ImVec2(80, 80)))
				{
					texpath = "../textures/Tiles/Ingredients/Ingredients0_tuna.png";
				}


				ret = LoadTextureFromFile("../textures/Tiles/Ingredients/Wasabi_Ingredient.png", &my_image_texture, &my_image_width, &my_image_height);
				IM_ASSERT(ret);
				if (ImGui::ImageButton((void*)(intptr_t)my_image_texture, ImVec2(80, 80)))
				{
					texpath = "../textures/Tiles/Ingredients/Wasabi_Ingredient.png";
				}
				ImGui::SameLine();
				ret = LoadTextureFromFile("../textures/Tiles/Ingredients/Ingredients0_ew_corn.png", &my_image_texture, &my_image_width, &my_image_height);
				IM_ASSERT(ret);
				if (ImGui::ImageButton((void*)(intptr_t)my_image_texture, ImVec2(80, 80)))
				{
					texpath = "../textures/Tiles/Ingredients/Ingredients0_ew_corn.png";
				}
				ImGui::SameLine();
				ret = LoadTextureFromFile("../textures/Tiles/Ingredients/Ingredients0_roes.png", &my_image_texture, &my_image_width, &my_image_height);
				IM_ASSERT(ret);
				if (ImGui::ImageButton((void*)(intptr_t)my_image_texture, ImVec2(80, 80)))
				{
					texpath = "../textures/Tiles/Ingredients/Ingredients0_roes.png";
				}

				ret = LoadTextureFromFile("../textures/Tiles/Ingredients/Ingredients0_rice.png", &my_image_texture, &my_image_width, &my_image_height);
				IM_ASSERT(ret);
				if (ImGui::ImageButton((void*)(intptr_t)my_image_texture, ImVec2(80, 80)))
				{
					texpath = "../textures/Tiles/Ingredients/Ingredients0_rice.png";
				}
				ImGui::SameLine();
				ret = LoadTextureFromFile("../textures/Tiles/Ingredients/Ingredients0_inari.png", &my_image_texture, &my_image_width, &my_image_height);
				IM_ASSERT(ret);
				if (ImGui::ImageButton((void*)(intptr_t)my_image_texture, ImVec2(80, 80)))
				{
					texpath = "../textures/Tiles/Ingredients/Ingredients0_inari.png";
				}
				ImGui::SameLine();
				ret = LoadTextureFromFile("../textures/Tiles/Ingredients/Ingredients0_tofu.png", &my_image_texture, &my_image_width, &my_image_height);
				IM_ASSERT(ret);
				if (ImGui::ImageButton((void*)(intptr_t)my_image_texture, ImVec2(80, 80)))
				{
					texpath = "../textures/Tiles/Ingredients/Ingredients0_tofu.png";
				}
				//ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.f, 0.f, 0.f, 0.f)); //uncomment if u want to make button bg transparent
				//ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.f, 0.f, 0.f, 0.f));
				//ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.f, 0.f, 0.f, 0.f));


				////salmon
				//int my_image_width2 = 0;
				//int my_image_height2 = 0;
				//GLuint my_image_texture2 = 0;
				//bool ret2 = LoadTextureFromFile("../textures/Tiles/Ingredients/Ingredients0_salmon.png", &my_image_texture2, &my_image_width2, &my_image_height2);
				//IM_ASSERT(ret2);
				//if (ImGui::ImageButton((void*)(intptr_t)my_image_texture2, ImVec2(80, 80)))
				//{
				//	texpath = "../textures/Tiles/Ingredients/Ingredients0_salmon.png";
				//}

				//ImGui::PopStyleColor(3); //free the custom transparency buttons
			}
			ImGui::End(); //end tile selector


			/*bool b = false;
			if (ImGui::BeginMainMenuBar())
			{
				if (ImGui::BeginMenu("menu"))
				{
					if (ImGui::MenuItem("menu item"))
					{
						b = true;
					}
					if (ImGui::MenuItem("menu item 2"))
					{
						b = true;
					}
					ImGui::EndMenu();

				}
				ImGui::EndMainMenuBar();
			}

			if (b)
			{
				ImGui::OpenPopup("popup");
			}

			if (ImGui::BeginPopupModal("popup"))
			{
				ImGui::Text("Load Level - Select JSON file");
				if (ImGui::Button("OK"))
				{
					ImGui::CloseCurrentPopup();
				}
				ImGui::EndPopup();
			}*/

			//ImGui::ShowDemoWindow();
			//ImGui::ShowDebugLogWindow();


			/*if (drawTexture)
			{
				glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			}*/

			ImGui::Begin("Object Editor - Imgui Window");

			//ImGui::Text("%s", * JSONSerializer::LevelLoadPathPtr);

			ImGui::Text("Select a file below to load a saved level!");
			ImGui::BulletText("JSON files are in ../Data");


			/******************************
				DESERIALIZE - LOAD A LEVEL
			******************************/
			//OPEN FILES
			if (ImGui::Begin("Object Editor - Imgui Window"))
			{
				// open file dialog when user clicks this button
				if (ImGui::Button("Click here to Load level!"))
				{
					fileDialog.Open();
					loadnewlevel = true;
				}

			}
			ImGui::End();
			fileDialog.Display(); //only need to call once in entire file

			if (fileDialog.HasSelected() && loadnewlevel == true)
			{
				std::cout << "You are now loading a level!" << std::endl;

				//std::cout << "Selected Load file before conversion " << fileDialog.GetSelected().string() << std::endl;
				path2 = fileDialog.GetSelected().string();
				std::replace(path2.begin(), path2.end(), '\\', '/');
				*Core::LevelLoadPathPtr = path2.c_str();
				//std::cout << "Selected Load file AFTER conversion" << *JSONSerializer::LevelLoadPathPtr << std::endl;

				delete Window::player; //delete old player? but it feels so inappropriate to put it here if i need to delete all objects in future to replace them
				Window::player = Core::Deserialize(*Core::LevelLoadPathPtr);

				std::cout << "the level is loaded, JSON file is " << *Core::LevelLoadPathPtr << std::endl;

				fileDialog.ClearSelected();
				loadnewlevel = false;


			}
			/*----------------------*/
			/*Content Browser Panel*/
			/*----------------------*/
			ImGui::Begin("Content Browser");

			if(m_curr_path != std::filesystem::path(s_TextureDirectory))
			{
				if(ImGui::Button("<-"))
				{
					m_curr_path = m_curr_path.parent_path();
				}
			}
			float padding = 10.f;
			float thumbnail_size = 128;
			float cellSize = thumbnail_size + padding;

			float panelWidth = ImGui::GetContentRegionAvail().x;
			float columnCount = (int)(panelWidth / cellSize);
			ImGui::Columns(5, 0, false);

			for( auto& directory_entry : std::filesystem::directory_iterator(m_curr_path))
			{
				std::string path = directory_entry.path().string();
				auto relative_path = std::filesystem::relative(directory_entry.path(),s_TextureDirectory);

				ImGui::Button(path.c_str(), { thumbnail_size, thumbnail_size });
				ImGui::Text(path.c_str());

				if (directory_entry.is_directory())
				{
					/*
					if (ImGui::Button(path.c_str()))
					{
						m_curr_path /= directory_entry.path().filename();
					}
					*/
				}
				else
				{
					/*
					if(ImGui::Button(path.c_str()))
					{
						
					}
					*/
				}
				ImGui::NextColumn();
				
			}
			ImGui::Columns(1);
			ImGui::SliderFloat("Thumbnail Size", &thumbnail_size, 16, 512);
			ImGui::SliderFloat("Padding", &padding, 0, 32);
			ImGui::End();


			/*currently not working oops*/
			//ImGui::Text("Click to Create New Object/Modify Object");

			//ImGui::Text("The selected object is: ");
			////ImGui::Checkbox("Display Texture", &mainclass::drawTexture);
			//// Slider that appears in the window
			//ImGui::SliderFloat("Size", &mainclass::size, 0.5f, 2.0f);
			//// Fancy color editor that appears in the window
			//ImGui::ColorEdit4("Color", mainclass::color);


			//ImGui::Text(objectString[i]);
			//ImGui::SliderInt("Object Index", &i, 0, objectString.size()-1);
			//ImGui::SliderFloat("x-position", &Object::objects[objectString[i]].position.x, -500.0f, 500.0f);
			//ImGui::SliderFloat("y-position", &Object::objects[objectString[i]].position.y, -500.0f, 500.0f);


			//float *arr[3] = { &Object::objects["temp"].color.r, &Object::objects["temp"].color.g, &Object::objects["temp"].color.b/*, Object::objects["Object5"].color.a*/ };

			//RGB colour selection
			//ImGui::ColorEdit3("Color", *arr);


			ImGui::Spacing();
			ImGui::Text("Buttons to test textures load in editor");

			/*ImGui::ImageButton("gfx/image.png", 64, 64, 8, 0xffffff, 1, 0xff0000, 0.5);*/

			if (ImGui::Button("Cucumber"))
			{
				texpath = "../textures/Tiles/Ingredients/Ingredients0_cucumber.png";
			}

			//ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.f, 0.f, 0.f, 0.f));
			//ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.f, 0.f, 0.f, 0.f));
			//ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.f, 0.f, 0.f, 0.f));
			////ImTextureID("../textures/Tiles/Ingredients/Ingredients0_octopus.png");
			//if (ImGui::ImageButton(ImTextureID("../textures/Tiles/Ingredients/Ingredients0_octopus.png"), ImVec2((float)300, (float)50), ImVec2(0.0f, 0.0f), ImVec2(1.0f, 1.0f), 1, ImVec4(0.0f, 0.0f, 0.0f, 0.0f), ImVec4(1.0f, 1.0f, 1.0f, 1.0f))) {
			//	Beep(400, 300);
			//	
			//}
			//ImGui::PopStyleColor(3);

			if (ImGui::Button("Salmon"))
			{
				texpath = "../textures/Tiles/Ingredients/Ingredients0_salmon.png";
				
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

			if (ImGui::Button("+"))
			{
				/*Window::ImGuiToObjContainer()*/
			}

			ImGui::Spacing();
			ImGui::Text("File Save Functions:");
			/******************************
				SERIALIZE - SAVE A LEVEL
			******************************/
			if (ImGui::Begin("Object Editor - Imgui Window"))
			{
				// save objects positions into json
				if (ImGui::Button("Click here to Save Level"))
				{
					levelsave = 1;
					//std::cout << "the level is saved, level save status is " << levelsave << std::endl;
				}
				if (levelsave >= 1)
				{
					ImGui::Text("Choose file to save level :D ");
					ImGui::Spacing();
					ImGui::BulletText("take note that you can only save to \nexisting JSON level files!");
					ImGui::BulletText("If you want to save to new levels, \nyou will need to manually create a new JSON");
					if (ImGui::Button("Select JSON filepath in ../Data"))
					{
						fileDialog.Open();
					}
					//fileDialog.Display(); //already called once upstairs
					//change the Serialised JSON file path to store new level
					if (fileDialog.HasSelected())
					{
						//std::cout << "Selected filename" << fileDialog.GetSelected().string() << std::endl;
						path2 = fileDialog.GetSelected().string();
						std::replace(path2.begin(), path2.end(), '\\', '/');
						*Core::LevelSavePathPtr = path2.c_str();
						//std::cout << "Selected filename" << *JSONSerializer::LevelSavePathPtr << std::endl;
						levelsave = 2;

						Core::Serialize(*Window::player, *Core::LevelSavePathPtr);

						std::cout << "the level is saved! level save status is " << levelsave << std::endl;

						fileDialog.ClearSelected();
					}

				}
				//create popup to tell user that level is saved
				if (levelsave == 2)
				{
					ImGui::Button("Level saved! Please exit window ^^"); //currently a button as popup gives problems
					//ImGui::CloseCurrentPopup();

					//ImGui::EndPopup();
				}

			}
			ImGui::End(); //end level save window

			ImGui::End(); //end the whole imgui process
#endif
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		}

		void LevelEditor::imguiShutDown(void)
		{
			ImGui_ImplOpenGL3_Shutdown();
			ImGui_ImplGlfw_Shutdown();
			ImGui::DestroyContext();
#if defined(EDITOR) | defined(_EDITOR)

#endif
		}

		/*void LevelEditor::imguiCreateObj(ObjectFactory& container)*/

		void LevelEditor::imguiCreateObj()
		{
#if defined(EDITOR) | defined(_EDITOR)

			double xpos = 0, ypos = 0;

			//grid snapping logic
			glfwGetCursorPos(Window::window_ptr, &xpos, &ypos);
			
			std::cout << "X: " << xpos << " " << ypos << std::endl;
			int i = imguiPlacedObjs;

			//newobjarr[i].spritevector = new Sprite(texpath); replace with pushing back a struct
			/*Window::a = new Sprite(texpath);*/
			xpos = (float)((int)(xpos) / 100 * 100);
			ypos = (float)((int)(ypos) / 100 * 100);

			/**************************
			* Step 1: set ur spritepath
			* 1a) set scale,
			* 1b) set pos
			* Step 2: set ur name given to object
			* Step 3: save your pos into x and y so that Object Container can read it
			* Step 4: push back the whole struct
			****************************************************/
			addedobjinfo a;
			a.spritepath = new Sprite(texpath); //1
			a.spritepath->transformation.Position = glm::vec2(xpos, ypos); //1a
			a.spritepath->transformation.Scale = glm::vec2(100, 100); //1b
			a.objname = "path"; //2
			a.x = xpos;
			a.y = ypos; //3
			newobjarr.push_back(a); //push back the whole struct
			//std::cout << "X: " << xpos << " Y:" << ypos << std::endl; //debug
			//newobjarr[i].spritepath->transformation.position = glm::vec2(xpos, ypos);
			//if (texpath = "../textures/Tiles/Ingredients/Ingredients0_salmon.png")
			//{
			//	newobjarr[i].objname = "salmon";//you placed a salmon!
			//}
			//else
			//	newobjarr[i].objname = "unknown";
			std::cout << "name of object you just created: " << newobjarr[i].objname << std::endl;

			
			++imguiPlacedObjs;
#endif
		}

		void LevelEditor::imguiDestroyObj()
		{
#if defined(EDITOR) | defined(_EDITOR)

			for (int i = 0; i < imguiPlacedObjs; ++i)
			{
				delete newobjarr[i].spritepath;
			}
#endif
		}

		void LevelEditor::AddToFactory(ObjectFactory* container)
		{
			Object::GameObject* EditorObj = container->Create();
			container->AddObjects(EditorObj, "Editor Obj");
			//container
			
			//this function is called when the "+" button to add new objects is called.
		}

		void LevelEditor::imguiObjectCursor(void)
		{
#if defined(EDITOR) | defined(_EDITOR)

			//display obj to place on cursor
			double xpos = 0, ypos = 0;

			//grid snapping logic
			glfwGetCursorPos(Window::window_ptr, &xpos, &ypos);
			//xpos += 100 * 0.5f;
			//ypos += 100 * 0.5f;
			xpos = (float)((int)(xpos) / 100 * 100);
			ypos = (float)((int)(ypos) / 100 * 100);

			//Window::ingredient->transformation.Position = glm::vec2(xpos, ypos);
			//place object on click

			if (ImGui::IsMouseClicked(0)) //0 means left
			{
				//std::cout << "placing NEW obj at x: " << Window::ingredient->transformation.Position.x << " and y: " << Window::ingredient->transformation.Position.y << std::endl;
				
				imguiCreateObj();

			}
#endif
			
		}
	}
}
>>>>>>> M3-submission-branch
