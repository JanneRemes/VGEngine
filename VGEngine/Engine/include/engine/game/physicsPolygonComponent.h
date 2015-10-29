#pragma once
#include <engine\game\physicsComponent.h>

namespace vg
{
		class PhysicsPolygonComponent : public PhysicsComponent
		{
		public:
			PhysicsPolygonComponent(TransformComponent *component, BODYTYPE type, float width = 0, float height = 0);
		private:
			b2PolygonShape mBoxShape;
		};
}