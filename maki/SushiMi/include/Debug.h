/*!
@file		Debug.h
@author		p.tzechengjennifer@digipen.edu
@date		28/09/2022

This file currently contains framework for debugging that we will include later.
*//*__________________________________________________________________________*/

#pragma once
#ifndef DEBUGGER_H
#define DEBUGGER_H

class Debugger
{
public:
	//return a debugger obj when we call Instance()
	static inline Debugger& Instance() 
	{
		if (instance)
			return *instance;
		instance = new Debugger();
		return *instance;
	}

	//output debugging msg to console
	void Log(std::string log);

private:
	Debugger();
	~Debugger();

	static Debugger* instance;
};

#endif