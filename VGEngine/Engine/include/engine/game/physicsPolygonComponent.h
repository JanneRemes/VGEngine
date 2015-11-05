
#pragma once

#include "engine/game/physicsComponent.h"

namespace vg
{
	/**
	Class used to make a physics polygon component
	*/
	class PhysicsPolygonComponent : public PhysicsComponent
	{
	public:
		/**
		Contructor
		@param component Desired transform component you wish to add physics polygon component with
		@param type Can be either 'DYNAMIC', 'KINEMATIC' or 'STATIC', defines the type of the physics object
		@param width Sets the boxes width
		@param height Sets the boxes height
		*/
		PhysicsPolygonComponent(TransformComponent *component, BODYTYPE type, float width = 0, float height = 0);
	private:
		b2PolygonShape mBoxShape; ///< Polygon boxes shape

	};
}