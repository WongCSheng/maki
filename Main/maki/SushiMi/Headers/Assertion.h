#pragma once
/******************************************************************************/
/*!
\file		Assertion.h
\author 	Aurelia Chong
\par    	email: fei.x@digipen.edu
\date   	16 Nov 2022
\brief		This header file contains the engine's assert functions

Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
*/
/******************************************************************************/
#ifndef Assertion_H
#define Assertion_H

#include "Log.h"

#define ASSERTION_ENABLED //turn assertions on/off by commenting this line

#ifdef ASSERTION_ENABLED
#if _MSC_VER
#include <intrin.h>
#define debugBreak() __debugbreak()
#else
#define debugBreak() __builtin_trap()
#endif

	/******************************************************************************/
	/*!
	\brief
	Output information to user in a readable format

	\param expression
	The string represenation of the code that was running that cause the failure assert

	\param message
	The message to be formatted

	\param file
	Name of the code file

	\param line
	The line number within the file

	\return
	void
	*/
	/******************************************************************************/
#ifdef __cplusplus
	extern "C" {
#endif
		void ReportAssertionFailure(const char* expression, const char* message, const char* file, int line);
#ifdef __cplusplus
	}
#endif //end of __cplusplus

	/*
	For ASSERTING : USE CAUTIOUSLY! This will cause immediate Breaking of the debugger/ app
	If you are very sure that the value here should never be a certain value, or a certain pointer should never point to a NULLPTR, use ASSERT functions below accordingly.

	ASSERT(expr) :
	expr is the expression you are comparing , similar to doing eg: if (file.is_open()), Assert will only run if the expr returns a FALSE/ 0 / NULLPTR!
	This will cause a Debug Mode break, closing the debugger, and showing you the location of where the break happens. This will also be logged into a log file for users to check
	Format of print:
	(expr)	\n
	"msg"	\n	// not for this function
	_FILE	\n	// the file in which the assert happen
	_LINE	\n	// the line in the file in which the assert happen

	In release build, the assert will exit the app, assertion should be logged to log file

	ASSERT_MSG(expr, msg):
	expr is the expression you are comparing, msg is the message you input to show during assertion
	This will cause a Debug Mode break, closing the debugger, and showing you the location of where the break happens. This will also be logged into a log file for users to check
	Format of print:
	(expr)	\n
	"msg"	\n	// the message you wrote to be printed out during assertion
	_FILE	\n	// the file in which the assert happen
	_LINE	\n	// the line in the file in which the assert happen

	In release build, the assert will exit the app, assertion should be logged to log file

	ASSERT_DEBUG(expr):
	expr is the expression you are comparing , this is a debug mode exclusive function, does not work in release mode
	This causes a Debug Mode break, closing the debugger, and showing you the location of where the break happens. This will also be logged into a log file for users to check
	Format of print:
	(expr)	\n
	"msg"	\n	// not for this function
	_FILE	\n	// the file in which the assert happen
	_LINE	\n	// the line in the file in which the assert happen

	*/

#ifdef _DEBUG	
#define ASSERT(expr)														\
	{																		\
		if (expr) {															\
		}																	\
		else {																\
			ReportAssertionFailure(#expr, "", __FILE__, __LINE__);			\
			debugBreak();													\
			}																\
	}

#define ASSERT_MSG(expr, message)											\
	{																		\
		if (expr) {															\
		}																	\
		else {																\
			ReportAssertionFailure(#expr, #message, __FILE__, __LINE__);	\
			debugBreak();													\
		}																	\
	}																


#define ASSERT_DEBUG(expr)												\
	{																		\
		if (expr) {															\
		}																	\
		else {																\
			ReportAssertionFailure(#expr, "", __FILE__, __LINE__);			\
			debugBreak();													\
		}																	\
	}																
#else
#define ASSERT(expr)														\
	{																		\
		if (expr) {															\
		}																	\
		else {																\
			ReportAssertionFailure(#expr, "", __FILE__, __LINE__);			\
			exit(1);														\
			}																\
	}

#define ASSERT_MSG(expr, message)											\
	{																		\
		if (expr) {															\
		}																	\
		else {																\
			ReportAssertionFailure(#expr, #message, __FILE__, __LINE__);	\
			exit(1);														\
		}																	\
	}

#define ASSERT_DEBUG(expr)		//exclusive to only debugmode									
#endif

#else 
#define ASSERT(expr)				//does nothing at all
#define ASSERT_MSG(expr, message)	//does nothing at all
#define ASSERT_DEBUG(expr)		//does nothing at all
#endif

#endif