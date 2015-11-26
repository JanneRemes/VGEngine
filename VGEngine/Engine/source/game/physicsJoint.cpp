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
}

void Joint::setAnchorB(Vec2f pos)
{
	revoluteDef.localAnchorB = b2Vec2(pos.x / PhysicsComponent::scale, pos.y / -PhysicsComponent::scale);
}

void Joint::enableLimit(bool b)
{
	revoluteDef.enableLimit = b;
}

Joint::~Joint()
{

}