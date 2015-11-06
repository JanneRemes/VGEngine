#include "engine\game\physicsComponent.h"

using namespace vg;
float PhysicsComponent::scale = 30.0f;
PhysicsComponent::PhysicsComponent(TransformComponent *component, BODYTYPE type)
{
	mInitialized = false;
}

void PhysicsComponent::setVelocity(Vector2<float> velocity)
{
	if (mInitialized)
		_body->SetLinearVelocity(b2Vec2(velocity.getX(), -velocity.getY()));
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
		return _body->GetAngle();
	else 
		return 0.0f;
}

void PhysicsComponent::setDensity(float density)
{
	if (mInitialized)
		_FixDef.density = density;
}

void PhysicsComponent::setFriction(float friction)
{
	if (mInitialized)
		_FixDef.friction = friction;
}

void PhysicsComponent::setRestitution(float restitution)
{
	if (mInitialized)
		_FixDef.restitution = restitution;
}

void PhysicsComponent::setMass(float mass)
{
	if (mInitialized)
		mMass.mass = mass;
}

void PhysicsComponent::setMassCenter(Vector2<float> position)
{
	if (mInitialized)
		mMass.center = b2Vec2(position.getX() / scale, position.getY() / -scale);
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