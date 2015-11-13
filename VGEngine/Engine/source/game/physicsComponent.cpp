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

void PhysicsComponent::setVelocity(Vector2<float> velocity)
{
	if (mInitialized)
		_body->SetLinearVelocity(b2Vec2(velocity.getX(), velocity.getY()));
}
void PhysicsComponent::setAngularVelocity(float velocity)
{
	if (mInitialized)
		_body->SetAngularVelocity(velocity);
}

void PhysicsComponent::applyForce(Vector2<float> force)
{
	if (mInitialized)
		_body->ApplyForce(b2Vec2(force.getX(), force.getY()), _body->GetWorldCenter(), true);
}

void PhysicsComponent::applyLinearImpulse(Vector2<float> force)
{
	if (mInitialized)
		_body->ApplyLinearImpulse(b2Vec2(force.getX(), force.getY()), _body->GetWorldCenter(), true);
}

Vector2<float> PhysicsComponent::getPosition()
{
	if (mInitialized)
		return Vector2<float>(_body->GetPosition().x * scale, _body->GetPosition().y * scale);
	else
		return Vector2<float>(0, 0);
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

void PhysicsComponent::setMassCenter(Vector2<float> position)
{
	if (mInitialized)
		mMass.center = b2Vec2(position.getX(), position.getY());

	_body->SetMassData(&mMass);
}

void PhysicsComponent::setPosition(Vector2<float> position)
{
	if (mInitialized)
		_body->SetTransform(b2Vec2(position.getX() / scale, position.getY() / -scale), _body->GetAngle());
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
