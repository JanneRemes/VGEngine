
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

	TransformComponent *animationTransform = new TransformComponent(Vector2<float>(720, graphics::Screen::getY() - 512), Vector2<float>(512, 512), 0.0f);
	animationTest->addComponent(animationTransform);
	animationTest->addComponent(new AnimationComponent(0.04, 3, 8, 24));

	scene->addGameObject(animationTest);
	
	// Physics
	physicsTest = new GameObject("physicsTest1");

	TransformComponent *physicsTransform = new TransformComponent(Vector2<float>(128 * 7, 128 * 2),
		Vector2<float>(64, 64), 0.0f);

	QuadrangleComponent *physicsObject = new QuadrangleComponent("hippo.png");
	PhysicsPolygonComponent *physicsPolyComponent1 = new PhysicsPolygonComponent(physicsTransform, PhysicsComponent::STATIC);

	physicsTest->addComponent(physicsPolyComponent1);
	physicsTest->addComponent(physicsTransform);
	physicsTest->addComponent(physicsObject);

	scene->addGameObject(physicsTest);

	// 2nd physics object
	TransformComponent *physicsTransform2 = new TransformComponent(Vector2<float>(600, 400),
		Vector2<float>(64, 64), 0.0f);

	GameObject *physicsTest2 = new GameObject("physicsTest2");
	QuadrangleComponent *physicsRender2 = new QuadrangleComponent("hippo.png");

	PhysicsPolygonComponent *physicsPolyComponent2 = new PhysicsPolygonComponent(physicsTransform2, PhysicsComponent::DYNAMIC, 64, 64);

	physicsTest2->addComponent(physicsPolyComponent2);
	physicsTest2->addComponent(physicsTransform2);
	physicsTest2->addComponent(physicsRender2);

	scene->addGameObject(physicsTest2);

	// 3rd physics object
	TransformComponent *physicsTransform3 = new TransformComponent(Vector2<float>(800, 400),
		Vector2<float>(64, 64), 0.0f);

	physicsTest3 = new GameObject("physicsTest2");
	QuadrangleComponent *physicsRender3 = new QuadrangleComponent("hippo.png");

	PhysicsPolygonComponent *physicsPolyComponent3 = new PhysicsPolygonComponent(physicsTransform3, PhysicsComponent::DYNAMIC, 64, 64);

	physicsTest3->addComponent(physicsPolyComponent3);
	physicsTest3->addComponent(physicsTransform3);
	physicsTest3->addComponent(physicsRender3);
	
	physicsTest3->getComponent<PhysicsPolygonComponent>()->setRotationLock(false);

	physicsTest3->getComponent<PhysicsPolygonComponent>()->setRestitution(1.1);

	scene->addGameObject(physicsTest3);

	system->createJoint(physicsTest2->getComponent<PhysicsPolygonComponent>(), physicsTest->getComponent<PhysicsPolygonComponent>());
}
void PhysicsTestSystem::update(std::vector<vg::GameObject*> *gameObjects, float deltaTime)
{
	animationTest->getComponent<TransformComponent>()->move(Vector2<float>(-10, 0));

	if (animationTest->getComponent<TransformComponent>()->getLocalPosition().getX() < -animationTest->getComponent<TransformComponent>()->getSize().getX())
		animationTest->getComponent<TransformComponent>()->setPosition(Vector2<float>(graphics::Screen::getX(), animationTest->getComponent<TransformComponent>()->getLocalPosition().getY()));


#ifdef OS_WINDOWS

	// Pappa explosions
	/*
	if (newPositionTime.getCurrentTimeSeconds() >= 0.12)
	{
		randPos = Vector2<float>(rand() % Screen::getX(), rand() % Screen::getY());
		newPositionTime.restart();

		for (auto it = gameObjects->begin(); it != gameObjects->end(); it++)
		{
			PhysicsCircleComponent* physComponent = (*it)->getComponent<PhysicsCircleComponent>();
			TransformComponent* transform = (*it)->getComponent<TransformComponent>();

			if (physComponent != nullptr && transform != nullptr)
			{
				float number = rand() % 400 - 200.0f;
				float number2 = rand() % 200;

				physComponent->setVelocity(Vector2<float>(number, number2));
				physComponent->setPosition(randPos);
			}
		}
	}
	*/


	if (vg::input::Mouse::isKeyPressed(vg::input::RIGHT))
	{
		vg::Vector2<float> pos = vg::input::Mouse::getPos();
		createPapis(pos);
	}

	if (vg::input::Keyboard::getKeyState(vg::input::Keyboard::W) == vg::input::Keyboard::KeyState::PRESSED)
	{
		vg::Vector2<float> pos = vg::input::Mouse::getPos();

		for (auto it = gameObjects->begin(); it != gameObjects->end(); it++)
		{
			PhysicsCircleComponent* physComponent = (*it)->getComponent<PhysicsCircleComponent>();
			TransformComponent* transform = (*it)->getComponent<TransformComponent>();

			if (physComponent != nullptr && transform != nullptr)
			{
				float number = rand() % 400 - 200.0f;
				float number2 = rand() % 200;
				physComponent->setVelocity(Vector2<float>(number, number2));
				physComponent->setPosition(pos);
			}
		}
	}
	
	if (vg::input::Keyboard::getKeyState(vg::input::Keyboard::E) == vg::input::Keyboard::KeyState::PRESSED)
	{
		vg::Vector2<float> pos = vg::input::Mouse::getPos();
		physicsTest3->getComponent<PhysicsPolygonComponent>()->applyLinearImpulse(Vector2<float>(0, 100));
	}

	if (vg::input::Keyboard::getKeyState(vg::input::Keyboard::Q) == vg::input::Keyboard::KeyState::PRESSED)
	{
		vg::Vector2<float> pos = vg::input::Mouse::getPos();
		physicsTest3->getComponent<PhysicsPolygonComponent>()->applyForce(Vector2<float>(0, 1000));
	}

	if (vg::input::Keyboard::getKeyState(vg::input::Keyboard::S) == vg::input::Keyboard::KeyState::PRESSED)
	{
		vg::Vector2<float> pos = vg::input::Mouse::getPos();
		physicsTest3->getComponent<PhysicsPolygonComponent>()->setPosition(pos);
	}

	if (vg::input::Keyboard::getKeyState(vg::input::Keyboard::A) == vg::input::Keyboard::KeyState::PRESSED)
	{
		system->setGravity(Vector2<float>(0, 0));
	}
	if (vg::input::Keyboard::getKeyState(vg::input::Keyboard::D) == vg::input::Keyboard::KeyState::PRESSED)
	{
		system->setGravity(Vector2<float>(0, -9.81));
	}

#endif

#ifdef OS_ANDROID
	if (vg::input::Touch::getIsTouched())
	{
		vg::Vector2<float> pos = vg::input::Touch::getPos();
		vg::Vector2<int> res = graphics::Screen::getSize();
		if (pos.getX() < res.getX() / 2)
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
					physComponent->setVelocity(Vector2<float>(number, number2));
				}
			}
		}
	}
#endif
}

void PhysicsTestSystem::createPapis(Vector2<float> pos)
{
	for (int i = 0; i < 5; i++)
	{
		TransformComponent *physicsTransform = new TransformComponent(Vector2<float>(pos.getX(), pos.getY()),
			Vector2<float>(64, 64), 0.0f);

		GameObject *physicsTest = new GameObject("physicsTest");
		physicsTest->addComponent(physicsTransform);
		physicsTest->addComponent(new PhysicsCircleComponent(physicsTransform, PhysicsComponent::DYNAMIC, 54));
		QuadrangleComponent *animationComponent = new QuadrangleComponent("papparunSmall2.png");

		physicsTest->addComponent(new AnimationComponent(0.04, 3, 8, 24));
		physicsTest->addComponent(animationComponent);

		scene->addGameObject(physicsTest);
	}
}