
#pragma once

#include <ctime>

namespace vg
{
	/**
		Timer that is used to measure time
	*/
	class Timer
	{
	public:
		/**
			Restarts the timer
		*/
		float restart();
	private:
		clock_t mBefore = clock();
	};
}
