/*!
@file		Timer.cpp
@author		p.tzechengjennifer@digipen.edu
@date		28/09/2022

This file contains code to start a timer. It can count in seconds or milliseconds.
*//*__________________________________________________________________________*/

#pragma once
#include "../include/common_headers.hpp"

/*  _________________________________________________________________________ */
/*! StartSecCountdown
@param int timeInSeconds
countdown timing in seconds
@return none

starts a countdown, tells you in console when countdown is over
*/
void StartSecCountdown(int timeInSeconds) {
	using namespace std::literals;
	using namespace std;

	auto start = chrono::high_resolution_clock::now();
	this_thread::sleep_for(std::chrono::seconds(timeInSeconds));
	auto end = chrono::high_resolution_clock::now();

	chrono::duration<float> duration = end - start;
	cout << duration.count() << "s" << endl;
}

/*  _________________________________________________________________________ */
/*! StartMilCountdown
@param int timeInMil
countdown timing in milliseconds
@return none

starts a countdown, tells you in console when countdown is over
*/
void StartMilCountdown(int timeInMil) {
	using namespace std::literals;
	using namespace std;

	auto start = chrono::high_resolution_clock::now();
	this_thread::sleep_for(std::chrono::milliseconds(timeInMil)); 
	auto end = chrono::high_resolution_clock::now();

	chrono::duration<float> duration = end - start;
	cout << duration.count() << "s" << endl;
}





