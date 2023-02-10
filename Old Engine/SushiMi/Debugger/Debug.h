/*
File: Debug.h
Author: 
Description: Header for Debug.cpp.
*/

#ifndef DEBUGGER_H
#define DEBUGGER_H

#include "../Headers/STL_Header.h"

class Debugger
{
public:
	static inline Debugger& Instance()
	{
		if (instance != 0)
		{
			return *instance;
		}
		instance = new Debugger();
		return *instance;
	}

	void Log(std::string log);

private:
	Debugger();
	~Debugger();

	static Debugger* instance;
};

#endif