#pragma once
#include <utility>

/// @todo Fix comments in this file

namespace vg
{
	class GameObject;
	class type_info;
	/**
		<description>
	*/
	class Component
	{
	public:
		Component() = default;
		virtual ~Component() = default;
		virtual void update() {}
	private:
		GameObject* mParent; ///< description
	};
}