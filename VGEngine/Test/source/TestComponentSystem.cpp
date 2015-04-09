#include "TestComponentSystem.h"
#include "engine/game/game.h"
#include "TestComponent.h"
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
}