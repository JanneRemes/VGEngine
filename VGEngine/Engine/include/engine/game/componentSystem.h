#pragma once
#include "engine/game/gameObject.h"
namespace vg
{
	class ComponentSystem
	{
	public:
		ComponentSystem();
		~ComponentSystem();
		void update(GameObject* gameObject);
	};

}