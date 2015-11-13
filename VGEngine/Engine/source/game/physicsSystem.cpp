
#include "engine/game/physicsSystem.h"
#include "engine/game/physicsPolygonComponent.h"


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

		 }
	 }

	 world->Step(deltaTime, velocityIterations, positionIterations);

	 for (auto it = gameObjects->begin(); it != gameObjects->end(); it++)
	 {
		 PhysicsComponent* physComponent = nullptr;
		 TransformComponent* transform = (*it)->getComponent<TransformComponent>();

		 auto *components = (*it)->getAllComponents();
		 for (std::unordered_map<const std::type_info*, Component*>::iterator ij = components->begin(); ij != components->end(); ij++)
		 {
			 if (dynamic_cast<PhysicsComponent*>(ij->second) != nullptr)
			 {
				 physComponent = dynamic_cast<PhysicsComponent*>(ij->second);
				 break;
			 }
		 }

		 if (physComponent != nullptr && transform != nullptr)
		 {
			 transform->setPosition(Vector2<float>((physComponent->getPosition().getX() ) - transform->getSize().getX() / 2.0f, 
												(-physComponent->getPosition().getY()) - transform->getSize().getY() / 2.0f));
			 transform->setRotation(-1.0f * physComponent->getRotation());
		 }
	 }
}

void PhysicsSystem::createBorders(float x, float y, float width, float height)
{
	b2Vec2 vs[5];
	b2Body *boundaries;

	vs[0].Set(x, y);
	vs[1].Set(x, -height / scale);
	vs[2].Set(width / scale, -height / scale);
	vs[3].Set(width / scale, y);
	vs[4].Set(x, y);
	
	b2ChainShape chain;
	b2BodyDef chainDef;
	b2FixtureDef chainFix;

	chain.CreateChain(vs, 5);
	chainFix.shape = &chain;

	boundaries = world->CreateBody(&chainDef);
	boundaries->CreateFixture(&chainFix);
}

Vector2<float> PhysicsSystem::getGravity()
{
	return Vector2<float>(world->GetGravity().x, world->GetGravity().y);
}

void PhysicsSystem::setGravity(Vector2<float> gravity)
{
	world->SetGravity(b2Vec2(gravity.getX(), gravity.getY()));
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