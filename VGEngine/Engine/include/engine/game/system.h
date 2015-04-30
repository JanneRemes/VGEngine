#pragma once
#include "engine/game/gameObject.h"
#include <vector>
namespace vg
{
	/**
	System-like class for s that is used for updating s
	*/
	class System
	{
	public:
		System();
		~System();

		/**
		Updates the s inside the gameObject
		@param gameObject The gameObject whos s we are updating
		*/
		virtual void update(std::vector<GameObject*> *gameObjects);
	};

}