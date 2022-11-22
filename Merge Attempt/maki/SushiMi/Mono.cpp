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
	//create mono domain
	m_ptrMonoDomain = mono_jit_init("maki");
	if (m_ptrMonoDomain)
	{
		return;
	}

}

SushiMi::~SushiMi()
{

}

void SushiMi::keyEvent(char key)
{

}

bool SushiMi::tick()
{
	return false;
}