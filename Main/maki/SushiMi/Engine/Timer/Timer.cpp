
#include "Timer.h"
namespace Core
{
	void Timer::StartSecTimer(int timeInSeconds) {
		// this counts in seconds, can use without header
		using namespace std::literals;
		using namespace std;

		auto start = chrono::high_resolution_clock::now();
		this_thread::sleep_for(std::chrono::seconds(timeInSeconds)); //can adjust in future for when player starts playing?
		auto end = chrono::high_resolution_clock::now();

		chrono::duration<float> duration = end - start;
		cout << duration.count() << "s" << endl;
	}

	void Timer::StartMilTimer(int timeInMil) {
		// this counts in seconds, can use without header
		using namespace std::literals;
		using namespace std;

		auto start = chrono::high_resolution_clock::now();
		this_thread::sleep_for(std::chrono::milliseconds(timeInMil)); //can adjust in future for when player starts playing?
		auto end = chrono::high_resolution_clock::now();

		chrono::duration<float> duration = end - start;
		cout << duration.count() << "s" << endl;
	}
}




