
#pragma once

#include <vector>

namespace vg
{
	class GameObject;

	class Scene
	{
	public:
		Scene() = default;
		virtual ~Scene() = default;

		virtual void test();
	private:
		std::vector<GameObject*> mActivePool;
		std::vector<GameObject*> mInactivePool;
	};
}
