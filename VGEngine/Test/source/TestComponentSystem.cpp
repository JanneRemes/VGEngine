#include "TestComponentSystem.h"
#include "engine/game/game.h"
#include "TestComponent.h"
#include "engine/game/transformComponent.h"
TestComponentSystem::TestComponentSystem() :vg::System()
{
}


TestComponentSystem::~TestComponentSystem()
{
}
void TestComponentSystem::update(std::vector<vg::GameObject*> *gameObjects)
{
	for (auto it = gameObjects->begin(); it != gameObjects->end(); it++)
	{
		TestComponent* component = (*it)->getComponent<TestComponent>();
		if (component != nullptr)
		{
			component->update();
		}
		vg::TransformComponent *transform = (*it)->getComponent<vg::TransformComponent>();
		if (transform != nullptr)
		{
			transform->setRotation(transform->getWorldRotation() + 1);
		}
	}
}