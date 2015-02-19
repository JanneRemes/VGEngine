
#include "engine\utility\timer.h"

namespace vg
{
	float Timer::restart()
	{
		clock_t now = clock();
		const float delta = (now - mBefore) / static_cast<float>(CLOCKS_PER_SEC);
		mBefore = now;

		return delta;
	}
}
