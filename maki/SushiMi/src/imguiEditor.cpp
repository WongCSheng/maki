/*!*****************************************************************************

\file       GameEditor.cpp
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


void imguiEditorInit(void)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(GLHelper::ptr_window, true);
	ImGui_ImplOpenGL3_Init("#version 450");

	

}

void imguiEditorDraw(void)
{
	//bool drawTriangle = true;

	//drawTriangle = true;
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	//if (drawTriangle)
		/*glDrawArrays(GL_TRIANGLES, 0, 3);*/

	ImGui::Begin("I am the ImGui Window!");
	ImGui::Text("Hi - Thea");
	//ImGui::Checkbox("Sample Checkbox", nullptr);
	//Object::objects["Object5"].shd_ref;
	//ImGui::SliderFloat("Size", (float*)Object::objects["Object5"].scale_up, 0.5f, 2.0f);
	ImGui::SliderFloat("x-position", &Object::objects["Object5"].position.x, -500.0f, 500.0f);
	ImGui::SliderFloat("y-position", &Object::objects["Object5"].position.y, -500.0f, 500.0f);
	ImGui::SliderFloat("R in RGB", &Object::objects["Object5"].color.r, .0f, 1.0f);
	ImGui::SliderFloat("G in RGB", &Object::objects["Object5"].color.g, .0f, 1.0f);
	ImGui::SliderFloat("B in RGB", &Object::objects["Object5"].color.b, .0f, 1.0f);
	//ImGui::SliderFloat("transparency", &Object::objects["Object5"].color., -500.0f, 500.0f);
	

	ImGui::End();

	/*glUniform1f(glGetUniformLocation(Object::objects["Object5"]., "size"), size);*/

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}


