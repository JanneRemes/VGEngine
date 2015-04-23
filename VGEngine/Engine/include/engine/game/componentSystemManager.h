#pragma once
#include "engine/game/gameObject.h"
#include "engine/game/componentSystem.h"
#include <vector>
namespace vg
{
	class ComponentSystemManager
	{
	public:
		ComponentSystemManager();
		~ComponentSystemManager();
		void update(GameObject* gameObject);
		void addSystem(ComponentSystem *system);
	private:
		std::vector<ComponentSystem*> systems;

	};

}