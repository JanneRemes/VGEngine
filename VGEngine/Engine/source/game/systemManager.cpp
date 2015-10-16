#include "engine/game/systemManager.h"
#include "engine/game/transformComponent.h"
#include "engine/game/renderSystem.h"
#include "engine/game/deleteSystem.h"
#include "engine/game/textRenderSystem.h"
#include "engine/game/animationSystem.h"
#include "engine/game/physicsSystem.h"
using namespace vg;

SystemManager::SystemManager()
{
	systems.push_back(new DeleteSystem());
	systems.push_back(new RenderSystem());
	systems.push_back(new TextRenderSystem());
	systems.push_back(new AnimationSystem());
	PhysicsSystem *physicsSystem = new PhysicsSystem(0, -9.81 * 20);
	systems.push_back(physicsSystem);
	Vector2<int> resolution = Game::getInstance()->getGraphics()->getResolution();
	physicsSystem->createBorders(0, 0, resolution.getX(), resolution.getY());
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
