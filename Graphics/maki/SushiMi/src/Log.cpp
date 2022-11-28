/******************************************************************************/
/*!
\file		Log.cpp
\author 	Aurelia Chong
\par    	email: fei.x@digipen.edu
\date   	16 Nov 2022
\brief		This header file contains the engine's assert functions

Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
*/
/******************************************************************************/


#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <ctime>

#include "../Headers/Log.h"

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
	//using namespace std;
	string FileNameInitialise(bool boolean) {
	string fileName = "Log.txt";
	string fileName2;
	string timeStamp;
	std::stringstream buffer;

	// THIS FEATURE ALLOWS FOR TIME SPECIFIC ERROR LOGGING
	// Will result in multiple files being generated if so
	time_t ttime = time(0);
	tm* localTime = localtime(&ttime);

	if (boolean) {
		buffer << "["
			<< std::setw(2) << std::setfill('0')
			<< localTime->tm_hour << ":"
			<< std::setw(2) << std::setfill('0')
			<< localTime->tm_min << ":"
			<< std::setw(2) << std::setfill('0')
			<< localTime->tm_sec
			<< "]\n";
		buffer >> timeStamp;
		//change to fileName 2 when working as intended
		return timeStamp;
	}
	else {
		buffer << "Log_"
			<< localTime->tm_mday
			<< 1 + localTime->tm_mon
			<< 1900 + localTime->tm_year
			<< localTime->tm_hour
			<< localTime->tm_min
			<< localTime->tm_sec
			<< ".txt";
		buffer >> fileName2;

		//change to fileName 2 when working as intended
		return fileName;
	}
	//return fileName;
}

/******************************************************************************/
/*!
\brief
Initialises the logging system on startup of the program

\param

\return
fstream of the open file
*/
/******************************************************************************/
std::fstream InitializeLogging() {
	std::fstream logFile;
	//switch to fileName2 for time specific logging
	string fileName = FileNameInitialise(false);
	logFile.open(fileName, logFile.app | logFile.in | logFile.out);
	if (!logFile.is_open()) {
		printf("Unable to open file! \n");
	}
	// Check if file is empty
	logFile.seekg(0, std::ios::end);
	int length = (int)logFile.tellg();
	if (!length) {
		time_t ttime = time(0);
		tm* localTime = localtime(&ttime);
		logFile << "Log File Dated: "
			<< localTime->tm_mday << "/"
			<< 1 + localTime->tm_mon << "/"
			<< 1900 + localTime->tm_year << "\t"
			<< "Timed: "
			<< std::setw(2) << std::setfill('0')
			<< localTime->tm_hour << ":"
			<< std::setw(2) << std::setfill('0')
			<< localTime->tm_min << ":"
			<< std::setw(2) << std::setfill('0')
			<< localTime->tm_sec << "\n";
	}
	return logFile;
}

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
int8_t AppendLogging(std::fstream& logFile, char* buffer) {
	if (logFile.is_open()) {
		logFile << buffer;
		return true;
	}
	else {
		return false;
	}
}

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
void ShutDownLogging(std::fstream& logFile) {
	logFile.close();
}

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
void RemoveLoggingFile(std::string fileName) {
	int status = remove(fileName.c_str());
	if (status) {
		//WARN("Unable to remove Log File!");
		std::cout << "Unable to remove Log File!";
	}
}

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
void LogOutput(LogLevel level, const char* message, ...) {
	std::fstream outFile = InitializeLogging();
	// Array of strings to append into message for formatting
	const char* LevelStrings[6] = {
		"[FATAL]: ",
		"[ERROR]: ",
		"[WARN]: ",
		"[INFO]: ",
		"[DEBUG]: ",
		"[TRACE]: " };
	//char IsError = level < LogLevel::LOG_LEVEL_WARN; // FATAL and ERROR is considered Error, the rest are sub errors

	const int BufLen = 1000;
	char OutMessage[BufLen];
	//Memory::ZeroMem(OutMessage, sizeof(OutMessage));

	//formatting of output message
	va_list ArgPtr;
	va_start(ArgPtr, message);
	vsnprintf(OutMessage, BufLen, message, ArgPtr);
	va_end(ArgPtr);
	//append to the output message with the error specific messages
	char OutMessage2[BufLen]; // temporary message buffer 

	string buffer = FileNameInitialise(true);
	/*if (outFile.) {

	}*/
	//sprintf(OutMessage2, "%s%s\n", LevelStrings[(int)level], OutMessage);
	sprintf(OutMessage2, "%s\t%s%s\n", buffer.c_str(), LevelStrings[(int)level], OutMessage);

	//Platform specific output
	//if(IsError)				//remove the comment if release build
	printf("%s", OutMessage2);

	//Logging into an output file
	int8_t appendStatus = AppendLogging(outFile, OutMessage2);
	if (!appendStatus) {
		printf("LOGFILE APPEND FAILURE\n");
	}
	ShutDownLogging(outFile);
}

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
void ReportAssertionFailure(const char* expression, const char* message, const char* file, int line) {
	LogOutput(LogLevel::LOG_LEVEL_FATAL,
		"BREAKPOINT WAS TRIGGERED >> ASSERTION FAILURE: %s\n\t\tMESSAGE: %s\n\t\tFILE: %s, LINE NO.: %d.\n",
		expression, message, file, line);
}