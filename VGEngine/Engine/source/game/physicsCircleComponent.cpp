#include <engine\game\physicsCircleComponent.h>
#include "engine\game\game.h"
#include "engine\game\physicsSystem.h"
#include "engine\game\scene.h"
using namespace vg;
PhysicsCircleComponent::PhysicsCircleComponent(TransformComponent *component, BODYTYPE type, float radius) : PhysicsComponent(component, type)
{
	PhysicsSystem *system = Game::getInstance()->getSceneManager()->getActiveScene()->getComponentSystemManager()->getSystem<PhysicsSystem>();

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

	_body = system->world->CreateBody(&bodyDef);
	_body->CreateFixture(&_FixDef);

}
