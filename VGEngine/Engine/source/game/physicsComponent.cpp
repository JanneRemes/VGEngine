#include "engine\game\physicsComponent.h"
#include "engine\game\physicsSystem.h"
#include "engine\game\scene.h"
#include "engine\game\game.h"

using namespace vg;
float PhysicsComponent::scale = 30.0f;
PhysicsComponent::PhysicsComponent(TransformComponent *component, BODYTYPE type)
{
	mInitialized = false;
}

PhysicsComponent::~PhysicsComponent()
{
	PhysicsSystem *system = Game::getInstance()->getSceneManager()->getActiveScene()->getComponentSystemManager()->getSystem<PhysicsSystem>();
	system->removeBody(_body);
}

void PhysicsComponent::setVelocity(Vec2f velocity)
{
	if (mInitialized)
		_body->SetLinearVelocity(b2Vec2(velocity.x, velocity.y));
}

Vec2f PhysicsComponent::getVelocity()
{
	if (mInitialized)
		return Vec2f( _body->GetLinearVelocity().x, _body->GetLinearVelocity().y);
}

void PhysicsComponent::setAngularVelocity(float velocity)
{
	if (mInitialized)
		_body->SetAngularVelocity(velocity);
}

void PhysicsComponent::applyForce(Vec2f force)
{
	if (mInitialized)
		_body->ApplyForce(b2Vec2(force.x, force.y), _body->GetWorldCenter(), true);
}

void PhysicsComponent::applyLinearImpulse(Vec2f force)
{
	if (mInitialized)
		_body->ApplyLinearImpulse(b2Vec2(force.x, force.y), _body->GetWorldCenter(), true);
}

Vec2f PhysicsComponent::getPosition()
{
	if (mInitialized)
		return Vec2f(_body->GetPosition().x * scale, _body->GetPosition().y * scale);
	else
		return Vec2f(0, 0);
}

float PhysicsComponent::getRotation()
{
	if (mInitialized)
		return (_body->GetAngle() * (180 / 3.14)) ;
	else 
		return 0.0f;
}

void PhysicsComponent::setRotation(float rotation)
{
	if (mInitialized)
		_body->SetTransform(_body->GetPosition(), rotation * (3.14 / 180 ));
}

void PhysicsComponent::setDensity(float density)
{
	if (mInitialized)
		_FixDef.density = density;

	_body->CreateFixture(&_FixDef);
}

void PhysicsComponent::setFriction(float friction)
{
	if (mInitialized)
		_FixDef.friction = friction;

	_body->CreateFixture(&_FixDef);
}

void PhysicsComponent::setRestitution(float restitution)
{
	if (mInitialized)
		_FixDef.restitution = restitution;

	_body->CreateFixture(&_FixDef);
}

void PhysicsComponent::setMass(float mass)
{
	if (mInitialized)
		mMass.mass = mass;

	_body->SetMassData(&mMass);
}

void PhysicsComponent::setMassCenter(Vec2f position)
{
	if (mInitialized)
		mMass.center = b2Vec2(position.x, position.y);

	_body->SetMassData(&mMass);
}

void PhysicsComponent::setPosition(Vec2f position)
{
	if (mInitialized)
		_body->SetTransform(b2Vec2(position.x / scale, position.y / -scale), _body->GetAngle());
}

void PhysicsComponent::setRotationLock(bool lock)
{
	if (mInitialized)
		_body->SetFixedRotation(lock);
}

void PhysicsComponent::setCollisionFilter(FILTER filter)
{
	if (mInitialized)
	{
		// The function GetFixureList() returns the first element in a linked list of fixtures
		b2Filter newFilter = _body->GetFixtureList()->GetFilterData();		
		newFilter.maskBits = filter;
		_body->GetFixtureList()->SetFilterData(newFilter);
	}
}
