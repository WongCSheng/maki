/*!*****************************************************************************

\file       LevelEditor.h
\author     Thea Sea. thea.sea, 2102348
\par        DP email: thea.sea@digipen.edu
\par        Course: CSD2400/GAM200
\date       7-10-2022

\brief
This program is a header file for GameEditor.cpp that implements a Game Engine Editor using ImGui

Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

*******************************************************************************/
#pragma once

#include "../Headers/STL_Header.h"
#include "../Headers/ImGui_Header.h"
#include "../../glew/include/GL/glew.h"
#include "../Engine/System/Graphics/glhelper.h"

namespace Core
{
	class mainclass
	{
	public:
		static void imguiEditorInit(void);
		static void imguiGraphicsTest(void);
		static void imguiEditorDraw(void);
		static void imguiShutDown(void);
		static inline int loadnewlevel = 0;
		static inline int levelsave = 0;
		static inline std::string path, path2;
		static void imguiObjectCursor(void);
		static inline const char* texpath = "../textures/Tiles/Ingredients/Ingredients0_rice.png";

	private:

		inline static bool drawTexture = true;
		inline static float size = 1.0f;
		inline static float color[4] = { 0.8f, 0.3f, 0.02f, 1.0f };
		//inline static GLuint VAO, VBO;
		inline static int width, height, nrChannels;

	};
	namespace Editor
	{
		class LevelEditor
		{
		public:
			static void imguiEditorInit(void);
			static void imguiGraphicsTest(void);
			static void imguiEditorDraw(void);
			static void imguiShutDown(void);
		private:

		};
	}
}