
#include "engine/game/systemManager.h"
#include "engine/game/transformComponent.h"
#include "engine/game/renderSystem.h"
#include "engine/game/deleteSystem.h"
#include "engine/game/animationSystem.h"
#include "engine/game/physicsSystem.h"
#include "engine/game/game.h"
#include "engine/graphics/screen.h"

using namespace vg;
using namespace vg::graphics;

SystemManager::SystemManager()
{
	addDefaultSystems();
}


SystemManager::~SystemManager()
{
}
void SystemManager::update(std::vector<GameObject*> *gameObjects, float deltaTime)
{
	for (int i = 0; i < systems.size(); i++)
	{
		Scene *scene = Game::getInstance()->getSceneManager()->getActiveScene();
		systems[i]->update(gameObjects, deltaTime);
		if (scene != Game::getInstance()->getSceneManager()->getActiveScene())
			break;
	}


}
void SystemManager::addSystem(System *system)
{
	systems.push_back(system);
	sort(systems.begin(), systems.end(),
		[](System* a, System* b)
	{
		return a->getPriority() < b->getPriority();
	});


}
void SystemManager::clearSystems()
{
	for (int i = 0; i < systems.size(); i++)
		delete systems[i];
	systems.clear();
}
void SystemManager::addDefaultSystems()
{
	addSystem(new DeleteSystem());

	addSystem(new AnimationSystem());
	PhysicsSystem *physicsSystem = new PhysicsSystem(0, -9.81);
	addSystem(physicsSystem);
	physicsSystem->createBorders(0, 0, Screen::getX(), Screen::getY());
	addSystem(new RenderSystem());
}