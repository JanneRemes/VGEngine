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
			static b2World* getWorld();
			static b2World* world;

			/**
			Create new physics world with gravity
			*/
			PhysicsSystem(Vector2<float> gravity, bool borders = false);
			~PhysicsSystem();
			void update(std::vector<GameObject*> *gameObjects, float deltaTime);
		private:
			void createBorders();
			b2JointDef jointDefinition;
		};
}