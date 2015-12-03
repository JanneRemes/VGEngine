#pragma once
#include "Box2D\Box2D.h"
#include "engine/game/system.h"
#include "engine/utility/vec2f.h"
#include "engine\game\transformComponent.h"
#include "engine\game\physicsComponent.h"
namespace vg
{
	class ContactListener : public b2ContactListener
	{
		void BeginContact(b2Contact *contact);
	};

	class PhysicsSystem : public System
	{
		friend class PhysicsComponent;
		friend class Joint;
	public:

		/**
		Create new physics world with gravity
		@param gravityX X-axel gravitation
		@param gravityY Y-axel gravitation
		*/
		PhysicsSystem(float gravityX, float gravityY);
		~PhysicsSystem();

		/**
		Updates gameobjects with physicsComponents
		@param gameObjects Vector that contains updateable gameObjects
		*/
		void update(std::vector<GameObject*> *gameObjects, float deltaTime);
		void removeBody(b2Body *body);
		void removeJoint(b2Joint *joint);
		/**
		Creates borders for chainable objects
		*/
		void createBorders(float x, float y, float width, float height);

		/**
		Creates joint between two physicsComponent bodies
		@param bodyA One of the two bodies that will be jointed together
		@param bodyB second of the two bodies that will be jointed together
		*/
		//void createRevoluteJoint(PhysicsComponent *bodyA, PhysicsComponent *bodyB);
		//void createRopeJoint(PhysicsComponent *bodyA, PhysicsComponent *bodyB);
		
		/**
		Sets gravity for the physics world
		@param gravity Vector2 gravity for the world
		*/
		void setGravity(Vec2f gravity);

		/**
		@return Returns worlds gravity value
		*/
		Vec2f getGravity();

		/**
		@return Returns the physics world
		*/
		b2World* getWorld() { return world; };

	protected:
		b2World* world;		///< Physics world
		std::vector<b2Body*> bodyRemovalList;
		std::vector<b2Joint*> jointRemovalList;
	};
}