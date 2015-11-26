
#include "engine/utility/string.h"

#include <sstream>
#include <iomanip>
#include <algorithm>

std::string vg::toStringi(int value, int width)
{
	std::ostringstream ss;
	if (width > 0)
		ss << std::setfill('0') << std::setw(width);
	ss << value;
	return ss.str();
}

std::string vg::toStringf(float value, int decimals, int width)
{
	std::ostringstream ss;
	if (decimals > 0)
		ss.precision(decimals);
	if (width > 0)
		ss << std::setfill('0') << std::setw(width);
	ss << std::fixed << value;
	return ss.str();
}

std::string vg::removeDigits(std::string str)
{
	int firstLetter = 0;
	for (int i = 0; i < str.size(); i++)
	{
		if (isalpha(str[i]))
		{
			firstLetter = i;
			break;
		}
	}
	str.erase(str.begin(), str.begin() + firstLetter);
	return str;
}

int vg::toInt(std::string str)
{
	std::remove_if(str.begin(), str.end(), &isalpha);
	std::istringstream iss(str);
	int i;
	iss >> i;
	return i;
}
