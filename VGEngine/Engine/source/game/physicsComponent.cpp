
#include "engine/game/physicsComponent.h"
#include "engine/game/physicsSystem.h"
#include "engine/game/scene.h"
#include "engine/game/game.h"
#include "engine/utility/math.h"

using namespace vg;
float PhysicsComponent::scale = 30.0f;

PhysicsComponent::PhysicsComponent(TransformComponent *component, BODYTYPE type, Vec2f size): Component()
{
	PhysicsSystem *system = Game::getInstance()->getSceneManager()->getActiveScene()->getComponentSystemManager()->getSystem<PhysicsSystem>();

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

	float x = component->getWorldPosition().x;
	float y = component->getWorldPosition().y;


	if (type == DYNAMIC)
	{
		mBodyDef.type = b2BodyType::b2_dynamicBody;
	}
	else if (type == KINEMATIC)
	{
		mBodyDef.type = b2BodyType::b2_kinematicBody;
	}
	else if (type == STATIC)
	{
		mBodyDef.type = b2BodyType::b2_staticBody;
	}

	Vec2f origin = component->getSize();
	origin *= 0.5f;
	component->setOrigin(origin);
	mBoxShape.SetAsBox(_width / scale / 2.0f, _height / scale / 2.0f);

	mFixDef.density = 1.0f;
	mFixDef.shape = &mBoxShape;

	mBodyDef.position = b2Vec2(x / scale, -y / scale);
	mBodyDef.angle = 0.0f;

	mBody = system->getWorld()->CreateBody(&mBodyDef);
	mBody->SetUserData(static_cast<void*>(this));
	mBody->SetGravityScale(5);
	mBody->SetTransform(mBody->GetPosition(), Math::degreesToRadians(-component->getWorldRotation()));
	mFixture = mBody->CreateFixture(&mFixDef);

	mBodyShape = BODYSHAPE::BOX;
}

PhysicsComponent::PhysicsComponent(TransformComponent *component, BODYTYPE type, float radius)
{
	PhysicsSystem *system = Game::getInstance()->getSceneManager()->getActiveScene()->getComponentSystemManager()->getSystem<PhysicsSystem>();
	Vec2f origin = component->getSize();
	origin *= 0.5f;
	component->setOrigin(origin);

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
		mBodyDef.type = b2BodyType::b2_dynamicBody;
	}
	else if (type == KINEMATIC)
	{
		mBodyDef.type = b2BodyType::b2_kinematicBody;
	}
	else
		mBodyDef.type = b2BodyType::b2_staticBody;

	mCircleShape.m_radius = ((_radius) / scale) / 2.0f;

	mFixDef.density = 10.0f;
	mFixDef.shape = &mCircleShape;

	mBodyDef.position = b2Vec2(x / scale, -y / scale);
	mBodyDef.angle = 0.0f;


	mBody = system->getWorld()->CreateBody(&mBodyDef);
	mBody->SetUserData(static_cast<void*>(this));
	mBody->SetGravityScale(2);
	mFixture = mBody->CreateFixture(&mFixDef);

	mBodyShape = BODYSHAPE::CIRCLE;
}

PhysicsComponent::PhysicsComponent(TransformComponent *component, std::vector<vg::Vec2f> ListOfPoints)
{
	PhysicsSystem *system = Game::getInstance()->getSceneManager()->getActiveScene()->getComponentSystemManager()->getSystem<PhysicsSystem>();
	
	mBodyDef.type = b2BodyType::b2_staticBody;
	b2Vec2 *vs = new b2Vec2[ListOfPoints.size()];

	for (int i = 0; i < ListOfPoints.size(); i++)
	{
		vs[i].Set(ListOfPoints[i].x / scale, ListOfPoints[i].y / -scale);
	}

	mChainShape.CreateChain(vs, ListOfPoints.size());
	mFixDef.shape = &mChainShape;

	mBody = system->world->CreateBody(&mBodyDef);
	mBody->SetUserData(static_cast<void*>(this));
	mFixture = mBody->CreateFixture(&mFixDef);

	delete vs;
	mBodyShape = BODYSHAPE::CUSTOM;
}

PhysicsComponent::~PhysicsComponent()
{
	PhysicsSystem *system = Game::getInstance()->getSceneManager()->getActiveScene()->getComponentSystemManager()->getSystem<PhysicsSystem>();
	system->removeBody(mBody);
}

void PhysicsComponent::setVelocity(Vec2f velocity)
{
	mBody->SetLinearVelocity(b2Vec2(velocity.x, velocity.y));
}

Vec2f PhysicsComponent::getVelocity()
{
	return Vec2f( mBody->GetLinearVelocity().x, mBody->GetLinearVelocity().y);
}

void PhysicsComponent::setAngularVelocity(float velocity)
{
	mBody->SetAngularVelocity(velocity);
}

float PhysicsComponent::getAngularVelocity()
{
	return mBody->GetAngularVelocity();
}

void PhysicsComponent::applyForce(Vec2f force)
{
	mBody->ApplyForce(b2Vec2(force.x, force.y), mBody->GetWorldCenter(), true);
}

void PhysicsComponent::applyLinearImpulse(Vec2f force)
{
	mBody->ApplyLinearImpulse(b2Vec2(force.x, force.y), mBody->GetWorldCenter(), true);
}

Vec2f PhysicsComponent::getPosition()
{
	return Vec2f(mBody->GetPosition().x * scale, mBody->GetPosition().y * scale);
}

float PhysicsComponent::getRotation()
{
	return -(Math::radianToDegrees(mBody->GetTransform().q.GetAngle()));
}

void PhysicsComponent::setRotation(float rotation)
{
	mBody->SetTransform(mBody->GetPosition(), Math::degreesToRadians(-rotation));
}

void PhysicsComponent::setDensity(float density)
{
	//mFixture->SetDensity(density);
	//mFixture = mBody->CreateFixture(&mFixDef);
	mFixDef.density = density;
	mBody->DestroyFixture(mFixture);
	mFixture = mBody->CreateFixture(&mFixDef);
}

void PhysicsComponent::setFriction(float friction)
{
	//mFixture->SetFriction(friction);
	//mFixture = mBody->CreateFixture(&mFixDef);
	mFixDef.friction = friction;
	mBody->DestroyFixture(mFixture);
	mFixture = mBody->CreateFixture(&mFixDef);
}

void PhysicsComponent::setRestitution(float restitution)
{
	//mFixture->SetRestitution(restitution);
	//mFixture = mBody->CreateFixture(&mFixDef);
	mFixDef.restitution = restitution;
	mBody->DestroyFixture(mFixture);
	mFixture = mBody->CreateFixture(&mFixDef);
}

void PhysicsComponent::setAngularDamping(float damping)
{
	mBody->SetAngularDamping(damping);
}

void PhysicsComponent::setLinearDamping(float damping)
{
	mBody->SetLinearDamping(damping);
}

void PhysicsComponent::setMass(float mass)
{
	mMass.mass = mass;
	mBody->SetMassData(&mMass);
}

void PhysicsComponent::setMassCenter(Vec2f position)
{
	mMass.center = b2Vec2(position.x, position.y);
	mBody->SetMassData(&mMass);
}

void PhysicsComponent::setPosition(Vec2f position)
{
	mBody->SetTransform(b2Vec2(position.x / scale, position.y / -scale), mBody->GetAngle());
}

void PhysicsComponent::setRotationLock(bool lock)
{
	mBody->SetFixedRotation(lock);
}

void PhysicsComponent::setCollisionFilter(FILTER filter)
{
	// The function GetFixureList() returns the first element in a linked list of fixtures
	b2Filter newFilter = mBody->GetFixtureList()->GetFilterData();
	newFilter.maskBits = filter;
	mBody->GetFixtureList()->SetFilterData(newFilter);
}

void PhysicsComponent::wake(bool sleep)
{
	mBody->SetAwake(sleep);
}

PhysicsComponent::BODYSHAPE PhysicsComponent::getBodyShape()
{
	return mBodyShape;
}

float PhysicsComponent::getScale()
{
	return scale;
}
