
#pragma once

#include <string>

namespace vg
{
	/**
	@param value number
	@param width result width with zeroes as padding
	@return integer in string form
	*/
	std::string toStringi(int value, int width = 0);
	
	/**
	@param value number
	@param decimals max number of decimals in result
	@param width of the result with zeroes as padding
	@return float in string form
	*/
	std::string toStringf(float value, int decimals = 0, int width = 0);
	
	/**
	@return string without any numbers
	*/
	std::string removeDigits(std::string str);
	
	/**
	@param str a string
	@return first integer from a string
	*/
	int toInt(std::string str);
}