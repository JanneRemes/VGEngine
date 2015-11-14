
#include "engine/utility/color.h"

#include <random>

using namespace vg;

Color::Color()
{
	red = green = blue = 0;
	alpha = 255;
}

Color::Color(const Color& other)
{
	red = other.red;
	green = other.green;
	blue = other.blue;
	alpha = other.alpha;
}

Color::Color(unsigned char _red, unsigned char _green, unsigned char _blue, unsigned char _alpha)
: red(_red), green(_green), blue(_blue), alpha(_alpha)
{
}

vg::Color Color::random()
{
	return Color(rand() % 255, rand() % 255, rand() % 255, 255);
}
