#include <engine\game\physicsPolygonComponent.h>

using namespace vg;
PhysicsPolygonComponent::PhysicsPolygonComponent(TransformComponent *component, b2BodyType type, b2World *world, float width, float height ) : PhysicsComponent(component, type, world)
{
	float _width = 1;
	float _height = 1;
	if (width != 0 && height != 0)
	{
		_width = width;
		_height = height;
	}
	else
	{
		_width = component->getSize().getX();
		_height = component->getSize().getY();
	}

	float x = component->getWorldPosition().getX();
	float y = component->getWorldPosition().getY();
	
	b2BodyDef bodyDef;

	mBoxShape.SetAsBox(_width / scale / 2.0f, _height / scale / 2.0f);

	FixDef.density = 100.0f;
	//FixDef.friction = 0.2f;
	//FixDef.restitution = 5.5f;
	FixDef.shape = &mBoxShape;

	bodyDef.position = b2Vec2(x / scale, -y / scale);
	bodyDef.angle = 0.0f;
	bodyDef.type = type;

	_body = world->CreateBody(&bodyDef);
	_body->CreateFixture(&FixDef);
}
