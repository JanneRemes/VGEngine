
#pragma once

#include <vector>
#include "objectPool.h"
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
		ObjectPool mObjectPool;
	};
}
