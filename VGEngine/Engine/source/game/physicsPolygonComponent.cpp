
#include "engine/game/physicsPolygonComponent.h"
#include "engine/game/game.h"
#include "engine/game/physicsSystem.h"
#include "engine/game/scene.h"

using namespace vg;

PhysicsPolygonComponent::PhysicsPolygonComponent(TransformComponent *component, BODYTYPE type, float width, float height) : PhysicsComponent(component, type)
{
	PhysicsSystem *system = Game::getInstance()->getSceneManager()->getActiveScene()->getComponentSystemManager()->getSystem<PhysicsSystem>();

	float _width = 1;
	float _height = 1;

	if (width != 0 && height != 0)
	{
		_width = width;
		_height = height;
	}
	else
	{
		_width = component->getSize().x;
		_height = component->getSize().y;
	}

	float x = component->getWorldPosition().x - component->getOrigin().x;
	float y = component->getWorldPosition().y - component->getOrigin().y;
	

	if (type == DYNAMIC)
	{
		bodyDef.type = b2BodyType::b2_dynamicBody;
	}
	else if (type == KINEMATIC)
	{
		bodyDef.type = b2BodyType::b2_kinematicBody;
	}
	else if (type == STATIC)
	{
		bodyDef.type = b2BodyType::b2_staticBody;
	}

	mBoxShape.SetAsBox(_width / scale / 2.0f, _height / scale / 2.0f);
	
	_FixDef.density = 1.0f;
	_FixDef.shape = &mBoxShape;

	bodyDef.position = b2Vec2(x / scale, -y / scale);
	bodyDef.angle = 0.0f;

	_body = system->getWorld()->CreateBody(&bodyDef);
	_body->SetGravityScale(5);
	_body->SetTransform(_body->GetPosition(), component->getWorldRotation() * (3.14 / 180));
	_body->CreateFixture(&_FixDef);
	mInitialized = true;
}
