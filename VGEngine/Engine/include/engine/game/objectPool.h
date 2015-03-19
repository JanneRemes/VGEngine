#pragma once
#include <vector>
#include "engine/game/gameObject.h"
namespace vg
{
	class ObjectPool
	{
		struct PoolObjectType
		{
			GameObject prefab;
			int	   amount;
		};
	public:
		ObjectPool();
		~ObjectPool();
		GameObject getGameObject();//returns pooled object if available
		void addPrefabType(PoolObjectType prefabType);
	private:
		std::vector<GameObject> mActivePool;   ///< description
		std::vector<GameObject> mInactivePool; ///< description
		std::vector<PoolObjectType> mPoolPrefabs;
	};

}