#pragma once
#include "engine/game/gameObject.h"
namespace vg
{
	/**
	System-like class for components that is used for updating components
	*/
	class ComponentSystem
	{
	public:
		ComponentSystem();
		~ComponentSystem();

		/**
		Updates the components inside the gameObject
		@param gameObject The gameObject whos components we are updating
		*/
		virtual void update(GameObject* gameObject);
	};

}