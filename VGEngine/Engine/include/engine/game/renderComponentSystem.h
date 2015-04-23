#pragma once
#include "engine/game/componentSystem.h"

namespace vg{

	/**
	System that updates renderComponents
	*/
	class RenderComponentSystem :
		public ComponentSystem
	{
	public:
		RenderComponentSystem();
		~RenderComponentSystem();
		void update(GameObject* gameObject);
	};

}