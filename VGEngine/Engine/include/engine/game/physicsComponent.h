#pragma once
#include <Box2D\Box2D.h>
#include <engine\game\component.h>
#include <engine\game\transformComponent.h>
namespace vg
{
		class PhysicsComponent : public Component
		{
			friend class PhysicsSystem;
		public:
			enum BODYTYPE { STATIC, DYNAMIC, KINEMATIC };
			static float scale;
			PhysicsComponent(TransformComponent *component, BODYTYPE type);
			
			void setPosition(Vector2<float> position);
			Vector2<float> getPosition();
			float getRotation();
			void setVelocity(Vector2<float> velocity);
			void applyForce(Vector2<float> force);

			void setDensity(float density);
			void setFriction(float friction);
			void setRestitution(float restitution);

			void setMass(float mass);
			void setMassCenter(Vector2<float> position);
			
			void setRotationLock(bool lock);

		protected:
			b2Body *_body;
			b2BodyDef bodyDef;
			b2FixtureDef _FixDef;
			b2MassData mMass;
		};
}