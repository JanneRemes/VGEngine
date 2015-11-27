#include "engine/game/physicsJoint.h"
#include "engine/game/scene.h"
#include "engine/game/game.h"
#include <typeinfo>
#include <vector>

using namespace vg;

Joint::Joint(PhysicsComponent *bodyA, PhysicsComponent *bodyB)
{
	system = Game::getInstance()->getSceneManager()->getActiveScene()->getComponentSystemManager()->getSystem<PhysicsSystem>();
	mBodyA = bodyA->mBody;
	mBodyB = bodyB->mBody;
}

void Joint::createRevoluteJoint()
{
	revoluteDef.bodyA = mBodyA;
	revoluteDef.bodyB = mBodyB;
	revoluteJoint = (b2RevoluteJoint*)system->world->CreateJoint(&revoluteDef);
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
	system->world->DestroyJoint(revoluteJoint);
	revoluteJoint = (b2RevoluteJoint*)system->world->CreateJoint(&revoluteDef);
}

void Joint::removeJoint()
{
	system->world->DestroyJoint(revoluteJoint);
}

Joint::~Joint()
{

}