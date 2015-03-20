
#pragma once

#include <vector>
#include "objectPool.h"
/// @todo Fix comments in this file

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
		Scene() : paused(false){};
		virtual ~Scene() = default;

		/**
		Updates the scene
		@param dt The elapsed time since the game last updated
		*/
		void update(float dt) {};

		/**
		Draws the scene
		*/
		void draw() {};
		
		/**
		Updates the scene
		@return returns the bool puased
		*/	
		bool getPaused() { return paused; }

	private:
		ObjectPool mObjectPool; ///< Pool of Objects
		bool paused;			///< Bool which is used for determining if scene is paused

	};
}
