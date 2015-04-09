#pragma once
#include "engine/game/componentSystem.h"
#include <vector>
namespace vg
{
	class TransformComponentSystem :
		public ComponentSystem
	{
	public:
		TransformComponentSystem();
		~TransformComponentSystem();
		void update(GameObject* gameObject);
	};

}