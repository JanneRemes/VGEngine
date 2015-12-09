
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
		Timer();

		/**
		Restarts the timer and returns elapsed time
		@return elapsed time in seconds
		*/
		float restart();

		/**
		@return elapsed time in seconds
		*/
		float getCurrentTimeSeconds();

		/**
		@return elapsed time in milliseconds
		*/
		float getCurrentTimeMillis();

	private:
		
		clock_t mStartTime;	///< tells when the Timer started
	};
}
