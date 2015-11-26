
#pragma once

#include <string>

namespace vg
{
	std::string toStringi(int value, int width = 0);
	std::string toStringf(float value, int decimals = 0, int width = 0);
	std::string removeDigits(std::string str);
	int toInt(std::string str);
}