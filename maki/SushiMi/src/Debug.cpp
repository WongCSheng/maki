/*!
@file		Debug.cpp
@author		p.tzechengjennifer@digipen.edu
@date		28/09/2022

This file currently contains framework for debugging that we will include later.
*//*__________________________________________________________________________*/

#pragma once
#include "../include/common_headers.hpp"

Debugger* Debugger::instance = 0;

Debugger::Debugger()
{
}


Debugger::~Debugger()
{
}

void Debugger::Log(std::string log)
{
	std::cout << log << std::endl;
}
