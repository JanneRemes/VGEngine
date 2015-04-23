#pragma once
#include <utility>

namespace vg
{
	class GameObject;
	class type_info;
	/**
		Base for all components
	*/
	class Component
	{
	public:
		Component() = default;
		virtual ~Component() = default;
	private:
		GameObject* mParent; ///< Gameobject parent of the component
	};
}