/*
File: Debug.cpp
Author: 
Description: Enables collision boxes, force vectors and different rendering patterns to be shown and manipulated.
			Also shows consoles for troubleshooting. Allows users to have a clearer picture of what is happening.
*/

#include "Debug.h"

Debugger* Debugger::instance = 0;
Debugger::Debugger()
{	
}


Debugger::~Debugger()
{
	if (instance)
		delete instance;
}

void Debugger::Log(std::string log)
{
	std::cout << log << std::endl;
}
