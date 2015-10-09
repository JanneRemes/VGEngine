#pragma once
#include <Box2D\Box2D.h>
#include <engine\game\component.h>
namespace vg
{
		class PhysicsComponent : public Component
		{
		public:
			// Create physics box
			PhysicsComponent(float x, float y, float width, float height, b2BodyType type, b2World *world);
			// Create physics circle
			PhysicsComponent(float x, float y, float radius, b2BodyType type, b2World *world);

			b2Body* getBody() { return _body; };
		private:
			b2Body *_body;
		};
}