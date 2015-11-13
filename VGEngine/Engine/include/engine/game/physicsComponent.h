
#pragma once

#include "engine/game/component.h"
#include "engine/utility/Vector2.h"

#include <Box2D\Box2D.h>

namespace vg
{
	//forward declaration
	class TransformComponent;

	class PhysicsComponent : public Component
	{
		friend class PhysicsSystem;
	public:
		enum BODYTYPE { STATIC, DYNAMIC, KINEMATIC };	///< physicsComponents body type
		enum FILTER : short { LOW = 0x0001, MIDDLE = 0x0002, HIGH = 0x0004, TOP = 0x0008 };
		static float scale;								///< Scale of the object
		/**
		Constructor for creating PhysicsComponent
		@param component Desired TransformComponent that you wish to add physicsComponent with
		@param type Can be either 'DYNAMIC', 'KINEMATIC' or 'STATIC', defines the type of the physics object
		*/
		PhysicsComponent(TransformComponent *component, BODYTYPE type);
		~PhysicsComponent();
		/**
		Sets Vector2 position for the physicsComponent
		*/
		void setPosition(Vector2<float> position);

		/**
		@return Returns Vector2 position of the physicsComponent
		*/
		Vector2<float> getPosition();

		/**
		@return Returns rotation of the physicsComponent
		*/
		float getRotation();

		/**
		Set body rotation
		*/
		void setRotation(float rotation);

		/**
		Sets velocity for the physicsComponent that it will move with
		*/
		void setVelocity(Vector2<float> velocity);

		/**
		Sets angular velocity
		*/
		void setAngularVelocity(float velocity);

		/**
		Applies force for the physicsComponent
		*/
		void applyForce(Vector2<float> force);


		void applyLinearImpulse(Vector2<float> force);

		/**
		Sets density for the physicsComponent
		*/
		void setDensity(float density);

		/**
		Sets friction for the physicsComponent
		*/
		void setFriction(float friction);

		/**
		Sets restitution for the physicsComponent
		*/
		void setRestitution(float restitution);

		/**
		Sets mass for the physicsComponent
		*/
		void setMass(float mass);

		/**
		Sets the center of the mass of the physicsComponent object
		@param position Center of mass of the object
		*/
		void setMassCenter(Vector2<float> position);

		/**
		Locks the rotation that the object will have while having physics
		@param lock True or False depending if you need it locked or not
		*/
		void setRotationLock(bool lock);

		/**
		Set collision filter
		*/
		void setCollisionFilter(FILTER filter);

	protected:
		b2Body *_body;			///< PhysicsComponents Box2D body
		b2BodyDef bodyDef;		///< PhysicsComponents Box2D bodyDef
		b2FixtureDef _FixDef;	///< PhysicsComponents Box2D fixDef
		b2MassData mMass;		///< PhysicsComponents Mass data
		bool mInitialized;
	};
}