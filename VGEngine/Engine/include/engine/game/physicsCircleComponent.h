#pragma once
#include <engine\game\physicsComponent.h>

namespace vg
{
		class PhysicsCircleComponent : public PhysicsComponent
		{
		public:
			PhysicsCircleComponent(TransformComponent *component, BODYTYPE type, float radius = 0);
		private:
			b2CircleShape mCircleShape;
		};
}