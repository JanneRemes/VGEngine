
#pragma once

#include <vector>

/// @todo Fix comments in this file

namespace vg
{
	class GameObject;

	/**
		<description>
	*/
	class Scene
	{
	public:
		Scene() = default;
		virtual ~Scene() = default;
	private:
		std::vector<GameObject*> mActivePool;   ///< description
		std::vector<GameObject*> mInactivePool; ///< description
	};
}
