
#include "engine/game/physicsSystem.h"

#include <typeinfo>
#include <vector>

#include "engine\game\game.h"
#include "engine\game\scene.h"

using namespace vg;

const float scale = PhysicsComponent::scale;

void ContactListener::BeginContact(b2Contact *contact)
{
	//std::cout << "Contacts are happening" << std::endl;
	PhysicsComponent *component = static_cast<PhysicsComponent*>(contact->GetFixtureA()->GetBody()->GetUserData());
	PhysicsComponent *component2 = static_cast<PhysicsComponent*>(contact->GetFixtureB()->GetBody()->GetUserData());
	if (component != nullptr && component2 != nullptr)
	{
		auto *systemList = Game::getInstance()->getSceneManager()->getActiveScene()->getComponentSystemManager()->getAllSystems();
		for (auto it = systemList->begin(); it != systemList->end(); it++)
		{
			(*it)->onHit(component->getGameObject(), component2->getGameObject());
		}
	}
}

PhysicsSystem::PhysicsSystem(float gravityX, float gravityY)
{
	b2Vec2 *b2Gravity = new b2Vec2(gravityX, gravityY);
	world = new b2World(*b2Gravity);
	world->SetGravity(*b2Gravity);
	world->SetContactListener(new ContactListener());
	timeStep = 1.0f / 60.0f;
}

void PhysicsSystem::addJoint(Joint *joint)
{
	jointList.push_back(joint);
}

PhysicsSystem::~PhysicsSystem()
{
	// delete joints
	for (auto i = jointList.begin(); i != jointList.end(); i++)
	{
		if (!world->IsLocked())
		{
			i = jointList.erase(i);
			if (jointList.size() == 0)
				break;
		}
	}
}

void PhysicsSystem::removeBody(b2Body *body)
{
	bodyRemovalList.push_back(body);
}

void PhysicsSystem::removeJoint(b2Joint *joint)
{
	jointRemovalList.push_back(joint);
}

void PhysicsSystem::update(std::vector<GameObject*> *gameObjects, float deltaTime)
{
	 int velocityIterations = 8;
	 int positionIterations = 3;

	 // delete marked physic bodies from world
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

	 // delete marked physic joints from world
	 for (auto i = jointRemovalList.begin(); i != jointRemovalList.end(); i++)
	 {
		 if (!world->IsLocked())
		 {
			 world->DestroyJoint(*i);
			 i = jointRemovalList.erase(i);
			 if (jointRemovalList.size() == 0)
				 break;
		 }
	 }

	 world->Step(timeStep, velocityIterations, positionIterations);

	 for (auto it = gameObjects->begin(); it != gameObjects->end(); it++)
	 {
		 PhysicsComponent* physComponent = (*it)->get<PhysicsComponent>();
		 TransformComponent* transform = (*it)->getComponent<TransformComponent>();

		 if (physComponent != nullptr && transform != nullptr)
		 {
			 transform->setPosition(Vec2f(physComponent->getPosition().x, -physComponent->getPosition().y));
			 transform->setRotation(physComponent->getRotation());
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

void PhysicsSystem::setTimeStep(float step)
{
	timeStep = step;
}

float PhysicsSystem::getTimeStep()
{
	return timeStep;
}