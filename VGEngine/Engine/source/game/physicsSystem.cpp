
#include "engine/game/physicsSystem.h"


#include <typeinfo>
#include <vector>

using namespace vg;

float scale = PhysicsComponent::scale;

PhysicsSystem::PhysicsSystem(float gravityX, float gravityY)
{
	b2Vec2 *b2Gravity = new b2Vec2(gravityX, gravityY);
	world = new b2World(*b2Gravity);
	world->SetGravity(*b2Gravity);
}

PhysicsSystem::~PhysicsSystem()
{

}

void PhysicsSystem::removeBody(b2Body *body)
{
	bodyRemovalList.push_back(body);
}


void PhysicsSystem::update(std::vector<GameObject*> *gameObjects, float deltaTime)
{
	 int velocityIterations = 8;
	 int positionIterations = 3;

	 // delete marked physic bodies
	 for (auto i = bodyRemovalList.begin(); i != bodyRemovalList.end(); i++)
	 {
		 if (!world->IsLocked())
		 {
			 world->DestroyBody(*i);
			 i = bodyRemovalList.erase(i);
			 if (bodyRemovalList.size() == 0)
				break;
		 }
	 }

	 world->Step(deltaTime, velocityIterations, positionIterations);

	 for (auto it = gameObjects->begin(); it != gameObjects->end(); it++)
	 {
		 PhysicsComponent* physComponent = (*it)->get<PhysicsComponent>();
		 TransformComponent* transform = (*it)->getComponent<TransformComponent>();

		 if (physComponent != nullptr && transform != nullptr)
		 {
			 transform->setPosition(Vec2f((physComponent->getPosition().x ) - transform->getSize().x / 2.0f, 
				(-physComponent->getPosition().y) - transform->getSize().y / 2.0f));
			 transform->setRotation(-1.0f * physComponent->getRotation());
		 }
	 }
}

void PhysicsSystem::createBorders(float x, float y, float width, float height)
{
	b2Vec2 vs[5];
	b2Body *boundaries;

	vs[0].Set(x / scale, y / -scale);
	vs[1].Set(x / scale, -height / scale);
	vs[2].Set(width / scale, -height / scale);
	vs[3].Set(width / scale, y / -scale);
	vs[4].Set(x / -scale, y / -scale);
	
	b2ChainShape chain;
	b2BodyDef chainDef;
	b2FixtureDef chainFix;

	chain.CreateChain(vs, 5);
	chainFix.shape = &chain;

	boundaries = world->CreateBody(&chainDef);
	boundaries->CreateFixture(&chainFix);
}

Vec2f PhysicsSystem::getGravity()
{
	return Vec2f(world->GetGravity().x, world->GetGravity().y);
}

void PhysicsSystem::setGravity(Vec2f gravity)
{
	world->SetGravity(b2Vec2(gravity.x, gravity.y));
}

void PhysicsSystem::createRevoluteJoint(PhysicsComponent *bodyA, PhysicsComponent *bodyB)
{
	b2RevoluteJointDef jointDef;
	
	jointDef.bodyA = bodyA->_body;
	jointDef.bodyB = bodyB->_body;
	jointDef.localAnchorA = b2Vec2(bodyA->_body->GetLocalCenter().x + 64 / scale, bodyA->_body->GetLocalCenter().y + 64 / -scale);
	jointDef.localAnchorB = bodyB->_body->GetLocalCenter();

	b2RevoluteJoint* joint = (b2RevoluteJoint*)world->CreateJoint(&jointDef);
}

void PhysicsSystem::createRopeJoint(PhysicsComponent *bodyA, PhysicsComponent *bodyB)
{
	b2RopeJointDef jointDef;

	jointDef.bodyA = bodyA->_body;
	jointDef.bodyB = bodyB->_body;
	jointDef.maxLength = 10;

	b2RopeJoint* joint = (b2RopeJoint*)world->CreateJoint(&jointDef);
} 