
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
			<description>
			@return <description>
		*/
		static int nexti();

		/**
			<description>
			@param min <description>
			@param max <description>
			@return <description>
		*/
		static int nexti(int min, int max);

		/**
			<description>
			@return <description>
		*/
		static float nextf();

		/**
			<description>
			@param min <description>
			@param max <description>
			@return <description>
		*/
		static float nextf(float min, float max);
		/**
			<description>
			@param newSeed <description>
			@return <description>
		*/
		static void seed(unsigned int newSeed = time(nullptr));
	private:
	};
}
