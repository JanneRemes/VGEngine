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
{	 int velocityIterations = 8;
	 int positionIterations = 3;
	 world->Step(deltaTime, velocityIterations, positionIterations);

	 for (auto it = gameObjects->begin(); it != gameObjects->end(); it++)
	 {
		 PhysicsComponent* physComponent = (*it)->getComponent<PhysicsComponent>();
		 TransformComponent* transform = (*it)->getComponent<TransformComponent>();

		 if (physComponent != nullptr && transform != nullptr)
		 {
			 for (int i = 0; i < 60; ++i)
			 {
			  transform->setPosition(Vector2<int>(physComponent->getBody()->GetPosition().x, -physComponent->getBody()->GetPosition().y));
			  transform->setRotation(-1.0f * physComponent->getBody()->GetAngle() * 180 / 3.14);
			  //Log("vgengine", "Box2D X: %f, Y: %f", physComponent->getBody()->GetPosition().x, physComponent->getBody()->GetPosition().y);

			 }
		 }
	 }
}