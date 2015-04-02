#include "engine/game/componentSystemManager.h"
#include "engine/game/scriptComponent.h"
#include "engine/game/transformComponent.h"
using namespace vg;

ComponentSystemManager::ComponentSystemManager()
{
	scriptSystem = ScriptSystem();
	transformSystem = TransformComponentSystem();
}


ComponentSystemManager::~ComponentSystemManager()
{
}
void ComponentSystemManager::update(GameObject* gameObject)
{
	ScriptComponent* component = gameObject->GetComponent<ScriptComponent>();
	if (component != nullptr)
	{
		scriptSystem.update(gameObject);
	}
	TransformComponent* transformComponent = gameObject->GetComponent<TransformComponent>();
	if (transformComponent != nullptr)
	{
		transformSystem.update(gameObject);
	}

}