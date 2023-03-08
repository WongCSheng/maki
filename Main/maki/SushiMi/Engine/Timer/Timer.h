#pragma once

#ifndef TIMER_H
#define TIMER_H

#include "../Headers/STL_Header.h"
namespace Core
{
	struct Timer {

		//need to initialize values
		std::chrono::time_point<std::chrono::steady_clock> start = std::chrono::high_resolution_clock::now();
		std::chrono::time_point<std::chrono::steady_clock> end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<float> duration;

		Timer() : duration( 0.f ) {
			using namespace std;
			auto start = chrono::high_resolution_clock::now();
		}

		~Timer() {
			using namespace std;
			end = chrono::high_resolution_clock::now();
			duration = end - start;

			float ms = duration.count() * 1000.0f;
			cout << "Time passed: " << ms << "ms" << endl;
		}
	};
}


#endif