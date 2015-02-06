
#pragma once

namespace vg
{
	class GameObject;

	class Component
	{
	public:
		Component() = default;
		virtual ~Component() = default;
	private:
		GameObject* mParent;
	};
}
