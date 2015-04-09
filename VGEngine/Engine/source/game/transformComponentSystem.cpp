#include "engine/game/transformComponentSystem.h"
#include "engine/game/transformComponent.h"
using namespace vg;
TransformComponentSystem::TransformComponentSystem() :ComponentSystem()
{
}


TransformComponentSystem::~TransformComponentSystem()
{
}
void TransformComponentSystem::update(GameObject* gameObject)
{
	TransformComponent* component = gameObject->GetComponent<TransformComponent>();
	if (component != nullptr)
	{
		component->update();
	}
	
}