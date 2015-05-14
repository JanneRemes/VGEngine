#pragma once
#include <vector>
#include "engine/game/gameObject.h"
#include "engine/game/systemManager.h"
namespace vg
{
	/**
	Class made to pool all objects for easier updating and managing
	*/
	class ObjectPool
	{

	public:
		ObjectPool();
		~ObjectPool();
		
		/**
		Adds a gameObject to the pool
		@param gObject gameObject that is being added in the pool
		*/
		void addGameObject(GameObject *gObject);
		
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
		SystemManager mSystemManager;		  ///< Updates different component systems
		std::vector<GameObject*> mActivePool; ///< List of the active gameObject pool
		
	};

}