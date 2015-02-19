
#pragma once

#include <ctime>

/// @todo Fix comments in this file

namespace vg
{
	/**
		<description>
	*/
	class Timer
	{
	public:
		/**
			<description>
			@return The delta time
		*/
		float restart();
	private:
		clock_t mBefore = clock(); ///< description
	};
}
