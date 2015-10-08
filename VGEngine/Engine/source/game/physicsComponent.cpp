#include "engine\game\physicsComponent.h"

using namespace vg;

PhysicsComponent::PhysicsComponent(b2World *world, float x, float y, float width, float height, b2BodyType type)
{
	b2PolygonShape shape;
	b2FixtureDef FixDef;
	b2BodyDef bodyDef;

	shape.SetAsBox(width, height);

	FixDef.density = 10.0f;
	FixDef.friction = 1.0f;
	FixDef.shape = &shape;

	bodyDef.position = b2Vec2(x, -y);
	bodyDef.angle = 0.0f;
	bodyDef.type = type;
	
	_body = world->CreateBody(&bodyDef);
	_body->CreateFixture(&FixDef);

}