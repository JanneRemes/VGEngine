#pragma once
#include <Box2D\Box2D.h>
#include <engine\game\component.h>
#include <engine\game\transformComponent.h>
namespace vg
{
		class PhysicsComponent : public Component
		{

		public:
			enum SHAPE{ BOX, CIRCLE };
			static float scale;
			// Create physics box
			PhysicsComponent(TransformComponent *component, b2BodyType type, b2World *world, SHAPE shape);

			b2Body* getBody() { return _body; };
			b2FixtureDef* getFixture() { return &FixDef; };
		private:
			b2Body *_body;
			b2FixtureDef FixDef;
		};
}