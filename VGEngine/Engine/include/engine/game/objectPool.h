#pragma once
#include <vector>
#include "engine/game/gameObject.h"
#include "engine/game/systemManager.h"
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
		/*
		Removes gameObject from list and deletes it (and puts it nullpointer)
		@param gameobject you want to remove
		@return returns iterator pointing to next object after removed or  end of mActivePool
		*/
		std::vector<GameObject*>::iterator removeGameObject(GameObject *gObject);
		//void removeGameObjectInactivePool(GameObject gObject);
		//void createGameObjectPool(std::vector<PoolObjectType> *prefabs); //creates empty gameobjects to InactivePool from mPoolPrefabList

		/**
		Updates all the gameObjects that are in the pool
		*/
		void updateGameObjects();

		/**
		@return Returns the componentSystemManager that the pool is using 
		*/
		SystemManager* getComponentSystemManager(){ return &mSystemManager; }

		/**
		Sorts objects in active pool by layer
		*/
		void sortActivePool();

	private:
		SystemManager mSystemManager;///< Updates different component systems
		//void addPrefabToPool(PoolObjectType type); //<Adds poolobjectype's amount of gameobjects to inactivepool
		//bool loaded;
		std::vector<GameObject*> mActivePool;   ///< List of the active gameObject pool
		std::vector<GameObject> mInactivePool;  ///< List of the unactive gameObject pool
	};

}