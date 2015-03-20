#pragma once
#include <vector>
#include "engine/game/gameObject.h"
namespace vg
{
	struct PoolObjectType
	{
		GameObject *prefab;
		int	   amount;
		PoolObjectType(GameObject *prefab, int amount)
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
		GameObject *getGameObjectFromPool(std::string name);//returns pooled object if available
		void addGameObject(GameObject gObject);
		void removeGameObjectInactivePool(GameObject gObject);
		void createGameObjectPool(std::vector<PoolObjectType> *prefabs); //creates empty gameobjects to InactivePool from mPoolPrefabList
	private:
		void addPrefabToPool(PoolObjectType type); //Adds poolobjectype's amount of gameobjects to inactivepool
		bool loaded;
		std::vector<GameObject> mActivePool;   ///< description
		std::vector<GameObject> mInactivePool; ///< description
	};

}