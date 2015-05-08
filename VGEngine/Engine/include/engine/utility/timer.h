
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
		Timer();
		float restart();
		float getCurrentTimeSeconds();
		float getCurrentTimeMillis();
	private:
		
		clock_t mStartTime;
	};
}
