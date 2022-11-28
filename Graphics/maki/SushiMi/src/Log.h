#pragma once
#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <ctime>
//using namespace std;
// Log.h entries
// ----------------------------------------------- //

// To switch/control logging during debug mode 
#if defined(_DEBUG) == 1
#define LOG_WARN_ENABLED 1
#define LOG_INFO_ENABLED 1
#define LOG_DEBUG_ENABLED 1
#define LOG_TRACE_ENABLED 1

// if in release build, disable debug mode logging
#else 
#define LOG_WARN_ENABLED 0
#define LOG_INFO_ENABLED 0
#define LOG_DEBUG_ENABLED 0
#define LOG_TRACE_ENABLED 0
#endif

/**************************************************************************/
/*!
	This enum contains the logging level enum for seriousness of the error
*/
/**************************************************************************/
typedef enum class LogLevel {
	LOG_LEVEL_FATAL,	//Errors that prevents application from running
	LOG_LEVEL_ERROR,	//Errors that may/may not prevent app from running
	LOG_LEVEL_WARN,	//Errors that may cause some sublevel harm to app
	LOG_LEVEL_INFO,	//Basic level logging for information
	LOG_LEVEL_DEBUG,	//Included only for debug/test build for debugging
	LOG_LEVEL_TRACE		//Includes very low level of detail for debugging mode
}LogLevel;


/******************************************************************************/
/*!
\brief
Creates a naming convention for the file name/ time stamp string

\param boolean
TRUE for Time stamp string, else FALSE for File String Name

\return
string of a name or a time stamp
*/
/******************************************************************************/
string FileNameInitialise(bool boolean);

/******************************************************************************/
/*!
\brief
Initialises the logging system on startup of the program

\param

\return
fstream of the open file
*/
/******************************************************************************/
fstream InitializeLogging();

/******************************************************************************/
/*!
\brief
Appends a buffer of text into the fstream

\param logFile
the logfile to be appended

\param buffer
the buffer used to append

\return
TRUE/ FALSE on append
*/
/******************************************************************************/
int8_t AppendLogging(std::fstream& logFile, char* buffer);

/******************************************************************************/
/*!
\brief
Shuts down the logging system

\param logfile
the logfile to be closed

\return
void
*/
/******************************************************************************/
void ShutDownLogging(std::fstream& logFile);

/******************************************************************************/
/*!
\brief
Remove the previous logging file of the same name

\param fileNile
the name of the log file to be removed from the directory

\return
void
*/
/******************************************************************************/
void RemoveLoggingFile(std::string fileName);

/******************************************************************************/
/*!
\brief
Logs the error into an output file

\param level
The seriousness of the error

\param message
The message to be logged

\return void
*/
/******************************************************************************/
void LogOutput(LogLevel level, const char* message, ...);

/*
LOGGING FUNCTIONS and How to use
When using Logging Functions, do #include "UTILS/NGDebug.h"
During your coding sessions, if you feel that there is a need for checking for errors, values, information printing or tracing code, you can use any of the functions below.

For Logging use: (msg) -> the VA_ARG (Printf("...%s%d%f%c", str, dec, float,char) <- similar to Printf syntax)
NGFATAL(msg) : For Fatal level of warning, game breaking error but you dont want it to break the runtime

NGERROR(msg): For Error Level of warning, may or may not break game, but still a close to fatal level

NGWARN(msg): For Lower Level of warning, not game breaking, but causes problems if not properly assigned

NGINFO(msg): For information printing, printing out information for self use

NGDEBUG(msg): For debugging purposes,  like checking if values are correct etc

NGTRACE(msg): For debugging purposes, if unsure where things are breaking, use this all around to check

Example of using:
char* array[10] {0}
If(array[i])
		NGINFO("The element in the array at position I is %d", array[i]);
else
	   NGWARN("The element in the array at position I is a '0', Put in a real value!);

*/

// Logs a Fatal-level message
#define FATAL(message, ...) LogOutput(LogLevel::LOG_LEVEL_FATAL, message, ##__VA_ARGS__ )

// Logs an Error-level message
#ifndef ERROR
#define ERROR(message, ...) LogOutput(LogLevel::LOG_LEVEL_ERROR, message, ##__VA_ARGS__ )
#endif

// Logs a Warning-level message
#if LOG_WARN_ENABLED == 1
#define WARN(message, ...) LogOutput(LogLevel::LOG_LEVEL_WARN, message, ##__VA_ARGS__ )
#else //does nothing if LOG_WARN_ENABLED != 1
#define WARN(message, ...)
#endif

// Logs a Info-level message
#if LOG_INFO_ENABLED == 1
#define INFO(message, ...) LogOutput(LogLevel::LOG_LEVEL_INFO, message, ##__VA_ARGS__ )
#else //does nothing if LOG_INFO_ENABLED != 1
#define INFO(message, ...)
#endif

// Logs a Debug-level message
#if LOG_DEBUG_ENABLED == 1
#define DEBUG(message, ...) LogOutput(LogLevel::LOG_LEVEL_DEBUG, message, ##__VA_ARGS__ )
#else //does nothing if LOG_DEBUG_ENABLED != 1
#define DEBUG(message, ...)
#endif

// Logs a Trace-level message
#if LOG_TRACE_ENABLED == 1
#define TRACE(message, ...) LogOutput(LogLevel::LOG_LEVEL_TRACE, message, ##__VA_ARGS__ )
#else //does nothing if LOG_TRACE_ENABLED != 1
#define TRACE(message, ...)
#endif

#endif