#include "engine\game\physicsComponent.h"

using namespace vg;
float PhysicsComponent::scale = 6.0f;
PhysicsComponent::PhysicsComponent(TransformComponent *component, b2BodyType type, b2World *world, SHAPE shape)
{
	if (shape == BOX)
	{
		float width = component->getSize().getX();
		float height = component->getSize().getY();
		float x = component->getWorldPosition().getX();
		float y = component->getWorldPosition().getY();

		b2PolygonShape shape;
		b2BodyDef bodyDef;

		shape.SetAsBox(width / scale / 2.0f, height / scale / 2.0f);

		FixDef.density = 100.0f;
		//FixDef.friction = 0.2f;
		//FixDef.restitution = 5.5f;
		FixDef.shape = &shape;

		bodyDef.position = b2Vec2(x / scale, -y / scale);
		bodyDef.angle = 0.0f;
		bodyDef.type = type;

		_body = world->CreateBody(&bodyDef);
		_body->CreateFixture(&FixDef);
	}

	if (shape == CIRCLE)
	{
		float width = component->getSize().getX();
		float x = component->getWorldPosition().getX();
		float y = component->getWorldPosition().getY();

		b2BodyDef bodyDef;

		b2CircleShape circle;
		circle.m_radius = ((width) / scale) / 2.0f;

		FixDef.density = 100.0f;
		//FixDef.friction = 0.2f;
		//FixDef.restitution = 5.5f;
		FixDef.shape = &circle;

		bodyDef.position = b2Vec2(x / scale, -y / scale);
		bodyDef.angle = 0.0f;
		bodyDef.type = type;

		_body = world->CreateBody(&bodyDef);
		_body->CreateFixture(&FixDef);
	}
}
