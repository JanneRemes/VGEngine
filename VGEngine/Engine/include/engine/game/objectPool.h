#pragma once
#include <vector>
#include "engine/game/gameObject.h"
namespace vg
{
	struct PoolObjectType
	{
		GameObject prefab;
		int	   amount;
		PoolObjectType(GameObject prefab, int amount)
		{
			this->prefab = prefab;
			this->amount = amount;
		}
	};
	class ObjectPool
	{

	public:
		ObjectPool();
		~ObjectPool();
		GameObject getGameObject();//returns pooled object if available
		void addPrefabType(GameObject gameObject, int amount);
		void removePrefabType(GameObject gameObject, bool clear);//if clear then remove all pooled objects
		void createGameObjectPool(); //creates empty gameobjects to InactivePool from mPoolPrefabList
		void addPrefabToPool(PoolObjectType type); //Adds poolobjectype's amount of gameobjects to inactivepool
	private:
		bool loaded;
		std::vector<GameObject> mActivePool;   ///< description
		std::vector<GameObject> mInactivePool; ///< description
		std::vector<PoolObjectType> mPoolPrefabs;
	};

}