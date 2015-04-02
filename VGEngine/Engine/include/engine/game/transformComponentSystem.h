#pragma once
#include "engine/game/componentSystem.h"
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