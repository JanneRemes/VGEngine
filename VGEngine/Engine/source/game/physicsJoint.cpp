#include "engine/game/physicsJoint.h"
#include "engine/game/physicsSystem.h"
#include "engine/game/scene.h"
#include "engine/game/game.h"
#include <typeinfo>
#include <vector>


using namespace vg;

Joint::Joint(PhysicsComponent *bodyA, PhysicsComponent *bodyB)
{
	connected = false;
	PhysicsSystem *system = Game::getInstance()->getSceneManager()->getActiveScene()->getComponentSystemManager()->getSystem<PhysicsSystem>();
	mBodyA = bodyA->mBody;
	mBodyB = bodyB->mBody;
	system->addJoint(this);
}

void Joint::createRevoluteJoint()
{
	PhysicsSystem *system = Game::getInstance()->getSceneManager()->getActiveScene()->getComponentSystemManager()->getSystem<PhysicsSystem>();
	revoluteDef.bodyA = mBodyA;
	revoluteDef.bodyB = mBodyB;
	revoluteJoint = (b2RevoluteJoint*)system->world->CreateJoint(&revoluteDef);
	connected = true;
}

void Joint::setAnchorA(Vec2f pos)
{
	revoluteDef.localAnchorA = b2Vec2(pos.x / PhysicsComponent::scale, pos.y / -PhysicsComponent::scale);
	reCreate();
}

void Joint::setAnchorB(Vec2f pos)
{
	revoluteDef.localAnchorB = b2Vec2(pos.x / PhysicsComponent::scale, pos.y / -PhysicsComponent::scale);
	reCreate();
}

void Joint::enableLimits(float lowerLimit, float upperLimit, bool b)
{
	revoluteDef.enableLimit = b;
	revoluteDef.lowerAngle = lowerLimit * 3.145 / 360;
	revoluteDef.upperAngle = upperLimit * 3.145 / 360;
	reCreate();
}

void Joint::enableLimit(bool b)
{
	revoluteDef.enableLimit = b;
	reCreate();
}

void Joint::reCreate()
{
	PhysicsSystem *system = Game::getInstance()->getSceneManager()->getActiveScene()->getComponentSystemManager()->getSystem<PhysicsSystem>();
	connected = false;
	removeJoint();
	revoluteJoint = (b2RevoluteJoint*)system->world->CreateJoint(&revoluteDef);
	connected = true;
}

void Joint::removeJoint()
{
	PhysicsSystem *system = Game::getInstance()->getSceneManager()->getActiveScene()->getComponentSystemManager()->getSystem<PhysicsSystem>();
	system->removeJoint(revoluteJoint);

	connected = false;
}

Joint::~Joint()
{
	PhysicsSystem *system = Game::getInstance()->getSceneManager()->getActiveScene()->getComponentSystemManager()->getSystem<PhysicsSystem>();
	system->removeJoint(revoluteJoint);
	connected = false;
}