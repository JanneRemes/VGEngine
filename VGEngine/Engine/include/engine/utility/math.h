
#pragma once

namespace vg
{
	class Math
	{
	public:
		template<class T>
		static T abs(T value)
		{
			return value < 0 ? -value : value;
		}
	private:
	};
}
