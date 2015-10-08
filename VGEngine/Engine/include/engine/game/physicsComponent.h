#pragma once
#include <Box2D\Box2D.h>
#include <engine\game\component.h>
namespace vg
{
		class PhysicsComponent : public Component
		{
		public:
			PhysicsComponent(b2World *world, float x, float y, float width, float height, b2BodyType type);
			b2Body* getBody() { return _body; };
		private:
			b2Body *_body;
		};
}