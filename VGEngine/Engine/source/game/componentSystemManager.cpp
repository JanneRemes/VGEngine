#include "engine/game/componentSystemManager.h"
#include "engine/game/transformComponent.h"
using namespace vg;

ComponentSystemManager::ComponentSystemManager()
{
	systems.push_back(new TransformComponentSystem());
}


ComponentSystemManager::~ComponentSystemManager()
{
}
void ComponentSystemManager::update(GameObject* gameObject)
{
		//scriptSystem.update(gameObject);
		//transformSystem.update(gameObject);
		for (auto it = systems.begin(); it != systems.end(); it++)
		{
			(*it)->update(gameObject);
		}
	

}
void ComponentSystemManager::addSystem(ComponentSystem *system)
{
	systems.push_back(system);
}