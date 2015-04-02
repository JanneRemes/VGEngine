#pragma once
#include "engine/game/gameObject.h"
namespace vg
{
	class ScriptSystem
	{
	public:
		ScriptSystem();
		~ScriptSystem();
		void update(GameObject* gameObject);

	};

}