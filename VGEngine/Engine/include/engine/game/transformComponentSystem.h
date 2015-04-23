#pragma once
#include "engine/game/componentSystem.h"
#include <vector>
namespace vg
{
	/**
	System that updates transformComponents
	*/
	class TransformComponentSystem :
		public ComponentSystem
	{
	public:
		TransformComponentSystem();
		~TransformComponentSystem();
		void update(GameObject* gameObject);
	};

}