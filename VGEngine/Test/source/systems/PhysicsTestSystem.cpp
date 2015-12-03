
#include "systems/PhysicsTestSystem.h"
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

using namespace vg;
using namespace vg::graphics;
PhysicsTestSystem::PhysicsTestSystem(Scene *scene)
{
	this->scene = scene;
	system = Game::getInstance()->getSceneManager()->getActiveScene()->getComponentSystemManager()->getSystem<PhysicsSystem>();
	system->createBorders(0, 0, Screen::getX(), Screen::getY());

	// Animation
	animationTest = new GameObject("animationTest");
	RenderComponent *animationComponent = new RenderComponent("papparunSmall2.png");
	animationTest->addComponent(animationComponent);

	TransformComponent *animationTransform = new TransformComponent(Vec2f(720, graphics::Screen::getY() - 512), Vec2f(512, 512), 0.0f);
	animationTest->addComponent(animationTransform);
	animationTest->addComponent(new AnimationComponent(0.04, 3, 8, 24));

	scene->addGameObject(animationTest);
	
	// Physics
	physicsTest = new GameObject("physicsTest1");

	TransformComponent *physicsTransform = new TransformComponent(Vec2f(128 * 7, 128 * 2),
		Vec2f(64, 64), 0.0f);

	RenderComponent *physicsObject = new RenderComponent("hippo.png");
	PhysicsComponent *physicsPolyComponent1 = new PhysicsComponent(physicsTransform, PhysicsComponent::STATIC);

	physicsTest->addComponent(physicsPolyComponent1);
	physicsTest->addComponent(physicsTransform);
	physicsTest->addComponent(physicsObject);

	scene->addGameObject(physicsTest);

	// 2nd physics object
	TransformComponent *physicsTransform2 = new TransformComponent(Vec2f(600, 500),
		Vec2f(64, 64), 0.0f);

	GameObject *physicsTest2 = new GameObject("physicsTest2");
	RenderComponent *physicsRender2 = new RenderComponent("hippo.png");

	PhysicsComponent *physicsPolyComponent2 = new PhysicsComponent(physicsTransform2, PhysicsComponent::DYNAMIC);

	physicsTest2->addComponent(physicsPolyComponent2);
	physicsTest2->addComponent(physicsTransform2);
	physicsTest2->addComponent(physicsRender2);

	physicsTest2->getComponent<PhysicsComponent>()->setFriction(1000);
	//physicsTest2->getComponent<PhysicsComponent>()->setRotationLock(true);

	scene->addGameObject(physicsTest2);

	// 3rd physics object
	TransformComponent *physicsTransform3 = new TransformComponent(Vec2f(800, 400),
		Vec2f(64, 64), 0.0f);

	physicsTest3 = new GameObject("physicsTest3");
	RenderComponent *physicsRender3 = new RenderComponent("hippo.png");

	PhysicsComponent *physicsPolyComponent3 = new PhysicsComponent(physicsTransform3, PhysicsComponent::DYNAMIC);

	physicsTest3->addComponent(physicsPolyComponent3);
	physicsTest3->addComponent(physicsTransform3);
	physicsTest3->addComponent(physicsRender3);
	physicsTest3->getComponent<PhysicsComponent>()->setRestitution(0);

	scene->addGameObject(physicsTest3);
	
	Joint *joint;
	joint = new Joint(physicsPolyComponent2, physicsPolyComponent1);
	joint->createRevoluteJoint();

	//// Two physics objects with same collision masks wont collide
	physicsTest3->getComponent<PhysicsComponent>()->setCollisionFilter(PhysicsComponent::FILTER::MIDDLE);
	physicsTest->getComponent<PhysicsComponent>()->setCollisionFilter(PhysicsComponent::FILTER::MIDDLE);

}
void PhysicsTestSystem::update(std::vector<vg::GameObject*> *gameObjects, float deltaTime)
{
	animationTest->getComponent<TransformComponent>()->move(Vec2f(-10, 0));

	if (animationTest->getComponent<TransformComponent>()->getLocalPosition().x < -animationTest->getComponent<TransformComponent>()->getSize().x)
		animationTest->getComponent<TransformComponent>()->setPosition(Vec2f(graphics::Screen::getX(), animationTest->getComponent<TransformComponent>()->getLocalPosition().y));


#ifdef OS_WINDOWS
	// Pappa explosions
	/*
	if (newPositionTime.getCurrentTimeSeconds() >= 0.12)
	{
		randPos = Vec2f(rand() % Screen::getX(), rand() % Screen::getY());
		newPositionTime.restart();

		for (auto it = gameObjects->begin(); it != gameObjects->end(); it++)
		{
			PhysicsComponent* physComponent = (*it)->getComponent<PhysicsComponent>();
			TransformComponent* transform = (*it)->getComponent<TransformComponent>();

			if (physComponent != nullptr && transform != nullptr)
			{
				float number = rand() % 400 - 200.0f;
				float number2 = rand() % 200;

				physComponent->setVelocity(Vec2f(number, number2));
				physComponent->setPosition(randPos);
			}
		}
	}
	*/
	
	if (vg::input::Mouse::isKeyDown(vg::input::RIGHT))
	{
		vg::Vec2f pos = vg::input::Mouse::getPos();
		createPapis(pos);
	}

	if (vg::input::Keyboard::getKeyState(vg::input::Keyboard::W) == vg::input::Keyboard::KeyState::PRESSED)
	{
		vg::Vec2f pos = vg::input::Mouse::getPos();

		for (auto it = gameObjects->begin(); it != gameObjects->end(); it++)
		{
			PhysicsComponent* physComponent = (*it)->getComponent<PhysicsComponent>();
			TransformComponent* transform = (*it)->getComponent<TransformComponent>();

			if (physComponent != nullptr && transform != nullptr)
			{
				float number = rand() % 400 - 200.0f;
				float number2 = rand() % 200;
				physComponent->setVelocity(Vec2f(number, number2));
				physComponent->setPosition(pos);
			}
		}
	}
	
	if (vg::input::Keyboard::getKeyState(vg::input::Keyboard::E) == vg::input::Keyboard::KeyState::PRESSED)
	{
		vg::Vec2f pos = vg::input::Mouse::getPos();
		physicsTest3->getComponent<PhysicsComponent>()->applyLinearImpulse(Vec2f(0, 100));
	}

	if (vg::input::Keyboard::getKeyState(vg::input::Keyboard::Q) == vg::input::Keyboard::KeyState::PRESSED)
	{
		vg::Vec2f pos = vg::input::Mouse::getPos();
		physicsTest3->getComponent<PhysicsComponent>()->applyForce(Vec2f(0, 1000));
	}

	if (vg::input::Keyboard::getKeyState(vg::input::Keyboard::S) == vg::input::Keyboard::KeyState::PRESSED)
	{
		vg::Vec2f pos = vg::input::Mouse::getPos();
		physicsTest->getComponent<PhysicsComponent>()->setPosition(pos);
		physicsTest->getComponent<PhysicsComponent>()->setAngularVelocity(0);
		physicsTest->getComponent<PhysicsComponent>()->setVelocity(Vec2f(0, 0));
		physicsTest->getComponent<PhysicsComponent>()->setRotation(0);
	}

	if (vg::input::Keyboard::getKeyState(vg::input::Keyboard::R) == vg::input::Keyboard::KeyState::PRESSED)
	{
		vg::Vec2f pos = vg::input::Mouse::getPos();
	}


	if (physicsTest3 != nullptr)
	{
		if (!physicsTest3->markedForDelete())
		{
			if (vg::input::Keyboard::getKeyState(vg::input::Keyboard::F) == vg::input::Keyboard::KeyState::PRESSED)
			{
				physicsTest3->markForDelete();
			}
		}
	}

	if (vg::input::Keyboard::getKeyState(vg::input::Keyboard::A) == vg::input::Keyboard::KeyState::PRESSED)
	{
		system->setGravity(Vec2f(0, 0));
	}
	if (vg::input::Keyboard::getKeyState(vg::input::Keyboard::D) == vg::input::Keyboard::KeyState::PRESSED)
	{
		system->setGravity(Vec2f(0, -9.81));
	}

#endif

#ifdef OS_ANDROID
	if (vg::input::Touch::getIsTouched())
	{
		vg::Vec2f pos = vg::input::Touch::getPos();
		vg::Vec2f res = graphics::Screen::getSize();
		if (pos.x < res.x / 2)
		{
			createPapis(pos);
		}
		else
		{
			for (auto it = gameObjects->begin(); it != gameObjects->end(); it++)
			{
				PhysicsComponent* physComponent = (*it)->getComponent<PhysicsComponent>();
				TransformComponent* transform = (*it)->getComponent<TransformComponent>();

				if (physComponent != nullptr && transform != nullptr)
				{
					float number = rand() % 400 - 200.0f;
					float number2 = rand() % 200;
					physComponent->setVelocity(Vec2f(number, number2));
				}
			}
		}
	}
#endif
}

void PhysicsTestSystem::createPapis(Vec2f pos)
{
	for (int i = 0; i < 5; i++)
	{
		TransformComponent *physicsTransform = new TransformComponent(Vec2f(pos.x, pos.y),
			Vec2f(64, 64), 0.0f);

		GameObject *physicsTest = new GameObject("physicsTest");
		physicsTest->addComponent(physicsTransform);
		physicsTest->addComponent(new PhysicsComponent(physicsTransform, PhysicsComponent::DYNAMIC, 54));
		RenderComponent *animationComponent = new RenderComponent("papparunSmall2.png");

		physicsTest->addComponent(new AnimationComponent(0.04, 3, 8, 24));
		physicsTest->addComponent(animationComponent);

		scene->addGameObject(physicsTest);
	}
}

void PhysicsTestSystem::onHit(vg::GameObject *other, vg::GameObject *other2)
{
	std::cout << "Doge" << std::endl;
}