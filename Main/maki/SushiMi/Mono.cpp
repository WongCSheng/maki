/*!
@file		Mono.cpp
@author		fei.x@digipen.edu
@date		20/11/2022

			This file contains mono scripting.....

*//*__________________________________________________________________________*/


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