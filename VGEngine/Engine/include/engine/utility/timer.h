
#pragma once

#include <ctime>

namespace vg
{
	class Timer
	{
	public:
		float restart()
		{
			clock_t now = clock();
			float delta = (now - mBefore) / static_cast<float>(CLOCKS_PER_SEC);
			mBefore = now;

			return delta;
		}
	private:
		clock_t mBefore = clock();
	};
}
