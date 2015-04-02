#pragma once
#include "engine/game/componentSystem.h"

namespace vg{
	class RenderComponentSystem :
		public ComponentSystem
	{
	public:
		RenderComponentSystem();
		~RenderComponentSystem();
	};

}