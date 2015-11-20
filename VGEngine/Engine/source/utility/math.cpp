
#include "engine/utility/math.h"

using namespace vg;

float Math::radianToDegrees(float radian)
{
	return ((static_cast<float>(180) / 3.14159265358f) * radian);
}

float Math::degreesToRadians(float degrees)
{
	return (3.14159265358f / static_cast<float>(180)) * degrees;
}
