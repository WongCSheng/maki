/*!
@file		Timer.h
@author		p.tzechengjennifer@digipen.edu
@date		28/09/2022

This file contains a struct we can use to start a timer.
It can count in seconds or milliseconds, it starts a timer in ms when it is constructed and
gives you time passed when it is destroyed.
*//*__________________________________________________________________________*/

#pragma once
#include "../include/common_headers.hpp"
#ifndef TIMER_H
#define TIMER_H

struct Timer {

	//need to initialize values
	std::chrono::time_point<std::chrono::steady_clock> start = std::chrono::high_resolution_clock::now();
	std::chrono::time_point<std::chrono::steady_clock> end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<float> duration = std::chrono::seconds(0); //need to initialize

	/*  _________________________________________________________________________ */
	/*! Timer
	@param none
	@return none

	save current time
	*/
	Timer() {
		using namespace std;
		auto start = chrono::high_resolution_clock::now();
	}
	/*  _________________________________________________________________________ */
	/*! ~Timer
	@param none
	@return none

	use start time and end time to calculate time passed.
	*/
	~Timer() { //call to end timer
		using namespace std;
		auto end = chrono::high_resolution_clock::now();
		duration = end - start;

		float ms = duration.count() * 1000.0f;
		cout << "Time passed: " << ms << "ms" << endl;
	}
};

#endif