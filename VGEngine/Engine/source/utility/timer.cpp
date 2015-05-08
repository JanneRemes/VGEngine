
#include "engine/utility/timer.h"

namespace vg
{
	Timer::Timer()
	{
		mStartTime = clock();
	}
	float Timer::restart()
	{
		clock_t current = clock();
		const float delta = (current - mStartTime) / static_cast<float>(CLOCKS_PER_SEC);
		mStartTime = current;

		return delta;
	}
	float Timer::getCurrentTimeSeconds()
	{
		clock_t current = clock();
		return (current - mStartTime) / static_cast<float>(CLOCKS_PER_SEC);
	}
	
	float Timer::getCurrentTimeMillis()
	{
		clock_t current = clock();
		return (current - mStartTime) / static_cast<float>(CLOCKS_PER_SEC) * 1000.0f;
	}
}
