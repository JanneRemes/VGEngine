#pragma once
#include "engine/game/component.h"
namespace vg{
	class ScriptComponent :
		public Component
	{
	public:
		ScriptComponent();
		~ScriptComponent();
		void update();
	};
}

