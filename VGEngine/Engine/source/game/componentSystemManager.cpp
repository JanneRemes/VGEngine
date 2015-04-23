#include "engine/game/componentSystemManager.h"
#include "engine/game/transformComponent.h"
#include "engine/game/renderComponentSystem.h"
using namespace vg;

ComponentSystemManager::ComponentSystemManager()
{
	systems.push_back(new RenderComponentSystem());
}


ComponentSystemManager::~ComponentSystemManager()
{
}
void ComponentSystemManager::update(GameObject* gameObject)
{
		for (auto it = systems.begin(); it != systems.end(); it++)
		{
			(*it)->update(gameObject);
		}
	

}
void ComponentSystemManager::addSystem(ComponentSystem *system)
{
	systems.push_back(system);
}