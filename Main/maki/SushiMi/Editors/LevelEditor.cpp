/*!*****************************************************************************

\file       LevelEditor.cpp
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
//#include "../../stb-master/stb_image.h"

#include "LevelEditor.h"
#include "imfilebrowser.h"
#include "../Engine/Shaders/ShaderLibrary.h"
#include "../testshader.h"
#include "../src/Window.h"
#include "../Engine/TileMap/Map.h"
#include "../Engine/Serialiser/JSONSerializer.h"
#include "../Engine/Factory/Factory.h"
#include "../Headers/SceneManager.h"
#include <sstream>


//#include "../Engine/Core/Core.h"
namespace Core
{
	int value = 'Q';

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
	static const std::filesystem::path s_TextureDirectory = "../TileMap";

	namespace Editor
	{
		void LevelEditor::imguiEditorInit(void)
		{
#if defined(EDITOR) | defined(_EDITOR)
			// Setup Dear ImGui context
			IMGUI_CHECKVERSION();
			ImGui::CreateContext();
			ImGuiIO& io = ImGui::GetIO(); (void)io;
			io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
			//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
			io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
			io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
			//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
			//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;

			float fontSize = 18.0f;// *2.0f;
			/*io.Fonts->AddFontFromFileTTF("assets/fonts/opensans/OpenSans-Bold.ttf", fontSize);
			io.FontDefault = io.Fonts->AddFontFromFileTTF("assets/fonts/opensans/OpenSans-Regular.ttf", fontSize);*/

			// Setup Dear ImGui style
			ImGui::StyleColorsDark();
			//ImGui::StyleColorsClassic();

			// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
			ImGuiStyle& style = ImGui::GetStyle();
			if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
			{
				style.WindowRounding = 0.0f;
				style.Colors[ImGuiCol_WindowBg].w = 1.0f;
			}

			//SetDarkThemeColors();

			GLFWwindow* window = static_cast<GLFWwindow*>(Window::window_ptr);
			//GLFWwindow* windowtest = glfwCreateWindow(400, 200, "TEST", NULL, NULL);/* = static_cast<GLFWwindow*>(Window::window_ptr)*/;

			// Setup Platform/Renderer bindings
			ImGui_ImplGlfw_InitForOpenGL(window, true);
			ImGui_ImplOpenGL3_Init("#version 450");


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
			alphabet = "click on a grid to see its object value";

		}

		void LevelEditor::imguiGraphicsTest(void)
		{
#if defined(EDITOR) | defined(_EDITOR)

			/*if (m_BlockEvents)
			{*/
			//}

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
#if defined(EDITOR) | defined(_EDITOR)
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();
			//make the whole screen dockable
			ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);
			//ImGui::GetMainViewport();

			fileDialog.SetTypeFilters({ ".txt"});
			fileDialog.SetPwd("../TileMap"); //current working directory is TileMap

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



			//***************************************DISPLAYING TILES*************************************
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
			ImGui::End(); 
			//******************************************end tile selector****************************


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
			ImGui::Begin("Main Dockspace");

			//Central Dockspace
			static ImGuiID dockspaceID = 0;
			dockspaceID = ImGui::GetID("Main Dockspace");
			ImGui::DockSpace(dockspaceID, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_None | ImGuiDockNodeFlags_PassthruCentralNode/*|ImGuiDockNodeFlags_NoResize*/);

			//ImGui::Text("%s", * JSONSerializer::LevelLoadPathPtr);
			ImGui::Begin("Object Editor - Imgui Window");
			//int value = Map::GetValue(xgrid, ygrid);
			
			ImGui::SliderInt("Value to set to tile", &value, '!', '~');
			/*if (ImGui::Button("Set Value"))
			{
				Map::SetValue(xgrid, ygrid, value);
			}*/


			ImGui::Text("Select a file below to load a saved level!");
			ImGui::BulletText("level text files are in ../TileMap");


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
				imguiloadedmap = path2.c_str();
				//std::cout << "Selected Load file AFTER conversion" << *JSONSerializer::LevelLoadPathPtr << std::endl;

			
				
				//delete Window::player; //delete old player? but it feels so inappropriate to put it here if i need to delete all objects in future to replace them
				//Window::player = Core::Deserialize(*Core::LevelLoadPathPtr);
				Window::loaded = false;

				std::cout << "You have loaded Level from text file: " << imguiloadedmap << std::endl;

				fileDialog.ClearSelected();
				loadnewlevel = false; 
				Window::timetodeletegrid = true;


			}
			/*----------------------*/
			/*Content Browser Panel*/
			/*----------------------*/
			ImGui::Begin("Content Browser");

			if(m_curr_path != std::filesystem::path(s_TextureDirectory))
			{
				if(ImGui::Button("<-")) //will only show if u went into a folder in the current directory above
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
					//std::cout << "the directory im clicking is: " << directory_entry.is_directory() << std::endl;
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
			ImGui::Text("Currently displaying: ");
			ImGui::Text(imguiloadedmap.c_str());

			ImGui::Spacing();
			ImGui::Text("Click on a cell to see its value");

			ImGui::Spacing();
			ImGui::Text("Grid row: ");
			ImGui::SameLine();
			std::stringstream xstring;
			xstring << xgrid;
			ImGui::Text(xstring.str().c_str());

			ImGui::Text("Grid col: ");
			ImGui::SameLine();
			std::stringstream ystring;
			ystring << ygrid;
			ImGui::Text(ystring.str().c_str());

			ImGui::Text("Tile Value in clicked grid: ");
			ImGui::SameLine();
			ImGui::Text(alphabet.c_str());

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
					ImGui::BulletText("take note that you can only save to \nexisting level txt files!");
					ImGui::BulletText("If you want to save to new levels, \nyou will need to manually create a new txt file");
					if (ImGui::Button("filepath containing levels is '../TileMap' "))
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

						Map::saveEditedMap(*Core::LevelSavePathPtr);
						/*Core::Serialize(*Window::player, *Core::LevelSavePathPtr);*/

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
			ImGui::End(); //end Main Docking window

			ImGui::End(); //end the whole imgui process
			ImGuiIO& io = ImGui::GetIO();
			int width, height;

			glfwGetWindowSize(Window::window_ptr, &width, &height);

			io.DisplaySize = ImVec2((float)width, (float)height);

			// Rendering
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
			{
				GLFWwindow* backup_current_context = glfwGetCurrentContext();
				ImGui::UpdatePlatformWindows();
				ImGui::RenderPlatformWindowsDefault();
				glfwMakeContextCurrent(backup_current_context);
			}
#endif
		}

		void LevelEditor::imguiShutDown(void)
		{
#if defined(EDITOR) | defined(_EDITOR)
			ImGui_ImplOpenGL3_Shutdown();
			ImGui_ImplGlfw_Shutdown();
			ImGui::DestroyContext();

#endif
		}

		/*void LevelEditor::imguiCreateObj(ObjectFactory& container)*/

		void LevelEditor::imguiCreateObj()
		{
#if defined(EDITOR) | defined(_EDITOR)

			double xpos = 0, ypos = 0;
			double gridxpos = 0, gridypos = 0;

			int width_, height_ = 0;
			//grid snapping logic
			glfwGetCursorPos(Window::window_ptr, &xpos, &ypos);
			glfwGetWindowSize(Window::window_ptr, &width_, &height_);

			/*std::cout << "You are clicking at grid position X: " << (int)(xpos/ width_*18) << " Y: " << (int)(ypos/height_*10) << std::endl;
			std::cout << "the object in the grid is: " << static_cast<char>(Map::GetValue((int)(xpos / width_ * 18), (int)(ypos / height_ * 10))) << std::endl;
			alphabet = static_cast<char>(Map::GetValue((int)(xpos / width_ * 18), (int)(ypos / height_ * 10)));
			xgrid = (int)(xpos / width_ * 18);
			ygrid = (int)(ypos / height_ * 10);*/


			int i = imguiPlacedObjs;

			//newobjarr[i].spritevector = new Sprite(texpath); replace with pushing back a struct

			if (SceneManager::getTileWidth() != 0 || SceneManager::getTileHeight() != 0)
			{
				gridxpos = ((int)(xpos) / SceneManager::getTileWidth());
				gridypos = ((int)(ypos) / SceneManager::getTileHeight());

				//r / static_cast<float>(grid_row) * width

				xpos = gridxpos / static_cast<float>(Map::grid_row) * width_;
				ypos = gridypos / static_cast<float>(Map::grid_col) * height_;
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
				a.spritepath->transformation.Scale = glm::vec2(SceneManager::getTileWidth()*1.01f, SceneManager::getTileHeight()*1.01f);//1b
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
			}
			/*Window::a = new Sprite(texpath);*/
			/*xpos = (float)((int)(xpos) / 100 * 100);
			ypos = (float)((int)(ypos) / 100 * 100);*/


			
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


		/**************************
		VALUES FOR EACH TEXTURE
		*************************/

		//case static_cast<int>(grid_number::player):
		//{
		//	texpath = "../textures/Bami"
		//	break;
		//}
		//case static_cast<int>(grid_number::avocado):
		//{
		//	Sprite* avocado = new Sprite("../textures/Tiles/Ingredients/Ingredients0_avocado.png");
		//	std::pair<grid_number, Sprite*> combine = std::make_pair(grid_number::avocado, avocado);

		//	SceneManager::loadIngr(grid_to_coord_x, grid_to_coord_y, r, c, combine);
		//	SceneManager::loadIngr_initPos(grid_to_coord_x, grid_to_coord_y, r, c, combine);
		//	break;
		//}
		//case static_cast<int>(grid_number::cucumber):
		//{
		//	Sprite* cucumber = new Sprite("../textures/Tiles/Ingredients/Ingredients0_cucumber.png");
		//	std::pair<grid_number, Sprite*> combine = std::make_pair(grid_number::cucumber, cucumber);

		//	SceneManager::loadIngr(grid_to_coord_x, grid_to_coord_y, r, c, combine);
		//	SceneManager::loadIngr_initPos(grid_to_coord_x, grid_to_coord_y, r, c, combine);
		//	break;
		//}
		//case static_cast<int>(grid_number::corn):
		//{
		//	Sprite* corn = new Sprite("../textures/Tiles/Ingredients/Ingredients0_ew_corn.png");
		//	std::pair<grid_number, Sprite*> combine = std::make_pair(grid_number::corn, corn);

		//	SceneManager::loadIngr(grid_to_coord_x, grid_to_coord_y, r, c, combine);
		//	SceneManager::loadIngr_initPos(grid_to_coord_x, grid_to_coord_y, r, c, combine);
		//	break;
		//}

		//case static_cast<int>(grid_number::inari):
		//{
		//	Sprite* inari = new Sprite("../textures/Tiles/Ingredients/Ingredients0_inari.png");
		//	std::pair<grid_number, Sprite*> combine = std::make_pair(grid_number::inari, inari);

		//	SceneManager::loadIngr(grid_to_coord_x, grid_to_coord_y, r, c, combine);
		//	SceneManager::loadIngr_initPos(grid_to_coord_x, grid_to_coord_y, r, c, combine);
		//	break;
		//}
		//case static_cast<int>(grid_number::octopus):
		//{
		//	Sprite* octopus = new Sprite("../textures/Tiles/Ingredients/Ingredients0_octopus.png");
		//	std::pair<grid_number, Sprite*> combine = std::make_pair(grid_number::octopus, octopus);

		//	SceneManager::loadIngr(grid_to_coord_x, grid_to_coord_y, r, c, combine);
		//	SceneManager::loadIngr_initPos(grid_to_coord_x, grid_to_coord_y, r, c, combine);
		//	break;
		//}
		//case static_cast<int>(grid_number::rice):
		//{
		//	/*Soya if you want to test out the animation
		//	Sprite* rice = new Sprite("../textures/spritesheet/soyaspritesheet.png");
		//	std::pair<grid_number, Sprite*> combine = std::make_pair(grid_number::rice, std::move(rice));
		//	rice->Add_animation("../textures/spritesheet/soya.txt");
		//	rice->curr_anim = Idle;
		//	*/

		//	rice = new Sprite("../textures/Tiles/Ingredients/Ingredients0_rice.png");
		//	std::pair<grid_number, Sprite*> combine = std::make_pair(grid_number::rice, rice);

		//	

		//	//old rice
		//	/*Sprite* rice = new Sprite("../textures/spritesheet/ricespritesheet.png");
		//	std::pair<grid_number, Sprite*> combine = std::make_pair(grid_number::rice, std::move(rice));
		//	rice->Add_animation("../textures/spritesheet/Run.txt");
		//	rice->curr_anim = Idle;
		//	rice->isSpriteSheet = 1;
		//	SceneManager::loadIngr(r / static_cast<float>(grid_row) * width, c / static_cast<float>(grid_col) * height, r, c, combine);
		//	SceneManager::loadIngr_initPos(r / static_cast<float>(grid_row) * width, c / static_cast<float>(grid_col) * height, r, c, combine);*/
		//	break;
		//}
		////roes
		//case static_cast<int>(grid_number::roes):
		//{
		//	Sprite* roes = new Sprite("../textures/Tiles/Ingredients/Ingredients0_roes.png");
		//	std::pair<grid_number, Sprite*> combine = std::make_pair(grid_number::roes, roes);

		//	SceneManager::loadIngr(grid_to_coord_x, grid_to_coord_y, r, c, combine);
		//	SceneManager::loadIngr_initPos(grid_to_coord_x, grid_to_coord_y, r, c, combine);
		//	break;
		//}
		////salmon
		//case static_cast<int>(grid_number::salmon):
		//{
		//	Sprite* salmon = new Sprite("../textures/Tiles/Ingredients/Ingredients0_salmon.png");
		//	std::pair<grid_number, Sprite*> combine = std::make_pair(grid_number::salmon, salmon);

		//	SceneManager::loadIngr(grid_to_coord_x, grid_to_coord_y, r, c, combine);
		//	SceneManager::loadIngr_initPos(grid_to_coord_x, grid_to_coord_y, r, c, combine);
		//	break;
		//}
		////tamago
		//case static_cast<int>(grid_number::tamago):
		//{
		//	Sprite* tamago = new Sprite("../textures/Tiles/Ingredients/Ingredients0_tamago.png");
		//	std::pair<grid_number, Sprite*> combine = std::make_pair(grid_number::tamago, tamago);

		//	SceneManager::loadIngr(grid_to_coord_x, grid_to_coord_y, r, c, combine);
		//	SceneManager::loadIngr_initPos(grid_to_coord_x, grid_to_coord_y, r, c, combine);
		//	break;
		//}
		////tofu
		//case static_cast<int>(grid_number::tofu):
		//{
		//	Sprite* tofu = new Sprite("../textures/Tiles/Ingredients/Ingredients0_tofu.png");
		//	std::pair<grid_number, Sprite*> combine = std::make_pair(grid_number::tofu, tofu);

		//	SceneManager::loadIngr(grid_to_coord_x, grid_to_coord_y, r, c, combine);
		//	SceneManager::loadIngr_initPos(grid_to_coord_x, grid_to_coord_y, r, c, combine);
		//	break;
		//}
		////tuna
		//case static_cast<int>(grid_number::tuna):
		//{
		//	Sprite* tuna = new Sprite("../textures/Tiles/Ingredients/Ingredients0_tuna.png");
		//	std::pair<grid_number, Sprite*> combine = std::make_pair(grid_number::tuna, tuna);

		//	SceneManager::loadIngr(grid_to_coord_x, grid_to_coord_y, r, c, combine);
		//	SceneManager::loadIngr_initPos(grid_to_coord_x, grid_to_coord_y, r, c, combine);
		//	break;
		//}
		////nori
		//case static_cast<int>(grid_number::nori):
		//{
		//	Sprite* nori = new Sprite("../textures/Tiles/Ingredients/Ingredients1_nori.png");
		//	std::pair<grid_number, Sprite*> combine = std::make_pair(grid_number::nori, std::move(nori));

		//	SceneManager::loadIngr(grid_to_coord_x, grid_to_coord_y, r, c, combine);
		//	SceneManager::loadIngr_initPos(grid_to_coord_x, grid_to_coord_y, r, c, combine);
		//	break;
		//}
		////soya
		//case static_cast<int>(grid_number::soya):
		//{

		//	soya = new Sprite("../textures/spritesheet/soyaspritesheet.png");
		//	soya->isSpriteSheet = 1;
		//	std::pair<grid_number, Sprite*> combine = std::make_pair(grid_number::soya, soya);
		//	//animate soy sauce
		//	soya->Add_animation("../textures/spritesheet/soya_Idle.txt");
		//	soya->Add_animation("../textures/spritesheet/soya_Pour.txt");
		//	soya->curr_anim = AnimationType::Idle;
		//	SceneManager::loadIngr(grid_to_coord_x, grid_to_coord_y, r, c, combine);
		//	SceneManager::loadIngr_initPos(grid_to_coord_x, grid_to_coord_y, r, c, combine);

		//	break;
		//}
		////wasabi
		//case static_cast<int>(grid_number::wasabi):
		//{
		//	Sprite* wasabi = new Sprite("../textures/Tiles/Ingredients/Wasabi_1.png");
		//	std::pair<grid_number, Sprite*> combine = std::make_pair(grid_number::wasabi, wasabi);

		//	SceneManager::loadIngr(grid_to_coord_x, grid_to_coord_y, r, c, combine);
		//	SceneManager::loadIngr_initPos(grid_to_coord_x, grid_to_coord_y, r, c, combine);
		//	break;
		//}
		//// Ingredients that have boxes are: avocado, cucumber,corn,inari,octopus,rice,roes,salmon,tamago,tofu,tuna,nori	
		//case static_cast<int>(wall_type::avocado_box):
		//{
		//	Sprite* box = new Sprite("../textures/Tiles/Pods/Pod_Avocado.png");
		//	std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::avocado_box, box);

		//	SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

		//	levelWinConditions.push_back(std::pair(grid_number::avocado, wall_type::avocado_box));

		//	SceneManager::win_condition.push_back(std::make_pair(r, c));
		//	SceneManager::amt_of_win_conditions++;
		//	break;
		//}
		////cucumber
		//case static_cast<int>(wall_type::cucumber_box):
		//{
		//	Sprite* box = new Sprite("../textures/Tiles/Pods/Pod_Cucumber.png");
		//	std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::cucumber_box, box);

		//	SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);


		//	levelWinConditions.push_back(std::pair(grid_number::cucumber, wall_type::cucumber_box));

		//	SceneManager::win_condition.push_back(std::make_pair(r, c));
		//	SceneManager::amt_of_win_conditions++;
		//	break;
		//}
		////corn
		//case static_cast<int>(wall_type::corn_box):
		//{
		//	Sprite* box = new Sprite("../textures/Tiles/Pods/Pod_Corn.png");
		//	std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::corn_box, box);

		//	SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);


		//	levelWinConditions.push_back(std::pair(grid_number::corn, wall_type::corn_box));

		//	SceneManager::win_condition.push_back(std::make_pair(r, c));
		//	SceneManager::amt_of_win_conditions++;
		//	break;
		//}
		////octopus
		//case static_cast<int>(wall_type::octopus_box):
		//{
		//	Sprite* box = new Sprite("../textures/Tiles/Pods/Pod_Octopus.png");
		//	std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::octopus_box, box);

		//	SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);


		//	levelWinConditions.push_back(std::pair(grid_number::octopus, wall_type::octopus_box));

		//	SceneManager::win_condition.push_back(std::make_pair(r, c));
		//	SceneManager::amt_of_win_conditions++;
		//	break;
		//}
		////roes
		//case static_cast<int>(wall_type::roes_box):
		//{
		//	Sprite* box = new Sprite("../textures/Tiles/Pods/Pod_Roes.png");
		//	std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::roes_box, box);

		//	SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);


		//	levelWinConditions.push_back(std::pair(grid_number::roes, wall_type::roes_box));

		//	SceneManager::win_condition.push_back(std::make_pair(r, c));
		//	SceneManager::amt_of_win_conditions++;
		//	break;
		//}
		////salmon
		//case static_cast<int>(wall_type::salmon_box):
		//{
		//	Sprite* box = new Sprite("../textures/Tiles/Pods/Pod_Salmon.png");
		//	std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::salmon_box, box);

		//	SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);


		//	levelWinConditions.push_back(std::pair(grid_number::salmon, wall_type::salmon_box));

		//	SceneManager::win_condition.push_back(std::make_pair(r, c));
		//	SceneManager::amt_of_win_conditions++;
		//	break;
		//}
		////tamago
		//case static_cast<int>(wall_type::tamago_box):
		//{
		//	Sprite* box = new Sprite("../textures/Tiles/Pods/Pod_Tamago.png");
		//	std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::tamago_box, box);

		//	SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);


		//	levelWinConditions.push_back(std::pair(grid_number::tamago, wall_type::tamago_box));

		//	SceneManager::win_condition.push_back(std::make_pair(r, c));
		//	SceneManager::amt_of_win_conditions++;
		//	break;
		//}
		////tofu
		//case static_cast<int>(wall_type::tofu_box):
		//{
		//	Sprite* box = new Sprite("../textures/Tiles/Pods/Pod_Tofu.png");
		//	std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::tofu_box, box);

		//	SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);


		//	levelWinConditions.push_back(std::pair(grid_number::tofu, wall_type::tofu_box));

		//	SceneManager::win_condition.push_back(std::make_pair(r, c));
		//	SceneManager::amt_of_win_conditions++;
		//	break;
		//}
		////tuna
		//case static_cast<int>(wall_type::tuna_box):
		//{
		//	Sprite* box = new Sprite("../textures/Tiles/Pods/Pod_Tuna.png");
		//	std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::tuna_box, box);

		//	SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);


		//	levelWinConditions.push_back(std::pair(grid_number::tuna, wall_type::tuna_box));

		//	SceneManager::win_condition.push_back(std::make_pair(r, c));
		//	SceneManager::amt_of_win_conditions++;
		//	break;
		//}
		////nori
		//case static_cast<int>(wall_type::nori_box):
		//{
		//	Sprite* box = new Sprite("../textures/Tiles/Pods/Pod_Nori.png");
		//	std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::nori_box, box);

		//	SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);


		//	levelWinConditions.push_back(std::pair(grid_number::nori, wall_type::nori_box));

		//	SceneManager::win_condition.push_back(std::make_pair(r, c));
		//	SceneManager::amt_of_win_conditions++;
		//	break;
		//}

		//case static_cast<int>(wall_type::rice_box):
		//{
		//	Sprite* box = new Sprite("../textures/Tiles/Pods/Pod_Rice.png");
		//	std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::rice_box, box);

		//	SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);


		//	levelWinConditions.push_back(std::pair(grid_number::rice, wall_type::rice_box));

		//	SceneManager::win_condition.push_back(std::make_pair(r, c));
		//	SceneManager::amt_of_win_conditions++;
		//	break;

		//}


		//case static_cast<int>(wall_type::inari_box):
		//{
		//	Sprite* box = new Sprite("../textures/Tiles/Pods/Pod_Inari.png");
		//	std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::inari_box, box);

		//	SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);


		//	levelWinConditions.push_back(std::pair(grid_number::inari, wall_type::inari_box));

		//	SceneManager::win_condition.push_back(std::make_pair(r, c));
		//	SceneManager::amt_of_win_conditions++;
		//	break;
		//}

		//case static_cast<int>(grid_number::boxcover):
		//{
		//	Sprite* boxcover = new Sprite("../textures/Tiles/Pods/Pod_Cover.png");
		//	std::pair<grid_number, Sprite*> combine = std::make_pair(grid_number::boxcover, boxcover);

		//	SceneManager::loadIngr(grid_to_coord_x, grid_to_coord_y, r, c, combine);

		//	break;
		//}

		//case static_cast<int>(wall_type::sinkhole):
		//{
		//	Sprite* sinkhole = new Sprite("../textures/Tiles/Trap/Sinkhole0_1.png");
		//	std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::sinkhole, sinkhole);

		//	SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);


		//	break;
		//}

		//case static_cast<int>(wall_type::filledsinkhole):
		//{
		//	Sprite* filledsinkhole = new Sprite("../textures/Tiles/Trap/Sinkhole_Filled.png");
		//	std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::filledsinkhole, filledsinkhole);

		//	SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);


		//	break;
		//}

		////Temporary placeholder for food in sinkhole
		//case static_cast<int>(wall_type::temp):
		//{
		//	Sprite* foodinsinkhole = new Sprite("../textures/doge.png");
		//	std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::temp, foodinsinkhole);

		//	SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);


		//	break;
		//}
		//case static_cast<int>(grid_number::ground0):
		//{
		//	Sprite* tile = new Sprite("../textures/Tiles/Ground/RicePlain_Ground0_0.jpg");

		//	std::pair<grid_number, Sprite*> combine = std::make_pair(grid_number::ground0, tile);

		//	SceneManager::loadIngr(grid_to_coord_x, grid_to_coord_y, r, c, combine);

		//	break;
		//}
		//case static_cast<int>(grid_number::ground1):
		//{
		//	Sprite* tile = new Sprite("../textures/Tiles/Ground/RicePlain_Ground0_1.jpg");

		//	std::pair<grid_number, Sprite*> combine = std::make_pair(grid_number::ground1, tile);

		//	SceneManager::loadIngr(grid_to_coord_x, grid_to_coord_y, r, c, combine);

		//	break;
		//}
		//case static_cast<int>(grid_number::ground2):
		//{
		//	Sprite* tile = new Sprite("../textures/Tiles/Ground/RicePlain_Ground0_2.jpg");

		//	std::pair<grid_number, Sprite*> combine = std::make_pair(grid_number::ground2, tile);

		//	SceneManager::loadIngr(grid_to_coord_x, grid_to_coord_y, r, c, combine);

		//	break;
		//}
		////sinkhole_gunkan
		//case static_cast<int>(wall_type::sinkhole_gunkan):
		//{
		//	Sprite* tile = new Sprite("../textures/Tiles/Ground_GunkanVillage/Sinkhole.png");

		//	std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::sinkhole_gunkan, tile);

		//	SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);


		//	break;
		//}
		//case static_cast<int>(wall_type::Wall0):
		//{
		//	Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall0.jpg");
		//	std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall0, tile);

		//	SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

		//	break;
		//}
		//case static_cast<int>(wall_type::Wall0_1):
		//{
		//	Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall0_1.jpg");
		//	std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall0_1, tile);

		//	SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

		//	break;
		//}
		//case static_cast<int>(wall_type::Wall1):
		//{
		//	Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall1.png");
		//	std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall1, tile);

		//	SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

		//	break;
		//}
		//case static_cast<int>(wall_type::Wall2):
		//{
		//	Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall2.jpg");
		//	std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall2, tile);

		//	SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

		//	break;
		//}



		//case static_cast<int>(wall_type::Wall2_1):
		//{
		//	Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall2_1.jpg");
		//	std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall2_1, tile);

		//	SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

		//	break;
		//}


		//case static_cast<int>(wall_type::Wall2_2):
		//{
		//	Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall2_2.jpg");
		//	std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall2_2, tile);

		//	SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

		//	break;
		//}
		//case static_cast<int>(wall_type::Wall2_3):
		//{
		//	Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall2_3.png");
		//	std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall2_3, tile);

		//	SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

		//	break;
		//}

		//case static_cast<int>(wall_type::Wall3):
		//{
		//	Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall3.jpg");
		//	std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall3, tile);

		//	SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

		//	break;
		//}

		//case static_cast<int>(wall_type::Wall3_1):
		//{
		//	Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall3_1.png");
		//	std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall3_1, tile);
		//	//tile->Add_animation()
		//	SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

		//	break;
		//}

		//case static_cast<int>(wall_type::Wall3_2):
		//{
		//	Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall3_2.jpg");
		//	std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall3_2, tile);
		//	//tile->Add_animation()
		//	SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

		//	break;
		//}


		//case static_cast<int>(wall_type::Wall3_3):
		//{
		//	Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall3_3.png");
		//	std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall3_3, tile);

		//	SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

		//	break;
		//}

		//case static_cast<int>(wall_type::Wall4):
		//{
		//	Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall4.png");
		//	std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall4, tile);

		//	SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

		//	break;
		//}

		//case static_cast<int>(wall_type::Wall4_1):
		//{
		//	Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall4_1.jpg");
		//	std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall4_1, tile);

		//	SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

		//	break;
		//}
		//case static_cast<int>(wall_type::Wall4_2):
		//{
		//	Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall4_2.jpg");
		//	std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall4_2, tile);

		//	SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

		//	break;
		//}
		//case static_cast<int>(wall_type::Wall4_3):
		//{
		//	Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall4_3.jpg");
		//	std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall4_3, tile);

		//	SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

		//	break;
		//}
		//case static_cast<int>(wall_type::Wall4_4):
		//{
		//	Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall4_4.jpg");
		//	std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall4_4, tile);

		//	SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

		//	break;
		//}



		//case static_cast<int>(wall_type::Wall5):
		//{
		//	Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall5.jpg");
		//	std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall5, tile);

		//	SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

		//	break;
		//}


		////most common wall
		//case static_cast<int>(wall_type::Wall5_1):
		//{
		//	Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall5_1.jpg");
		//	std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall5_1, tile);

		//	SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

		//	break;

		//}

		//case static_cast<int>(wall_type::Wall5_2):
		//{
		//	Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall5_2.jpg");
		//	std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall5_2, tile);

		//	SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

		//	break;

		//}

		//case static_cast<int>(wall_type::Wall5_3):
		//{
		//	Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall5_3.jpg");
		//	std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall5_3, tile);

		//	SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

		//	break;

		//}

		//case static_cast<int>(wall_type::Wall5_4):
		//{
		//	Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall5_4.jpg");
		//	std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall5_4, tile);

		//	SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

		//	break;

		//}
		//case static_cast<int>(wall_type::Wall6):
		//{
		//	Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall6.png");
		//	std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall6, tile);

		//	SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

		//	break;
		//}
		//case static_cast<int>(wall_type::Wall6_1):
		//{
		//	Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall6_1.jpg");
		//	std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall6_1, tile);

		//	SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

		//	break;

		//}

		//case static_cast<int>(wall_type::Wall6_2):
		//{
		//	Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall6_2.jpg");
		//	std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall6_2, tile);

		//	SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

		//	break;

		//}

		//case static_cast<int>(wall_type::Wall6_3):
		//{
		//	Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall6_3.jpg");
		//	std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall6_3, tile);

		//	SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

		//	break;

		//}

		//case static_cast<int>(wall_type::Wall6_4):
		//{
		//	Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall6_4.jpg");
		//	std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall6_4, tile);

		//	SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

		//	break;

		//}
		////wall 7
		//case static_cast<int>(wall_type::Wall7):
		//{
		//	Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall7.png");
		//	std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall7, tile);

		//	SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

		//	break;
		//}
		//case static_cast<int>(wall_type::Wall7_1):
		//{
		//	Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall7_1.jpg");
		//	std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall7_1, tile);

		//	SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

		//	break;

		//}

		//case static_cast<int>(wall_type::Wall7_2):
		//{
		//	Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall7_2.jpg");
		//	std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall7_2, tile);

		//	SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

		//	break;

		//}

		//case static_cast<int>(wall_type::Wall7_3):
		//{
		//	Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall7_3.jpg");
		//	std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall7_3, tile);

		//	SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

		//	break;

		//}

		//case static_cast<int>(wall_type::Wall7_4):
		//{
		//	Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall7_4.jpg");
		//	std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall7_4, tile);

		//	SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

		//	break;

		//}
		////wall 8
		//case static_cast<int>(wall_type::Wall8):
		//{
		//	Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall8.png");
		//	std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall8, tile);

		//	SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

		//	break;
		//}
		////wall 9
		//case static_cast<int>(wall_type::Wall9):
		//{
		//	Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall9.png");
		//	std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall9, tile);

		//	SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

		//	break;
		//}
		//case static_cast<int>(wall_type::Wall9_1):
		//{
		//	Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall9_1.jpg");
		//	std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall9_1, tile);

		//	SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

		//	break;
		//}
		//case static_cast<int>(wall_type::Wall9_2):
		//{
		//	Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall9_2.jpg");
		//	std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall9_2, tile);

		//	SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

		//	break;
		//}
		//case static_cast<int>(wall_type::Wall9_3):
		//{
		//	Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall9_3.jpg");
		//	std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall9_3, tile);

		//	SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

		//	break;
		//}
		//case static_cast<int>(wall_type::Wall9_4):
		//{
		//	Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall9_4.jpg");
		//	std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall9_4, tile);

		//	SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

		//	break;
		//}
		//case static_cast<int>(wall_type::Wall9_5):
		//{
		//	Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall9_5.jpg");
		//	std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall9_5, tile);

		//	SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

		//	break;
		//}
		//case static_cast<int>(wall_type::Wall9_6):
		//{
		//	Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall9_6.jpg");
		//	std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall9_6, tile);

		//	SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

		//	break;
		//}
		//case static_cast<int>(wall_type::Wall9_7):
		//{
		//	Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall9_7.jpg");
		//	std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall9_7, tile);

		//	SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

		//	break;
		//}
		//case static_cast<int>(wall_type::WaterWall):
		//{
		//	Sprite* tile = new Sprite("../textures/Tiles/Wall_FishingVillage/Fishing_Wall.png");
		//	std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::WaterWall, tile);

		//	SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

		//	break;
		//}
		////	Wall0_Gunkan,		//j
		//case static_cast<int>(wall_type::Wall0_Gunkan):
		//{
		//	Sprite* tile = new Sprite("../textures/Tiles/Wall_GunkanVillage/Wall0.png");
		//	std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall0_Gunkan, tile);

		//	SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

		//	break;
		//}
		////	Wall1_Gunkan,		//k
		//case static_cast<int>(wall_type::Wall1_Gunkan):
		//{
		//	Sprite* tile = new Sprite("../textures/Tiles/Wall_GunkanVillage/Wall1.png");
		//	std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall1_Gunkan, tile);

		//	SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

		//	break;
		//}
		////	Wall1_1_Gunkan,		//l
		//case static_cast<int>(wall_type::Wall1_1_Gunkan):
		//{
		//	Sprite* tile = new Sprite("../textures/Tiles/Wall_GunkanVillage/Wall1_1.png");
		//	std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall1_1_Gunkan, tile);

		//	SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

		//	break;
		//}
		////	Wall2_Gunkan,		//m
		//case static_cast<int>(wall_type::Wall2_Gunkan):
		//{
		//	Sprite* tile = new Sprite("../textures/Tiles/Wall_GunkanVillage/Wall2.png");
		//	std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall2_Gunkan, tile);

		//	SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

		//	break;
		//}
		////	Wall2_1_Gunkan,		//n
		//case static_cast<int>(wall_type::Wall2_1_Gunkan):
		//{
		//	Sprite* tile = new Sprite("../textures/Tiles/Wall_GunkanVillage/Wall2_1.png");
		//	std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall2_1_Gunkan, tile);

		//	SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

		//	break;
		//}
		////	Wall3_Gunkan,		//o
		//case static_cast<int>(wall_type::Wall3_Gunkan):
		//{
		//	Sprite* tile = new Sprite("../textures/Tiles/Wall_GunkanVillage/Wall3.png");
		//	std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall3_Gunkan, tile);

		//	SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

		//	break;
		//}
		////	Wall3_1_Gunkan,		//p
		//case static_cast<int>(wall_type::Wall3_1_Gunkan):
		//{
		//	Sprite* tile = new Sprite("../textures/Tiles/Wall_GunkanVillage/Wall3_1.png");
		//	std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall3_1_Gunkan, tile);

		//	SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

		//	break;
		//}

		///*case static_cast<int>(wall_type::Water):
		//{
		//	Sprite* tile = new Sprite("../textures/Tiles/Wall_FishingVillage/Fishing_Wall.png");
		//	std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Water, tile);

		//	SceneManager::loadTile(r / static_cast<float>(grid_row) * width, c / static_cast<float>(grid_col) * height, combine);
		//	break;
		//}*/
		////	Wall3_1_Gunkan,		//p
		//case static_cast<int>(wall_type::WoodenPlatform):
		//{
		//	Sprite* tile = new Sprite("../textures/Tiles/Ground_FishingVillage/Fishing_Ground.png");
		//	std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::WoodenPlatform, tile);

		//	SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

		//	break;
		//}

		void LevelEditor::imguiObjectCursor(void)
		{
#if defined(EDITOR) | defined(_EDITOR)

			ImGuiIO& io = ImGui::GetIO(); (void)io;
			if (io.WantCaptureMouseUnlessPopupClose == false)
			{

				Window::ingredient = new Sprite(Editor::LevelEditor::texpath);

				//display obj to place on cursor
				int width_ = 0, height_ = 0;
				double xpos = 0, ypos = 0;
				double gridxpos = 0, gridypos = 0;

				//grid snapping logic
				glfwGetCursorPos(Window::window_ptr, &xpos, &ypos);
				glfwGetWindowSize(Window::window_ptr, &width_, &height_);
				//xpos += 100 * 0.5f;
				//ypos += 100 * 0.5f;
				//xpos = col number
				//static_cast<float>(grid_row) * width
				//xpos = (int)(xpos / SceneManager::getTileWidth()) /** (double)SceneManager::getTileWidth()*/;
				//ypos = ((int)(ypos / (double)SceneManager::getTileHeight())) * (double)SceneManager::getTileHeight();
				/*xpos = (int) (float)((int)(xpos / width_ / 18) * (width_ / 18));
				ypos = (int)(float)((int)(ypos / height_ / 10) * (height_ / 10));*/
				Window::ingredient->transformation.Scale = glm::vec2(SceneManager::getTileWidth()*1.01f, SceneManager::getTileHeight()*1.01f);
				/*SceneManager::rows*/
				if (SceneManager::getTileWidth() != 0 || SceneManager::getTileHeight() != 0)
				{
					gridxpos = ((int)(xpos) / SceneManager::getTileWidth());
					gridypos = ((int)(ypos) / SceneManager::getTileHeight());

					//r / static_cast<float>(grid_row) * width
				
					Window::ingredient->transformation.Position.x =  gridxpos / static_cast<float>(Map::grid_row) * width_ ;
					Window::ingredient->transformation.Position.y = gridypos / static_cast<float>(Map::grid_col) * height_;
				}
					/*= glm::vec2(xpos, ypos)*/
				//place object on click
				//std::cout << "Grid width: " << SceneManager::getTileWidth() << " and height: " << SceneManager::getTileHeight() << std::endl;
				//std::cout << "Grid pos x: " << gridxpos << " and y: " << gridypos << std::endl;

				if (ImGui::IsMouseClicked(0)) //0 means left
				{
					std::cout << "placing NEW obj at x: " << Window::ingredient->transformation.Position.x << " and y: " << Window::ingredient->transformation.Position.y << std::endl;
				
					imguiCreateObj();
					Map::SetValue(gridxpos, gridypos, value);
					Map::print_map_to_console;

				}
				Shaders->Textured_Shader()->Send_Mat4("model_matrx", Window::ingredient->transformation.Get());
				Window::ingredient->draw();

				if (Window::ingredient)
				{
					delete Window::ingredient;
				}
			}
		
#endif
			
		}
	}
}