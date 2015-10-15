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
			static b2World* world;
			
			/**
			Create new physics world with gravity
			*/
			PhysicsSystem(float gravityX, float gravityY);
			void createBorders(float x, float y, float width, float height);
			~PhysicsSystem();
			void update(std::vector<GameObject*> *gameObjects, float deltaTime);
		private:
			b2JointDef jointDefinition;
		};
}