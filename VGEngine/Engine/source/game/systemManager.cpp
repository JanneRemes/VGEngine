#include "engine/game/systemManager.h"
#include "engine/game/transformComponent.h"
#include "engine/game/renderSystem.h"
#include "engine/game/deleteSystem.h"
using namespace vg;

SystemManager::SystemManager()
{
	systems.push_back(new DeleteSystem());
	systems.push_back(new RenderSystem());
}


SystemManager::~SystemManager()
{
}
void SystemManager::update(std::vector<GameObject*> *gameObjects,float deltaTime)
{
		for (auto it = systems.begin(); it != systems.end(); it++)
		{
			(*it)->update(gameObjects,deltaTime);
		}
	

}
void SystemManager::addSystem(System *system)
{
	systems.push_back(system);
}