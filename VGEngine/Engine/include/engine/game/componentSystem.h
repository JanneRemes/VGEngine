#pragma once
#include "engine/game/gameObject.h"
namespace vg
{
	class ComponentSystem
	{
	public:
		ComponentSystem();
		~ComponentSystem();
		virtual void update(GameObject* gameObject);
	};

}