#pragma once
/******************************************************************************/
/*!
\file		Mono.h
\author 	Aurelia Chong
\par    	email: fei.x@digipen.edu
\date   	21 Nov 2022
\brief		This is header file for Mono.cpp

Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
*/
/******************************************************************************/
#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/debug-helpers.h>

class SushiMi
{
	public:
		SushiMi();
		~SushiMi();

		//interface
		void keyEvent(char key);
		bool tick();

	private:
		MonoDomain* m_ptrMonoDomain = nullptr;
		MonoAssembly* m_ptrGameAssembly = nullptr;
		MonoImage* m_ptrGameAssemblyImage = nullptr;
};