#include "engine\game\physicsComponent.h"

using namespace vg;

PhysicsComponent::PhysicsComponent(b2World world)
{
	b2BodyDef bodyDef;
	b2PolygonShape shape;
	_body = world.CreateBody(&bodyDef);
	_body->CreateFixture(&shape, 10.0f);
}