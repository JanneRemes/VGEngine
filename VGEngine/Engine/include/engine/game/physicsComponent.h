
#pragma once

#include "engine/game/component.h"
#include "engine/utility/vec2f.h"
#include <vector>

#include <Box2D\Box2D.h>

namespace vg
{
	//forward declaration
	class TransformComponent;

	class PhysicsComponent : public Component
	{
		friend class Joint;
	public:
		enum BODYSHAPE { BOX, CIRCLE, CUSTOM };	///< physicsComponents body shape
		enum BODYTYPE { STATIC, DYNAMIC, KINEMATIC };	///< physicsComponents body type
		enum FILTER : short { LOW = 0x0001, MIDDLE = 0x0002, HIGH = 0x0004, TOP = 0x0008 };
		
		static float scale;		///< Scale of the object
		
		/**
		Constructor for creating PhysicsComponent
		@param component Desired TransformComponent that you wish to add physicsComponent with
		@param type Can be either 'DYNAMIC', 'KINEMATIC' or 'STATIC', defines the type of the physics object
		*/
		PhysicsComponent(TransformComponent *component, BODYTYPE type, Vec2f size = 0);

		/**
		Circle shapes
		*/
		PhysicsComponent(TransformComponent *component, BODYTYPE type, float radius);

		/** 
		Custom shapes
		*/
		PhysicsComponent(TransformComponent *component, std::vector<vg::Vec2f> ListOfPoints);
		
		~PhysicsComponent();
		
		/**
		Sets Vector2 position for the physicsComponent
		*/
		void setPosition(Vec2f position);

		/**
		@return Returns Vector2 position of the physicsComponent
		*/
		Vec2f getPosition();

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
		void setVelocity(Vec2f velocity);
		Vec2f getVelocity();
		void wake(bool sleep);
		
		/**
		Sets angular velocity
		*/
		void setAngularVelocity(float velocity);

		/**
		Get angular velocity
		*/
		float getAngularVelocity();

		/**
		Applies force for the physicsComponent
		*/
		void applyForce(Vec2f force);


		void applyLinearImpulse(Vec2f force);

		/**
		Sets density for the physicsComponent
		*/
		void setDensity(float density);

		/**
		Sets angular damping for the physicsComponent
		*/
		void setAngularDamping(float damping);
		
		/**
		Sets linear damping for the physicsComponent
		*/
		void setLinearDamping(float damping);

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
		void setMassCenter(Vec2f position);

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
		b2Body* mBody;				///< PhysicsComponents Box2D body
		b2BodyDef mBodyDef;			///< PhysicsComponents Box2D bodyDef
		b2FixtureDef mFixDef;		///< PhysicsComponents Box2D fixDef
		b2PolygonShape mBoxShape;	///< PhysicsComponents Box2D bodyDef
		b2CircleShape mCircleShape;	///< PhysicsComponents Box2D bodyDef
		b2ChainShape mChainShape;	///< PhysicsComponents Box2D bodyDef
		b2MassData mMass;			///< PhysicsComponents Mass data
	};
}