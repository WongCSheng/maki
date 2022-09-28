/*!
@file		Debug.h
@author		p.tzechengjennifer@digipen.edu
@date		28/09/2022

This file currently contains framework for debugging that we will include later.
*//*__________________________________________________________________________*/

#pragma once
#include "../include/common_headers.hpp"
#ifndef DEBUGGER_H
#define DEBUGGER_H

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