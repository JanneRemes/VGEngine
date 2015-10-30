#pragma once
#include "Box2D\Box2D.h"
#include "engine/game/system.h"
#include "engine\utility\Vector2.h"
#include "engine\game\transformComponent.h"
#include "engine\game\physicsComponent.h"

namespace vg
{
		class PhysicsSystem : public System
		{
			friend class PhysicsComponent;
		public:
			
			/**
			Create new physics world with gravity
			*/
			PhysicsSystem(float gravityX, float gravityY);
			~PhysicsSystem();
			void update(std::vector<GameObject*> *gameObjects, float deltaTime);

			void createBorders(float x, float y, float width, float height);
			void createJoint(PhysicsComponent *bodyA, PhysicsComponent *bodyB);

			void setGravity(Vector2<float> gravity);
			Vector2<float> getGravity();

			b2World* getWorld() { return world; };

		private:
			b2World* world;
		};
}