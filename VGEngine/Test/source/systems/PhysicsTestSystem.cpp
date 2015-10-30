
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

using namespace vg;

PhysicsTestSystem::PhysicsTestSystem(Scene *scene)
{
	this->scene = scene;
	system = Game::getInstance()->getSceneManager()->getActiveScene()->getComponentSystemManager()->getSystem<PhysicsSystem>();

	// Physics
	physicsTest = new GameObject("physicsTest1");

	TransformComponent *physicsTransform = new TransformComponent(Vector2<float>(80, 64),
		Vector2<float>(64, 64), 0.0f);

	QuadrangleComponent *physicsObject = new QuadrangleComponent("hippo.png");
	PhysicsPolygonComponent *physicsPolyComponent1 = new PhysicsPolygonComponent(physicsTransform, PhysicsComponent::DYNAMIC);

	physicsTest->addComponent(physicsPolyComponent1);
	physicsTest->addComponent(physicsTransform);
	physicsTest->addComponent(physicsObject);

	scene->addGameObject(physicsTest);

	// 2nd physics object
	TransformComponent *physicsTransform2 = new TransformComponent(Vector2<float>(400, 400),
		Vector2<float>(64, 64), 0.0f);

	GameObject *physicsTest2 = new GameObject("physicsTest2");
	QuadrangleComponent *physicsRender2 = new QuadrangleComponent("hippo.png");

	PhysicsPolygonComponent *physicsPolyComponent2 = new PhysicsPolygonComponent(physicsTransform2, PhysicsComponent::STATIC, 64, 64);

	physicsTest2->addComponent(physicsPolyComponent2);
	physicsTest2->addComponent(physicsTransform2);
	physicsTest2->addComponent(physicsRender2);

	scene->addGameObject(physicsTest2);

	system->createJoint(physicsTest->getComponent<PhysicsPolygonComponent>(), physicsTest2->getComponent<PhysicsPolygonComponent>());
}
void PhysicsTestSystem::update(std::vector<vg::GameObject*> *gameObjects, float deltaTime)
{
#ifdef OS_WINDOWS

	if (vg::input::Mouse::isKeyPressed(vg::input::RIGHT))
	{
		vg::Vector2<float> pos = vg::input::Mouse::getPos();
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

	if (vg::input::Mouse::isKeyPressed(vg::input::MIDDLE))
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
			}
		}
	}

	if (vg::input::Keyboard::getKeyState(vg::input::Keyboard::S) == vg::input::Keyboard::KeyState::PRESSED)
	{
			vg::Vector2<float> pos = vg::input::Mouse::getPos();
			physicsTest->getComponent<PhysicsPolygonComponent>()->setPosition(pos);
			//physicsTest->getComponent<TransformComponent>()->setPosition(pos);
	}

	if (vg::input::Keyboard::getKeyState(vg::input::Keyboard::A) == vg::input::Keyboard::KeyState::PRESSED)
	{
		system->setGravity(Vector2<float>(0, 0));
	}
	if (vg::input::Keyboard::getKeyState(vg::input::Keyboard::D) == vg::input::Keyboard::KeyState::PRESSED)
	{
		system->setGravity(Vector2<float>(0, -9.81 * 20));
	}

#endif

#ifdef OS_ANDROID
	if (vg::input::Touch::getIsTouched())
	{
		vg::Vector2<float> touchPos = vg::input::Touch::getTouchPos();
		vg::Vector2<int> res = graphics::Screen::getSize();
		if (touchPos.getX() < res.getX() / 2)
		{
			for (int i = 0; i < 5; i++)
			{

				TransformComponent *physicsTransform2 = new TransformComponent(
					Vector2<float>(touchPos.getX(), touchPos.getY()), Vector2<float>(64, 64), 0.0f);

				GameObject *physicsTest = new GameObject("physicsTest");
				physicsTest->addComponent(new PhysicsComponent(physicsTransform2, PhysicsComponent::DYNAMIC));

				QuadrangleComponent *physicsRender2 = new QuadrangleComponent("doge.png");
				physicsTest->addComponent(physicsRender2);
				physicsTest->addComponent(physicsTransform2);

				scene->addGameObject(physicsTest);
			}
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
					physComponent->setVelocity(Vector2<float>(number, number2));
				}
			}
		}
	}
#endif
}