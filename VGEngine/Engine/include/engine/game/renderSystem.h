#pragma once
#include "engine/game/system.h"

namespace vg{

	/**
	System that updates renderComponents
	*/
	class RenderSystem :
		public System
	{
	public:
		RenderSystem();
		~RenderSystem();
		void update(std::vector<GameObject*> *gameObjects);
	};

}