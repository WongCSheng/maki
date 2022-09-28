#pragma once
#include "../include/common_headers.hpp"

void InitTimer() {
	// this counts in seconds, can use without header
	using namespace std::literals;
	using namespace std;

	auto start = chrono::high_resolution_clock::now();
	this_thread::sleep_for(5s); //can adjust in future for when player starts playing?
	auto end = chrono::high_resolution_clock::now();

	chrono::duration<float> duration = end - start;
	cout << duration.count() << "s" << endl;

}

void RestartTimer() {
	Timer timer;
}



