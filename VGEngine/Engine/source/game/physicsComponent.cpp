#include "engine\game\physicsComponent.h"

using namespace vg;
float PhysicsComponent::scale = 6.0f;
PhysicsComponent::PhysicsComponent(TransformComponent *component, BODYTYPE type)
{

}

void PhysicsComponent::setVelocity(Vector2<float> velocity)
{
	_body->SetLinearVelocity(b2Vec2(velocity.getX(), velocity.getY()));
}

void PhysicsComponent::setForce(Vector2<float> force, Vector2<float> position)
{
	_body->ApplyForce(b2Vec2(force.getX(), force.getY()), b2Vec2(position.getX(), position.getY()), true);
}

Vector2<float> PhysicsComponent::getPosition()
{
	return Vector2<float>(_body->GetPosition().x, _body->GetPosition().y);
}

float PhysicsComponent::getRotation()
{
	return _body->GetAngle();
}

void PhysicsComponent::setDensity(float density)
{
	_FixDef.density = density;
}

void PhysicsComponent::setFriction(float friction)
{
	_FixDef.friction = friction;
}

void PhysicsComponent::setRestitution(float restitution)
{
	_FixDef.restitution = restitution;
}

void PhysicsComponent::setMass(float mass)
{
	mMass.mass = mass;
}

void PhysicsComponent::setMassCenter(Vector2<float> position)
{
	mMass.center = b2Vec2(position.getX(), position.getY());
}

void PhysicsComponent::setPosition(Vector2<float> position)
{
	//_body->SetTransform(b2Vec2(position.getX(), position.getY()), _body->GetAngle());
	_body->ApplyLinearImpulse(b2Vec2(10000, 10000), b2Vec2(position.getX(), position.getY()), true);
}