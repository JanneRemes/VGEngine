#pragma once
#include <Box2D\Box2D.h>
#include <engine\game\component.h>
#include <engine\game\transformComponent.h>
namespace vg
{
		class PhysicsComponent : public Component
		{
		public:
			enum BODYTYPE { STATIC, DYNAMIC };
			static float scale;
			PhysicsComponent(TransformComponent *component, BODYTYPE type, b2World *world);
			
			Vector2<float> getPosition();
			float getRotation();
			void setVelocity(Vector2<float> velocity);

			void setDensity(float density);
			void setFriction(float friction);
			void setRestitution(float restitution);

		protected:
			b2Body *_body;
			b2FixtureDef _FixDef;
		};
}