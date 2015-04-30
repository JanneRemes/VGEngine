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
		TestComponent* component = (*it)->GetComponent<TestComponent>();
		if (component != nullptr)
		{
			component->update();
		}
		vg::TransformComponent *transform = (*it)->GetComponent<vg::TransformComponent>();
		if (transform != nullptr)
		{
			transform->setRotation(transform->getRotation() + 1);
		}
	}
}