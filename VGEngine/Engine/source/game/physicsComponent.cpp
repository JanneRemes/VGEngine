#include "engine\game\physicsComponent.h"
#include "engine\game\physicsSystem.h"
#include "engine\game\scene.h"
#include "engine\game\game.h"

using namespace vg;
float PhysicsComponent::scale = 30.0f;

PhysicsComponent::PhysicsComponent(TransformComponent *component, BODYTYPE type, Vec2f size)
{
	PhysicsSystem *system = Game::getInstance()->getSceneManager()->getActiveScene()->getComponentSystemManager()->getSystem<PhysicsSystem>();

	bodyDef = new b2BodyDef();		///< PhysicsComponents Box2D bodyDef
	_FixDef = new b2FixtureDef();	///< PhysicsComponents Box2D fixDef
	boxShape = new b2PolygonShape();	///< PhysicsComponents Box2D fixDef
	circleShape = new b2CircleShape();		///< PhysicsComponents Box2D bodyDef
	chainShape = new b2ChainShape();		///< PhysicsComponents Box2D bodyDef

		float _width = 1;
		float _height = 1;

		if (size.x != 0 && size.y != 0)
		{
			_width = size.x;
			_height = size.y;
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
			bodyDef->type = b2BodyType::b2_dynamicBody;
		}
		else if (type == KINEMATIC)
		{
			bodyDef->type = b2BodyType::b2_kinematicBody;
		}
		else if (type == STATIC)
		{
			bodyDef->type = b2BodyType::b2_staticBody;
		}

		boxShape->SetAsBox(_width / scale / 2.0f, _height / scale / 2.0f);

		_FixDef->density = 1.0f;
		_FixDef->shape = boxShape;

		bodyDef->position = b2Vec2(x / scale, -y / scale);
		bodyDef->angle = 0.0f;

		_body = system->getWorld()->CreateBody(bodyDef);
		_body->SetGravityScale(5);
		_body->SetTransform(_body->GetPosition(), component->getWorldRotation() * (3.14 / 180));
		_body->CreateFixture(_FixDef);
}

PhysicsComponent::PhysicsComponent(TransformComponent *component, BODYTYPE type, float radius)
{
	PhysicsSystem *system = Game::getInstance()->getSceneManager()->getActiveScene()->getComponentSystemManager()->getSystem<PhysicsSystem>();

	bodyDef = new b2BodyDef();		///< PhysicsComponents Box2D bodyDef
	_FixDef = new b2FixtureDef();	///< PhysicsComponents Box2D fixDef
	boxShape = new b2PolygonShape();	///< PhysicsComponents Box2D fixDef
	circleShape = new b2CircleShape();		///< PhysicsComponents Box2D bodyDef
	chainShape = new b2ChainShape();		///< PhysicsComponents Box2D bodyDef

	float _radius = 0;
	if (radius != 0)
	{
		_radius = radius;
	}
	else
	{
		_radius = component->getSize().x;
	}

	float x = component->getWorldPosition().x;
	float y = component->getWorldPosition().y;

	if (type == DYNAMIC)
	{
		bodyDef->type = b2BodyType::b2_dynamicBody;
	}
	else if (type == KINEMATIC)
	{
		bodyDef->type = b2BodyType::b2_kinematicBody;
	}
	else
		bodyDef->type = b2BodyType::b2_staticBody;

	circleShape->m_radius = ((_radius) / scale) / 2.0f;

	_FixDef->density = 10.0f;
	_FixDef->shape = circleShape;

	bodyDef->position = b2Vec2(x / scale, -y / scale);
	bodyDef->angle = 0.0f;


	_body = system->getWorld()->CreateBody(bodyDef);
	_body->SetGravityScale(2);
	_body->CreateFixture(_FixDef);
}

PhysicsComponent::PhysicsComponent(TransformComponent *component, std::vector<vg::Vec2f> ListOfPoints)
{
	PhysicsSystem *system = Game::getInstance()->getSceneManager()->getActiveScene()->getComponentSystemManager()->getSystem<PhysicsSystem>();

	bodyDef = new b2BodyDef();		///< PhysicsComponents Box2D bodyDef
	_FixDef = new b2FixtureDef();	///< PhysicsComponents Box2D fixDef
	boxShape = new b2PolygonShape();	///< PhysicsComponents Box2D fixDef
	circleShape = new b2CircleShape();		///< PhysicsComponents Box2D bodyDef
	chainShape = new b2ChainShape();		///< PhysicsComponents Box2D bodyDef
	
	bodyDef->type = b2BodyType::b2_staticBody;
	b2Vec2 *vs = new b2Vec2[ListOfPoints.size()];

	for (int i = 0; i < ListOfPoints.size(); i++)
	{
		vs[i].Set(ListOfPoints[i].x / scale, ListOfPoints[i].y / -scale);
	}

	chainShape->CreateChain(vs, ListOfPoints.size());
	_FixDef->shape = chainShape;

	_body = system->world->CreateBody(bodyDef);
	_body->CreateFixture(_FixDef);

	delete vs;
}


PhysicsComponent::~PhysicsComponent()
{
	PhysicsSystem *system = Game::getInstance()->getSceneManager()->getActiveScene()->getComponentSystemManager()->getSystem<PhysicsSystem>();
	system->removeBody(_body);

	delete bodyDef;
	delete _FixDef;
	delete boxShape;
	delete circleShape;
	delete chainShape;
}

void PhysicsComponent::setVelocity(Vec2f velocity)
{
	_body->SetLinearVelocity(b2Vec2(velocity.x, velocity.y));
}

Vec2f PhysicsComponent::getVelocity()
{
	return Vec2f( _body->GetLinearVelocity().x, _body->GetLinearVelocity().y);
}

void PhysicsComponent::setAngularVelocity(float velocity)
{
	_body->SetAngularVelocity(velocity);
}

void PhysicsComponent::applyForce(Vec2f force)
{
	_body->ApplyForce(b2Vec2(force.x, force.y), _body->GetWorldCenter(), true);
}

void PhysicsComponent::applyLinearImpulse(Vec2f force)
{
	_body->ApplyLinearImpulse(b2Vec2(force.x, force.y), _body->GetWorldCenter(), true);
}

Vec2f PhysicsComponent::getPosition()
{
	return Vec2f(_body->GetPosition().x * scale, _body->GetPosition().y * scale);
}

float PhysicsComponent::getRotation()
{
	return (_body->GetAngle() * (180 / 3.14));
}

void PhysicsComponent::setRotation(float rotation)
{
	_body->SetTransform(_body->GetPosition(), rotation * (3.14 / 180 ));
}

void PhysicsComponent::setDensity(float density)
{
	_FixDef->density = density;
	_body->CreateFixture(_FixDef);
}

void PhysicsComponent::setFriction(float friction)
{
	_FixDef->friction = friction;
	_body->CreateFixture(_FixDef);
}

void PhysicsComponent::setRestitution(float restitution)
{
	_FixDef->restitution = restitution;
	_body->CreateFixture(_FixDef);
}

void PhysicsComponent::setMass(float mass)
{
	mMass.mass = mass;
	_body->SetMassData(&mMass);
}

void PhysicsComponent::setMassCenter(Vec2f position)
{
	mMass.center = b2Vec2(position.x, position.y);
	_body->SetMassData(&mMass);
}

void PhysicsComponent::setPosition(Vec2f position)
{
	_body->SetTransform(b2Vec2(position.x / scale, position.y / -scale), _body->GetAngle());
}

void PhysicsComponent::setRotationLock(bool lock)
{
	_body->SetFixedRotation(lock);
}

void PhysicsComponent::setCollisionFilter(FILTER filter)
{
	// The function GetFixureList() returns the first element in a linked list of fixtures
	b2Filter newFilter = _body->GetFixtureList()->GetFilterData();
	newFilter.maskBits = filter;
	_body->GetFixtureList()->SetFilterData(newFilter);
}

void PhysicsComponent::wake(bool sleep)
{
	_body->SetAwake(sleep);
}