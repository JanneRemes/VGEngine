#pragma once
#include "engine/game/gameObject.h"
#include "engine/game/system.h"
#include <vector>
namespace vg
{
	/**
	Manages componentSystems
	*/
	class SystemManager
	{
	public:
		SystemManager();
		~SystemManager();

		/**
		Updates the components inside the gameObject
		@param gameObject The gameObject that is going to be updated inside the componentSystems
		*/
		void update(std::vector<GameObject*> *gameObjects);
		void addSystem(System *system);
	private:
		std::vector<System*> systems;

	};

}