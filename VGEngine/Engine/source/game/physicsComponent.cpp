#include "engine\game\physicsComponent.h"

using namespace vg;
float PhysicsComponent::scale = 6.0f;
PhysicsComponent::PhysicsComponent(TransformComponent *component, BODYTYPE type, b2World *world)
{

}

Vector2<float> PhysicsComponent::getPosition()
{
	return Vector2<float>(_body->GetPosition().x, _body->GetPosition().y);
}

float PhysicsComponent::getRotation()
{
	return _body->GetAngle();
}

void PhysicsComponent::setVelocity(Vector2<float> velocity)
{
	_body->SetLinearVelocity(b2Vec2(velocity.getX(), velocity.getY()));
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