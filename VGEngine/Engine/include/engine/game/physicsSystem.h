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
			PhysicsSystem(Vector2<float> gravity);
			~PhysicsSystem();
			void update(std::vector<GameObject*> *gameObjects, float deltaTime);
			//void createJoint(b2Body bodyA, b2Body bodyB);
			//void setGravity(b2Vec2 gravity);
			b2World* getWorld() { return world; };
		private:
			b2World *world;
		};
}