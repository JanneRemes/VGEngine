#include <engine\game\physicsCircleComponent.h>

using namespace vg;
PhysicsCircleComponent::PhysicsCircleComponent(TransformComponent *component, BODYTYPE type, b2World *world, float radius) : PhysicsComponent(component, type, world)
{
	float _radius = 0;
	if (radius != 0)
	{
		_radius = radius;
	}
	else
	{
		_radius = component->getSize().getX();
	}

	float x = component->getWorldPosition().getX();
	float y = component->getWorldPosition().getY();

	b2BodyDef bodyDef;

	if (type == DYNAMIC)
	{
		bodyDef.type = b2BodyType::b2_dynamicBody;
	}
	else
		bodyDef.type = b2BodyType::b2_staticBody;

	mCircleShape.m_radius = ((_radius) / scale) / 2.0f;

	_FixDef.density = 100.0f;
	_FixDef.shape = &mCircleShape;

	bodyDef.position = b2Vec2(x / scale, -y / scale);
	bodyDef.angle = 0.0f;

	_body = world->CreateBody(&bodyDef);
	_body->CreateFixture(&_FixDef);
}
