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
