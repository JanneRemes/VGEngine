#include "engine/game/scriptSystem.h"
#include "engine/game/scriptComponent.h"

using namespace vg;

ScriptSystem::ScriptSystem()
{
}


ScriptSystem::~ScriptSystem()
{
}
void ScriptSystem::update(GameObject* gameObject)
{
	ScriptComponent* component = gameObject->GetComponent<ScriptComponent>();
	component->update();
}