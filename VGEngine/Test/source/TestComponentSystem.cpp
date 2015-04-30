#include "TestComponentSystem.h"
#include "engine/game/game.h"
#include "TestComponent.h"
#include "engine/game/transformComponent.h"
TestComponentSystem::TestComponentSystem() :vg::ComponentSystem()
{
}


TestComponentSystem::~TestComponentSystem()
{
}
void TestComponentSystem::update(vg::GameObject* gameObject)
{
	TestComponent* component = gameObject->GetComponent<TestComponent>();
	if (component != nullptr)
	{
		component->update();
	}
	vg::TransformComponent *transform = gameObject->GetComponent<vg::TransformComponent>();
	if (transform != nullptr)
	{
		transform->setRotation(transform->getRotation() + 1);
	}
}