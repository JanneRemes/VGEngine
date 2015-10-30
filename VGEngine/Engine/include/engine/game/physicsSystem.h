#pragma once
#include "Box2D\Box2D.h"
#include "engine/game/system.h"
#include "engine\utility\Vector2.h"
#include "engine\game\transformComponent.h"
#include "engine\game\physicsComponent.h"

namespace vg
{
	/**
	Class used to updating and creating physics
	*/
	class PhysicsSystem : public System
	{
		friend class PhysicsComponent;
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

		/**
		Creates borders for chainable objects
		*/
		void createBorders(float x, float y, float width, float height);

		/**
		Creates joint between two physicsComponent bodies
		@param bodyA One of the two bodies that will be jointed together
		@param bodyB second of the two bodies that will be jointed together
		*/
		void createJoint(PhysicsComponent *bodyA, PhysicsComponent *bodyB);

		/**
		Sets gravity for the physics world
		@param gravity Vector2 gravity for the world
		*/
		void setGravity(Vector2<float> gravity);

		/**
		@return Returns worlds gravity value
		*/
		Vector2<float> getGravity();

		/**
		@return Returns the physics world
		*/
		b2World* getWorld() { return world; };

	private:
		b2World* world; ///< Physics world
	};
}