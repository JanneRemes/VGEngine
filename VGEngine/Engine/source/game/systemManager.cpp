
#include "engine/game/systemManager.h"
#include "engine/game/transformComponent.h"
#include "engine/game/renderSystem.h"
#include "engine/game/deleteSystem.h"
#include "engine/game/textRenderSystem.h"
#include "engine/game/animationSystem.h"
#include "engine/game/physicsSystem.h"
#include "engine/graphics/screen.h"
using namespace vg;
using namespace vg::graphics;

SystemManager::SystemManager()
{
	addSystem(new DeleteSystem());

	addSystem(new TextRenderSystem());
	addSystem(new AnimationSystem());
	PhysicsSystem *physicsSystem = new PhysicsSystem(0, -9.81);
	addSystem(physicsSystem);
	physicsSystem->createBorders(0, 0, Screen::getX(), Screen::getY());
	addSystem(new RenderSystem());
}


SystemManager::~SystemManager()
{
}
void SystemManager::update(std::vector<GameObject*> *gameObjects, float deltaTime)
{
	for (auto it = systems.begin(); it != systems.end(); it++)
	{
		(*it)->update(gameObjects, deltaTime);
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
