
#include "systems/jumpSystem.h"

#ifdef OS_WINDOWS
#include "engine/input/mouse.h"
#include "engine\input\keyboard.h"
#endif
#ifdef OS_ANDROID
#include "engine/input/touch.h"
#endif

#include "engine/game/renderComponent.h"
#include "engine/game/game.h"

#include "engine/game/animationComponent.h"
#include "engine/game/animationSystem.h"
#include "engine/utility/random.h"
#include "engine/graphics/screen.h"
#include "engine/utility/timer.h"
#include "engine/graphics/camera.h"

using namespace vg;
using namespace vg::graphics;

JumpSystem::JumpSystem(Scene *scene)
{
	this->scene = scene;
	system = Game::getInstance()->getSceneManager()->getActiveScene()->getComponentSystemManager()->getSystem<PhysicsSystem>();
	
	// Snowboard
	physicsTest = new GameObject("physicsTest1");

	TransformComponent *physicsTransform = new TransformComponent(Vec2f(10, -10),
		Vec2f(64, 8), -45.0f);

	RenderComponent *physicsObject = new RenderComponent("koala.png");
	PhysicsComponent *physicsComponent = new PhysicsComponent(physicsTransform, PhysicsComponent::DYNAMIC);

	physicsTest->addComponent(physicsComponent);
	physicsTest->addComponent(physicsTransform);
	physicsTest->addComponent(physicsObject);
	physicsTest->getComponent<PhysicsComponent>()->setFriction(0.1);

	scene->addGameObject(physicsTest);
	
	// Jumping muumi
	TransformComponent *muumiTransform = new TransformComponent(Vec2f(10, -10),
		Vec2f(64, 64), -45.0f);

	muumiObject = new GameObject("muumiObject");
	muumiObject->addComponent(muumiTransform);
	PhysicsComponent *muumiPhysics = new PhysicsComponent(muumiTransform, PhysicsComponent::DYNAMIC, 54);
	RenderComponent *muumiAnimation = new RenderComponent("papparunSmall2.png");

	muumiObject->addComponent(new AnimationComponent(0.04, 3, 8, 24));
	muumiObject->addComponent(muumiAnimation);
	muumiObject->addComponent(muumiPhysics);

	scene->addGameObject(muumiObject);
	
	muumiJoint = new Joint(muumiPhysics, physicsComponent);
	muumiJoint->createRevoluteJoint();
	
	muumiJoint->setAnchorA(Vec2f(0, 35));
	muumiJoint->enableLimit(true);
}
void JumpSystem::update(std::vector<vg::GameObject*> *gameObjects, float deltaTime)
{
	//Camera::setPosition(Vec2f(physicsTest->getComponent<TransformComponent>()->getWorldPosition().x - Screen::getX() * 0.5, physicsTest->getComponent<TransformComponent>()->getWorldPosition().y - Screen::getY() * 0.5));

	if (physicsTest->getComponent<TransformComponent>()->getWorldPosition().y >= Screen::getY())
	{
		for (auto it = gameObjects->begin(); it != gameObjects->end(); it++)
		{
			if ((*it)->getName().find("physicsTest1") != -1)
			{
				PhysicsComponent* phys = (*it)->get<PhysicsComponent>();
				if (phys != nullptr)
				{
					phys->setPosition(Vec2f(10, -10));
					phys->setAngularVelocity(0);
					phys->setVelocity(Vec2f(0, 0));
					phys->setRotation(-45);

					muumiObject->getComponent<PhysicsComponent>()->setPosition(Vec2f(10, -10));
					muumiObject->getComponent<PhysicsComponent>()->setAngularVelocity(0);
					muumiObject->getComponent<PhysicsComponent>()->setVelocity(Vec2f(0, 0));
					muumiObject->getComponent<PhysicsComponent>()->setRotation(-45);
					muumiObject->getComponent<PhysicsComponent>()->wake(true);
				}
			}
		}
				
	
	}
	
#ifdef OS_WINDOWS
	if (vg::input::Keyboard::getKeyState(vg::input::Keyboard::S) == vg::input::Keyboard::KeyState::PRESSED)
	{
		vg::Vec2f pos = vg::input::Mouse::getPos();
		physicsTest->getComponent<PhysicsComponent>()->setPosition(pos);
		physicsTest->getComponent<PhysicsComponent>()->setAngularVelocity(0);
		physicsTest->getComponent<PhysicsComponent>()->setVelocity(Vec2f(0, 0));
		physicsTest->getComponent<PhysicsComponent>()->setRotation(0);
		physicsTest->getComponent<PhysicsComponent>()->wake(true);

	}
#endif


#ifdef OS_ANDROID
	
#endif
}