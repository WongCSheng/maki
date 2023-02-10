/******************************************************************************/
/*!
\file		Mono.cpp
\author 	Aurelia Chong
\par    	email: fei.x@digipen.edu
\date   	21 Nov 2022
\brief		This file contains basic mono scripting enviroment set-up
Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
*/
/******************************************************************************/


#include "Mono.h"

//mono_set_dirs(".\\lib")

SushiMi::SushiMi()
{
	//set current dir as mono dir
	mono_set_dirs(".", ".");
	//create mono domain
	m_ptrMonoDomain = mono_jit_init("maki");
	if (m_ptrMonoDomain)
	{
		//load a mono assembly.dll

	}

}

SushiMi::~SushiMi()
{	//release the domain
	if (m_ptrMonoDomain)
	{
		mono_jit_cleanup(m_ptrMonoDomain);
	}

}

void SushiMi::keyEvent(char key)
{

}

bool SushiMi::tick()
{
	return false;
}