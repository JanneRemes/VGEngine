
#pragma once

/// @todo Fix comments in this file

namespace vg
{
	class GameObject;

	/**
		<description>
	*/
	class Component
	{
	public:
		Component() = default;
		virtual ~Component() = default;
	private:
		GameObject* mParent; ///< description
	};
}
