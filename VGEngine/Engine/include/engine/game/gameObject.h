
#pragma once

#include <vector>

namespace vg
{
	class Component;

	class GameObject
	{
	public:
		GameObject() = default;
		virtual ~GameObject() = default;
	private:
		std::vector<Component*> mComponents;
	};
}
