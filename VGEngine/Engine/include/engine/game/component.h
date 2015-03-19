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
		type_info *mType;
		Component() = default;
		virtual ~Component() = default;
		virtual void Update() = 0;
	private:
		GameObject* mParent; ///< description
	};
}