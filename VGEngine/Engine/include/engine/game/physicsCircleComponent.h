#pragma once
#include <engine\game\physicsComponent.h>

namespace vg
{
		class PhysicsCircleComponent : public PhysicsComponent
		{
		public:
			PhysicsCircleComponent(TransformComponent *component, b2BodyType type, b2World *world, float radius = 0);
		private:
			b2CircleShape mCircleShape;
		};
}