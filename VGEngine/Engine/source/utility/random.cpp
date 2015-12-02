
#include "engine/utility/random.h"
#include "engine/utility/math.h"

#include <math.h>

namespace vg
{
	int Random::nexti()
	{
		return nexti(0, RAND_MAX);
	}

	int Random::nexti(int min, int max)
	{
		if (min == max)
			return min;

		return min + rand() % (Math::abs(min - max) + 1);
	}

	float Random::nextf()
	{
		return nextf(0.0f, 1.0f);
	}

	float Random::nextf(float min, float max)
	{
		if (min == max)
			return min;

		const float phase = rand() / static_cast<float>(RAND_MAX);
		return min + fabsf(min - max) * phase;
	}

	void Random::seed(unsigned int newSeed)
	{
		srand(newSeed);
	}
}
