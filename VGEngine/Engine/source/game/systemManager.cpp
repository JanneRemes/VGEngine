#include "engine/game/systemManager.h"
#include "engine/game/transformComponent.h"
#include "engine/game/renderSystem.h"
using namespace vg;

SystemManager::SystemManager()
{
	systems.push_back(new RenderSystem());
}


SystemManager::~SystemManager()
{
}
void SystemManager::update(std::vector<GameObject*> *gameObjects)
{
		for (auto it = systems.begin(); it != systems.end(); it++)
		{
			(*it)->update(gameObjects);
		}
	

}
void SystemManager::addSystem(System *system)
{
	systems.push_back(system);
}