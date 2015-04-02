#pragma once
#include "engine/game/scriptSystem.h"
#include "engine/game/gameObject.h"
#include "engine/game/transformComponentSystem.h"
namespace vg
{
	class ComponentSystemManager
	{
	public:
		ComponentSystemManager();
		~ComponentSystemManager();
		void update(GameObject* gameObject);
	private:
		ScriptSystem scriptSystem;
		TransformComponentSystem transformSystem;
	};

}