#pragma once
#include <engine\game\physicsComponent.h>

namespace vg
{
	/**
	Class used to make a physics circle component
	*/
		class PhysicsCircleComponent : public PhysicsComponent
		{
		public:
			/**
			Constructor for the physics circle component
			@param component Desired transform component you wish to add physics polygon component with
			@param type Can be either 'DYNAMIC', 'KINEMATIC' or 'STATIC', defines the type of the physics object
			@param radius Customizeable radius value for the circle objects physics, by default this value will be the width of the transform
			*/
			PhysicsCircleComponent(TransformComponent *component, BODYTYPE type, float radius = 0);
		private:
			b2CircleShape mCircleShape;
		};
}