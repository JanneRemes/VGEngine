#include <engine\game\physicsSystem.h>
#include "engine\game\physicsComponent.h"
#include <typeinfo>
#include <vector>
using namespace vg;

PhysicsSystem::PhysicsSystem(Vector2<float> gravity)
{
	b2Vec2 b2Gravity(gravity.getX(), gravity.getY());
	world = new b2World(b2Gravity);
}

PhysicsSystem::~PhysicsSystem()
{

}

void PhysicsSystem::update(std::vector<GameObject*> *gameObjects, float deltaTime)
{
	 float timeStep = 1.0f / 60.0f;	 int velocityIterations = 8;
	 int positionIterations = 3;
	 for (auto it = gameObjects->begin(); it != gameObjects->end(); it++)
	 {
		 PhysicsComponent* physComponent = (*it)->getComponent<PhysicsComponent>();
		 TransformComponent* transform = (*it)->getComponent<TransformComponent>();

		 if (physComponent != nullptr && transform != nullptr)
		 {
			 for (int i = 0; i < 60; ++i)
			 {
			  world->Step(timeStep, velocityIterations, positionIterations);
			  transform->setPosition(Vector2<int>(physComponent->getBody()->GetPosition().x, physComponent->getBody()->GetPosition().y));
			  //float angle = body->GetAngle();
			 }
		 }
	 }
}