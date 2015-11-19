
#include "systems/PhysicsTestSystem.h"

#ifdef OS_WINDOWS
#include "engine/input/mouse.h"
#include "engine\input\keyboard.h"
#endif
#ifdef OS_ANDROID
#include "engine/input/touch.h"
#endif

#include "engine/game/quadrangleComponent.h"
#include "engine/game/game.h"
#include "engine/game/physicsCircleComponent.h"
#include "engine/game/physicsPolygonComponent.h"
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
	QuadrangleComponent *animationComponent = new QuadrangleComponent("papparunSmall2.png");
	animationTest->addComponent(animationComponent);

	TransformComponent *animationTransform = new TransformComponent(Vec2f(720, graphics::Screen::getY() - 512), Vec2f(512, 512), 0.0f);
	animationTest->addComponent(animationTransform);
	animationTest->addComponent(new AnimationComponent(0.04, 3, 8, 24));

	scene->addGameObject(animationTest);
	
	// Physics
	physicsTest = new GameObject("physicsTest1");

	TransformComponent *physicsTransform = new TransformComponent(Vec2f(128 * 7, 128 * 2),
		Vec2f(64, 64), 0.0f);

	QuadrangleComponent *physicsObject = new QuadrangleComponent("hippo.png");
	PhysicsPolygonComponent *physicsPolyComponent1 = new PhysicsPolygonComponent(physicsTransform, PhysicsComponent::STATIC);

	physicsTest->addComponent(physicsPolyComponent1);
	physicsTest->addComponent(physicsTransform);
	physicsTest->addComponent(physicsObject);

	scene->addGameObject(physicsTest);

	// 2nd physics object
	TransformComponent *physicsTransform2 = new TransformComponent(Vec2f(600, 500),
		Vec2f(64, 64), 0.0f);

	GameObject *physicsTest2 = new GameObject("physicsTest2");
	QuadrangleComponent *physicsRender2 = new QuadrangleComponent("hippo.png");

	PhysicsPolygonComponent *physicsPolyComponent2 = new PhysicsPolygonComponent(physicsTransform2, PhysicsComponent::DYNAMIC, 64, 64);

	physicsTest2->addComponent(physicsPolyComponent2);
	physicsTest2->addComponent(physicsTransform2);
	physicsTest2->addComponent(physicsRender2);

	//physicsTest2->getComponent<PhysicsPolygonComponent>()->setRotationLock(true);

	scene->addGameObject(physicsTest2);

	// 3rd physics object
	TransformComponent *physicsTransform3 = new TransformComponent(Vec2f(800, 400),
		Vec2f(64, 64), 0.0f);

	physicsTest3 = new GameObject("physicsTest3");
	QuadrangleComponent *physicsRender3 = new QuadrangleComponent("hippo.png");

	PhysicsPolygonComponent *physicsPolyComponent3 = new PhysicsPolygonComponent(physicsTransform3, PhysicsComponent::DYNAMIC, 64, 64);

	physicsTest3->addComponent(physicsPolyComponent3);
	physicsTest3->addComponent(physicsTransform3);
	physicsTest3->addComponent(physicsRender3);
	physicsTest3->getComponent<PhysicsPolygonComponent>()->setRestitution(0);

	scene->addGameObject(physicsTest3);

	system->createRevoluteJoint(physicsTest2->getComponent<PhysicsPolygonComponent>(), physicsTest->getComponent<PhysicsPolygonComponent>());

	// Two physics objects with same collision masks wont collide
	physicsTest3->getComponent<PhysicsPolygonComponent>()->setCollisionFilter(PhysicsComponent::FILTER::MIDDLE);
	physicsTest->getComponent<PhysicsPolygonComponent>()->setCollisionFilter(PhysicsComponent::FILTER::MIDDLE);

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
			PhysicsCircleComponent* physComponent = (*it)->getComponent<PhysicsCircleComponent>();
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
			PhysicsCircleComponent* physComponent = (*it)->getComponent<PhysicsCircleComponent>();
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
		physicsTest3->getComponent<PhysicsPolygonComponent>()->applyLinearImpulse(Vec2f(0, 100));
	}

	if (vg::input::Keyboard::getKeyState(vg::input::Keyboard::Q) == vg::input::Keyboard::KeyState::PRESSED)
	{
		vg::Vec2f pos = vg::input::Mouse::getPos();
		physicsTest3->getComponent<PhysicsPolygonComponent>()->applyForce(Vec2f(0, 1000));
	}

	if (vg::input::Keyboard::getKeyState(vg::input::Keyboard::S) == vg::input::Keyboard::KeyState::PRESSED)
	{
		vg::Vec2f pos = vg::input::Mouse::getPos();
		physicsTest3->getComponent<PhysicsPolygonComponent>()->setPosition(pos);
		physicsTest3->getComponent<PhysicsPolygonComponent>()->setAngularVelocity(0);
		physicsTest3->getComponent<PhysicsPolygonComponent>()->setVelocity(Vec2f(0, 0));
		physicsTest3->getComponent<PhysicsPolygonComponent>()->setRotation(0);
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
				PhysicsCircleComponent* physComponent = (*it)->getComponent<PhysicsCircleComponent>();
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
		physicsTest->addComponent(new PhysicsCircleComponent(physicsTransform, PhysicsComponent::DYNAMIC, 54));
		QuadrangleComponent *animationComponent = new QuadrangleComponent("papparunSmall2.png");

		physicsTest->addComponent(new AnimationComponent(0.04, 3, 8, 24));
		physicsTest->addComponent(animationComponent);

		scene->addGameObject(physicsTest);
	}
}