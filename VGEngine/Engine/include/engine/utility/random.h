
#pragma once

#include <cstdlib>
#include <ctime>

namespace vg
{
	/**
		Has functions for generating random int and float values
	*/
	class Random
	{
	public:
		/**		
			@return Random number between 0 - 32767 (at least)
		*/
		static int nexti();

		/**
			@param min Minimum number to random from
			@param max Maximum number to random from
			@return Random number between the minimum and maximum numbers
		*/
		static int nexti(int min, int max);

		/**
			@return Random float number between 0 - 32767 (at least)
		*/
		static float nextf();

		/**
			@param min Minimum number to random from
			@param max Maximum number to random from
			@return Random float number between the minimum and maximum float numbers
		*/
		static float nextf(float min, float max);
		/**
			Sets seed for pseudo-random number generator algorithm
			@param newSeed An integer value to be used as seed by the pseudo-random number generator algorithm
		*/
		static void seed(unsigned int newSeed = time(nullptr));
	private:
	};
}
