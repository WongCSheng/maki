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
#include "../Engine/System/Graphics/glapp.h"

namespace Editor
{
	class LevelEditor
	{
	public:
		static void imguiEditorInit(void);
		static void imguiEditorDraw(void);

	private:

	};
}