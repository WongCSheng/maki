/*!*****************************************************************************

\file       imguiEditor.cpp
\author     Thea Sea. thea.sea, 2102348
\par        DP email: thea.sea@digipen.edu
\par        Course: CSD2400/GAM200
\date       7-10-2022

\brief
This program implements a Game Engine Editor using ImGui

Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

*******************************************************************************/

#include "..\include\imguiEditor.h"
std::vector<std::string> ObjVector;
std::vector<const char*> objectString;
int i = 0;

void imguiEditorInit(void)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(GLHelper::ptr_window, true);
	ImGui_ImplOpenGL3_Init("#version 450");
	
	/*for (int i = 1; i < Scene::ObjVector.size(); i += 14)
	{
		std::string s(Scene::ObjVector[i]);
		const char* s2 = s.c_str();
		Scene::objectString.push_back(s2);

	}*/

	
	/*for (int i = 0; i < Scene::objectString.size(); ++i)
	{
		std::cout << Scene::objectString[i] << std::endl;

	}*/
	//std::cout << "Hi" << std::endl;
	for (int i = 1; i < 57*14; i += 14)
	{
		//std::cout << Scene::ObjVector[i] << std::endl;
		const char* s2 = Scene::ObjVector[i].c_str();
		//std::cout << s2 << std::endl;
		objectString.push_back(s2);
	}
	/*for (int i = 0 ; i < objectString.size(); ++i)
	{

	std::cout << objectString[0] << std::endl;
	}*/

}

void imguiEditorDraw(void)
{
	//bool drawTriangle = true;
	
	//Object Index

	//drawTriangle = true;
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	ImGui::ShowDemoWindow();
	ImGui::ShowDebugLogWindow();
	

	//if (drawTriangle)
		/*glDrawArrays(GL_TRIANGLES, 0, 3);*/

	ImGui::Begin("Object Editor - Imgui Window");
	ImGui::Text("Click to Select Object");
	
	
	
	//ImGui::Text(objectString);
	//ImGui::Checkbox("Sample Checkbox", nullptr);
	//Object::objects["Object5"].shd_ref;
	//ImGui::SliderFloat("Size", (float*)Object::objects["Object5"].scale_up, 0.5f, 2.0f);
	//ImGui::SliderFloat("Object Index", &i, 0, objectString.size());
	ImGui::SliderInt("Object Index", &i, 0, objectString.size());
	ImGui::SliderFloat("x-position", &Object::objects[objectString[i]].position.x, -500.0f, 500.0f);
	ImGui::SliderFloat("y-position", &Object::objects[objectString[i]].position.y, -500.0f, 500.0f);

	//rgb slider test
	/*ImGui::SliderFloat("R in RGB", &Object::objects["Object5"].color.r, .0f, 1.0f);
	ImGui::SliderFloat("G in RGB", &Object::objects["Object5"].color.g, .0f, 1.0f);
	ImGui::SliderFloat("B in RGB", &Object::objects["Object5"].color.b, .0f, 1.0f);*/

	//ImGui::SliderFloat("transparency", &Object::objects["Object5"].color.a, .0f, 1.0f);
	//ImGui::SliderFloat("transparency", &Object::objects["Object5"].color., -500.0f, 500.0f);
	//array to store RGBA values

	float *arr[3] = { &Object::objects["temp"].color.r, &Object::objects["temp"].color.g, &Object::objects["temp"].color.b/*, Object::objects["Object5"].color.a*/ };

	//RGB colour selection
	ImGui::ColorEdit3("Color", *arr);

	ImGui::End();

	/*glUniform1f(glGetUniformLocation(Object::objects["Object5"]., "size"), size);*/

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}


