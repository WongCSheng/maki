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