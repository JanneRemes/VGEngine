
#pragma once

#include "engine/game/systemManager.h"

#include <vector>

namespace vg
{
	class GameObject;

	/**
		The stage for drawing and updating objects
	*/
	class Scene
	{
	public:
		/**
		Default constructor
		*/
		Scene();
		~Scene();

		virtual void loadObjects(){};
		/**
		Updates the scene
		@param dt The elapsed time since the game last updated
		*/
		virtual void update(float dt) {};

		/**
		Draws the scene
		*/
		void draw() {};
		
		/**
		Updates the scene
		@return returns the bool puased
		*/	
		bool getPaused() { return paused; }



		/**
		Adds a gameObject to the pool
		@param gObject gameObject that is being added in the pool
		*/
		void addGameObject(GameObject *gObject);

		/**
		Updates all the gameObjects that are in the pool
		*/
		void updateGameObjects(float deltaTime);

		/**
		@return Returns the componentSystemManager that the pool is using
		*/
		SystemManager* getComponentSystemManager(){ return &mSystemManager; }

		/**
		Sorts objects in active pool by layer
		*/
		void sortActivePool();

		/**
		Clears objects from the active objects pool
		*/
		void clearObjects();
		/**
		Resets systems
		*/
		void clearSystems();
	private:
		bool paused;							///< Bool which is used for determining if scene is paused
		SystemManager mSystemManager;			///< Updates different component systems
		std::vector<GameObject*> mActivePool;	///< List of the active gameObject pool

	};
}
