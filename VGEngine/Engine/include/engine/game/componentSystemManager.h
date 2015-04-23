#pragma once
#include "engine/game/gameObject.h"
#include "engine/game/componentSystem.h"
#include <vector>
namespace vg
{
	/**
	Manages componentSystems
	*/
	class ComponentSystemManager
	{
	public:
		ComponentSystemManager();
		~ComponentSystemManager();

		/**
		Updates the components inside the gameObject
		@param gameObject The gameObject that is going to be updated inside the componentSystems
		*/
		void update(GameObject* gameObject);
		void addSystem(ComponentSystem *system);
	private:
		std::vector<ComponentSystem*> systems;

	};

}