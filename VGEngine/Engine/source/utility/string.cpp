
#include "engine/utility/string.h"

#include <sstream>
#include <iomanip>

using namespace std;

string vg::toString(int value, int width)
{
	ostringstream ss;
	if (width > 0)
		ss << setfill('0') << setw(width);
	ss << value;
	return ss.str();
}

string vg::toString(float value, int decimals, int width)
{
	ostringstream ss;
	if (decimals > 0)
		ss.precision(decimals);
	if (width > 0)
		ss << setfill('0') << setw(width);
	ss << value;
	return ss.str();
}