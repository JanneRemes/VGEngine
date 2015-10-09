#include <engine\game\physicsSystem.h>
#include "engine\game\physicsComponent.h"
#include "engine\game.h"
#include <typeinfo>
#include <vector>
using namespace vg;

b2World *PhysicsSystem::world = nullptr;
b2World* PhysicsSystem::getWorld()
{
	return world;
}

PhysicsSystem::PhysicsSystem(Vector2<float> gravity, bool borders)
{
	b2Vec2 b2Gravity(gravity.getX(), gravity.getY());
	world = new b2World(b2Gravity);
	
	if (borders)
	{
		createBorders();
	}
}

PhysicsSystem::~PhysicsSystem()
{

}

void PhysicsSystem::update(std::vector<GameObject*> *gameObjects, float deltaTime)
{	 int velocityIterations = 8;
	 int positionIterations = 3;
	 world->Step(deltaTime * 4, velocityIterations, positionIterations);

	 for (auto it = gameObjects->begin(); it != gameObjects->end(); it++)
	 {
		 PhysicsComponent* physComponent = (*it)->getComponent<PhysicsComponent>();
		 TransformComponent* transform = (*it)->getComponent<TransformComponent>();

		 if (physComponent != nullptr && transform != nullptr)
		 {
			 for (int i = 0; i < 60; ++i)
			 {
			  transform->setPosition(Vector2<int>(physComponent->getBody()->GetPosition().x , -physComponent->getBody()->GetPosition().y));
			  transform->setRotation(-1.0f * physComponent->getBody()->GetAngle() * 180 / 3.14);
			  //Log("vgengine", "Box2D X: %f, Y: %f", physComponent->getBody()->GetPosition().x, physComponent->getBody()->GetPosition().y);

			 }
		 }
	 }
}

void PhysicsSystem::createBorders()
{
	b2PolygonShape shapeHorizontal;
	b2PolygonShape shapeVertical;

	shapeHorizontal.SetAsBox(Game::getInstance()->getGraphics()->getScreenWidth(), 64);
	shapeVertical.SetAsBox(64, Game::getInstance()->getGraphics()->getScreenHeight());

	b2BodyDef bodyDef1;
	b2BodyDef bodyDef2;
	b2BodyDef bodyDef3;
	b2BodyDef bodyDef4;

	b2FixtureDef FixDef1;
	b2FixtureDef FixDef2;
	b2FixtureDef FixDef3;
	b2FixtureDef FixDef4;

	FixDef1.density = 10.0f;
	FixDef1.friction = 1.0f;
	FixDef1.restitution = 5.0f;
	FixDef1.shape = &shapeHorizontal;

	FixDef2.density = 10.0f;
	FixDef2.friction = 1.0f;
	FixDef2.restitution = 5.0f;
	FixDef2.shape = &shapeHorizontal;

	FixDef3.density = 10.0f;
	FixDef3.friction = 1.0f;
	FixDef3.restitution = 5.0f;
	FixDef3.shape = &shapeVertical;

	FixDef4.density = 10.0f;
	FixDef4.friction = 1.0f;
	FixDef4.restitution = 5.0f;
	FixDef4.shape = &shapeVertical;

	bodyDef1.position = b2Vec2(0, 0);
	bodyDef1.angle = 0.0f;
	bodyDef1.type = b2BodyType::b2_staticBody;

	bodyDef2.position = b2Vec2(0, -Game::getInstance()->getGraphics()->getScreenHeight());
	bodyDef2.angle = 0.0f;
	bodyDef2.type = b2BodyType::b2_staticBody;

	bodyDef3.position = b2Vec2(0, 0);
	bodyDef3.angle = 90.0f;
	bodyDef3.type = b2BodyType::b2_staticBody;

	bodyDef4.position = b2Vec2(Game::getInstance()->getGraphics()->getScreenWidth(), 0);
	bodyDef4.angle = 90.0f;
	bodyDef4.type = b2BodyType::b2_staticBody;

	b2Body *_body1;
	b2Body *_body2;
	b2Body *_body3;
	b2Body *_body4;

	_body1 = world->CreateBody(&bodyDef1);
	_body1->CreateFixture(&FixDef1);

	_body2 = world->CreateBody(&bodyDef2);
	_body2->CreateFixture(&FixDef2);

	_body3 = world->CreateBody(&bodyDef3);
	_body3->CreateFixture(&FixDef3);

	_body4 = world->CreateBody(&bodyDef4);
	_body4->CreateFixture(&FixDef4);
}