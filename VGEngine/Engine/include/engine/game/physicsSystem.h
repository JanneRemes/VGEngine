#pragma once
#include "Box2D\Box2D.h"
#include "engine/game/system.h"
#include "engine\utility\Vector2.h"
#include  "engine\game\transformComponent.h"

namespace vg
{
		class PhysicsSystem : public System
		{
		public:
			/**
			Create new physics world with gravity
			*/
			static b2World* getWorld();
			static b2World* world;
			PhysicsSystem(Vector2<float> gravity, bool borders = false);
			~PhysicsSystem();
			void update(std::vector<GameObject*> *gameObjects, float deltaTime);
			//void createJoint(b2Body bodyA, b2Body bodyB);
			//void setGravity(b2Vec2 gravity);
			//b2World* getWorld() { return world; };
		private:
			void createBorders();
			//b2World *world;
		};
}