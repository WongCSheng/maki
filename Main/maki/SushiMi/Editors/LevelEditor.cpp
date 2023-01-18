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
//#include "../../stb-master/stb_image.h"

#include "LevelEditor.h"
#include "imfilebrowser.h"
#include "../Engine/Shaders/ShaderLibrary.h"
#include "../testshader.h"
#include "../src/Window.h"
#include "../Engine/Serialiser/JSONSerializer.h"
#include "../Engine/Factory/Factory.h"
//#include "../Engine/Core/Core.h"

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

namespace Core
{
	

	//std::vector<std::string> ObjVector;
	//std::vector<const char*> objectString;
	int i = 0;
	//unsigned int VBO, VAO;
	//unsigned int EBO;
	// create a file browser instance
	static ImGui::FileBrowser fileDialog;


	namespace Editor
	{
		void LevelEditor::imguiEditorInit(void)
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
			static ImGui::FileBrowser fileDialog;
			


			// (optional) set browser properties
			fileDialog.SetTitle("ImGui File Explorer");
			//fileDialog.SetPwd("../maki/textures/");
			//fileDialog.SetCurrentTypeFilterIndex(0);

		}

		void LevelEditor::imguiGraphicsTest(void)
		{
			if (fileDialog.HasSelected())
			{
				std::cout << "Selected filename" << fileDialog.GetSelected().string() << std::endl;
				path = fileDialog.GetSelected().string();
				std::replace(path.begin(), path.end(), '\\', '/');
				texpath = path.c_str();

				fileDialog.ClearSelected();
			}
		}

		void LevelEditor::imguiEditorDraw(void)
		{
			fileDialog.SetTypeFilters({ ".png", ".jpg", ".json" });


			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

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
				*JSONSerializer::LevelLoadPathPtr = path2.c_str();
				//std::cout << "Selected Load file AFTER conversion" << *JSONSerializer::LevelLoadPathPtr << std::endl;

				delete Window::player; //delete old player? but it feels so inappropriate to put it here if i need to delete all objects in future to replace them
				Window::player = JSONSerializer::Deserialize(*JSONSerializer::LevelLoadPathPtr);

				std::cout << "the level is loaded, JSON file is " << *JSONSerializer::LevelLoadPathPtr << std::endl;

				fileDialog.ClearSelected();
				loadnewlevel = false;


			}

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
						*JSONSerializer::LevelSavePathPtr = path2.c_str();
						//std::cout << "Selected filename" << *JSONSerializer::LevelSavePathPtr << std::endl;
						levelsave = 2;

						JSONSerializer::Serialize(*Window::player, *JSONSerializer::LevelSavePathPtr);

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
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		}

		void LevelEditor::imguiShutDown(void)
		{
			ImGui_ImplOpenGL3_Shutdown();
			ImGui_ImplGlfw_Shutdown();
			ImGui::DestroyContext();
		}

		/*void LevelEditor::imguiCreateObj(ObjectFactory& container)*/

		void LevelEditor::imguiCreateObj()
		{
			double xpos = 0, ypos = 0;

			//grid snapping logic
			glfwGetCursorPos(Window::window_ptr, &xpos, &ypos);
			
			std::cout << "X: " << xpos << " " << ypos << std::endl;
			int i = imguiPlacedObjs;
			newobjarr.push_back(new Sprite(texpath));
			/*Window::a = new Sprite(texpath);*/
			newobjarr[i]->transformation.scale = glm::vec2(100, 100);
			xpos += newobjarr[i]->transformation.scale.x * 0.5f;
			ypos += newobjarr[i]->transformation.scale.y * 0.5f;
			xpos = (float)((int)(xpos) / 100 * 100);
			ypos = (float)((int)(ypos) / 100 * 100);
			newobjarr[i]->transformation.position = glm::vec2(xpos, ypos);

			
			++imguiPlacedObjs;
			
		}

		void LevelEditor::imguiDestroyObj()
		{
			for (int i = 0; i < imguiPlacedObjs; ++i)
			{
				delete newobjarr[i];
			}
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
			
			//display obj to place on cursor
			double xpos = 0, ypos = 0;

			//grid snapping logic
			glfwGetCursorPos(Window::window_ptr, &xpos, &ypos);
			xpos += 100 * 0.5f;
			ypos += 100 * 0.5f;
			xpos = (float)((int)(xpos) / 100 * 100);
			ypos = (float)((int)(ypos) / 100 * 100);

			Window::ingredient->transformation.position = glm::vec2(xpos, ypos);
			//place object on click
			if (ImGui::IsMouseClicked(0)) //0 means left
			{
				std::cout << "placing NEW obj at x: " << Window::ingredient->transformation.position.x << " and y: " << Window::ingredient->transformation.position.y << std::endl;
				
				imguiCreateObj();

			}
			
		}
	}
}