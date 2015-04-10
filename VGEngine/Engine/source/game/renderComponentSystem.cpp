#include "engine/game/renderComponentSystem.h"
#include "engine/game/renderComponent.h"
using namespace vg;
RenderComponentSystem::RenderComponentSystem() :ComponentSystem()
{
}


RenderComponentSystem::~RenderComponentSystem()
{
}
void RenderComponentSystem::update(GameObject* gameObject)
{
	RenderComponent* component = gameObject->GetComponent<RenderComponent>();
	if (component != nullptr)
	{
		
	}
}