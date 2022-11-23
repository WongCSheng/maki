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


#include "LevelEditor.h"
#include "imfilebrowser.h"
//std::vector<std::string> ObjVector;
//std::vector<const char*> objectString;
int i = 0;
// create a file browser instance
static ImGui::FileBrowser fileDialog;
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
	

	// (optional) set browser properties
	fileDialog.SetTitle("title");
	fileDialog.SetTypeFilters({ ".h", ".cpp" });
}

void Editor::LevelEditor::imguiEditorDraw(void)
{
	
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	ImGui::ShowDemoWindow();
	ImGui::ShowDebugLogWindow();
	
	ImGui::Begin("Object Editor - Imgui Window");
	ImGui::Text("Click to Select Object");
	

	ImGui::Text("The selected object is: ");
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
		if (ImGui::Button("open file dialog"))
			fileDialog.Open();
	}
	ImGui::End();

	fileDialog.Display();

	if (fileDialog.HasSelected())
	{
		std::cout << "Selected filename" << fileDialog.GetSelected().string() << std::endl;
		fileDialog.ClearSelected();
	}

	ImGui::End();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
