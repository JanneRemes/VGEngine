#pragma once
#include <Box2D\Box2D.h>
#include <engine\game\component.h>
namespace vg
{
		class PhysicsComponent : public Component
		{
		public:
			PhysicsComponent(b2World world);
			b2Body* getBody() { return _body; };
		private:
			b2Body *_body;
		};
}