#pragma once
#include <Box2D\Box2D.h>
#include <engine\game\component.h>
#include <engine\game\transformComponent.h>
namespace vg
{
	/**
	Class used to create and modify physicsComponents
	*/
	class PhysicsComponent : public Component
	{
		friend class PhysicsSystem;
	public:
		enum BODYTYPE { STATIC, DYNAMIC, KINEMATIC };	///< physicsComponents body type
		static float scale;								///< Scale of the object

		/**
		Constructor for creating PhysicsComponent
		@param component Desired TransformComponent that you wish to add physicsComponent with
		@param type Can be either 'DYNAMIC', 'KINEMATIC' or 'STATIC', defines the type of the physics object
		*/
		PhysicsComponent(TransformComponent *component, BODYTYPE type);

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
		Sets velocity for the physicsComponent that it will move with
		*/
		void setVelocity(Vector2<float> velocity);

		/**
		Applies force for the physicsComponent
		*/
		void applyForce(Vector2<float> force);

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

	protected:
		b2Body *_body;			///< PhysicsComponents Box2D body
		b2BodyDef bodyDef;		///< PhysicsComponents Box2D bodyDef
		b2FixtureDef _FixDef;	///< PhysicsComponents Box2D fixDef
		b2MassData mMass;		///< PhysicsComponents Mass data
	};
}