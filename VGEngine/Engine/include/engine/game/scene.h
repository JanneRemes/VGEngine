
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
		Scene() : paused(false){};
		virtual ~Scene() = default;

		void update(float dt) {};
		void draw() {};

		bool getPaused() { return paused; }

	private:
		ObjectPool mObjectPool;
		bool paused;

	};
}
