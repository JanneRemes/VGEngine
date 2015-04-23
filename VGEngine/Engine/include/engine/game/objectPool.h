#pragma once
#include <vector>
#include "engine/game/gameObject.h"
#include "engine/game/componentSystemManager.h"
namespace vg
{
	/*struct PoolObjectType
	{
		GameObject *prefab;
		int	   amount;
		PoolObjectType(GameObject *prefab, int amount)
		{
			this->prefab = prefab;
			this->amount = amount;
		}
	};*/

	/**
	Class made to pool all objects for easier updating and managing
	*/
	class ObjectPool
	{

	public:
		ObjectPool();
		~ObjectPool();
		//GameObject *getGameObjectFromPool(std::string name);//returns pooled object if available

		/**
		Adds a gameObject to the pool
		@param gObject gameObject that is being added in the pool
		*/
		void addGameObject(GameObject *gObject);
		//void removeGameObjectInactivePool(GameObject gObject);
		//void createGameObjectPool(std::vector<PoolObjectType> *prefabs); //creates empty gameobjects to InactivePool from mPoolPrefabList

		/**
		Updates all the gameObjects that are in the pool
		*/
		void updateGameObjects();

		/**
		@return Returns the componentSystemManager that the pool is using 
		*/
		ComponentSystemManager* getComponentSystemManager(){ return &mComponentSystemManager; }
	private:
		ComponentSystemManager mComponentSystemManager;///< Updates different component systems
		//void addPrefabToPool(PoolObjectType type); //<Adds poolobjectype's amount of gameobjects to inactivepool
		//bool loaded;
		std::vector<GameObject*> mActivePool;   ///< List of the active gameObject pool
		std::vector<GameObject> mInactivePool; ///< List of the unactive gameObject pool
	};

}