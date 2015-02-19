
#pragma once

#include <vector>

/// @todo Fix comments in this file

namespace vg
{
	class Component;

	/**
		<description>
	*/
	class GameObject
	{
	public:
		GameObject() = default;
		virtual ~GameObject() = default;
	private:
		std::vector<Component*> mComponents; ///< description
	};
}
