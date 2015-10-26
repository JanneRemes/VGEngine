
#include "PhysicsTestSystem.h"

#ifdef OS_WINDOWS
#include "engine/input/mouse.h"
#endif
#ifdef OS_ANDROID
#include "engine/input/touch.h"
#endif

#include "engine/game/quadrangleComponent.h"
#include "engine/game/game.h"
#include "engine/game/physicsCircleComponent.h"
#include "engine/game/physicsPolygonComponent.h"
#include "engine/game/physicsSystem.h"
#include "engine/game/animationComponent.h"
#include "engine/game/animationSystem.h"
#include "engine/utility/random.h"
#include "engine/graphics/screen.h"

#include <iostream>

using namespace vg;

PhysicsTestSystem::PhysicsTestSystem(Scene *scene)
{
	this->scene = scene;

	// Physics
	TransformComponent *physicsTransform = new TransformComponent(Vector2<int>(80, 64),
		Vector2<int>(64, 64), 0.0f);

	GameObject *physicsTest = new GameObject("physicsTest1");
	physicsTest->addComponent(physicsTransform);

	PhysicsPolygonComponent *polytestasd = new PhysicsPolygonComponent(physicsTransform, b2BodyType::b2_dynamicBody, PhysicsSystem::world);
	physicsTest->addComponent(polytestasd);

	QuadrangleComponent *physicsObject = new QuadrangleComponent("hippo.png");
	physicsTest->addComponent(physicsObject);

	scene->addGameObject(physicsTest);

	// 2nd physics object

	TransformComponent *physicsTransform2 = new TransformComponent(Vector2<int>(128, 128 * 3),
		Vector2<int>(64, 64), 0.0f);

	GameObject *physicsTest2 = new GameObject("physicsTest2");
	physicsTest2->addComponent(physicsTransform2);

	physicsTest2->addComponent(new PhysicsPolygonComponent(physicsTransform2, b2BodyType::b2_dynamicBody, PhysicsSystem::world, 64, 64));

	QuadrangleComponent *physicsRender2 = new QuadrangleComponent("hippo.png");
	physicsTest2->addComponent(physicsRender2);

	scene->addGameObject(physicsTest2);
}
void PhysicsTestSystem::update(std::vector<vg::GameObject*> *gameObjects, float deltaTime)
{
#ifdef OS_WINDOWS

	if (vg::input::Mouse::isKeyPressed(vg::input::RIGHT))
	{
		vg::Vector2<float> pos = vg::input::Mouse::getMousePos();
		for (int i = 0; i < 5; i++)
		{
			TransformComponent *physicsTransform = new TransformComponent(Vector2<int>(pos.getX(), pos.getY()),
				Vector2<int>(64, 64), 0.0f);

			GameObject *physicsTest = new GameObject("physicsTest");
			physicsTest->addComponent(physicsTransform);
			physicsTest->addComponent(new PhysicsCircleComponent(physicsTransform, b2BodyType::b2_dynamicBody, PhysicsSystem::world, 54));
			QuadrangleComponent *animationComponent = new QuadrangleComponent("papparunSmall2.png");
			
			physicsTest->addComponent(new AnimationComponent(0.04, 3, 8, 24));
			physicsTest->addComponent(animationComponent);

			scene->addGameObject(physicsTest);
		}
	}

	if (vg::input::Mouse::isKeyPressed(vg::input::MIDDLE))
	{
		//PhysicsSystem::world->SetGravity(b2Vec2(PhysicsSystem::world->GetGravity().x, -PhysicsSystem::world->GetGravity().y));
		vg::Vector2<float> pos = vg::input::Mouse::getMousePos();

		for (auto it = gameObjects->begin(); it != gameObjects->end(); it++)
		{
			PhysicsCircleComponent* physComponent = (*it)->getComponent<PhysicsCircleComponent>();
			TransformComponent* transform = (*it)->getComponent<TransformComponent>();

			if (physComponent != nullptr && transform != nullptr)
			{
				float number = rand() % 400 - 200.0f;
				float number2 = rand() % 200;
				physComponent->getBody()->SetLinearVelocity(b2Vec2(number, number2));
			}
		}
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

				TransformComponent *physicsTransform2 = new TransformComponent(Vector2<int>(touchPos.getX(), touchPos.getY()),
					Vector2<int>(64, 64), 0.0f);

				GameObject *physicsTest = new GameObject("physicsTest");
				physicsTest->addComponent(new PhysicsComponent(physicsTransform2, b2BodyType::b2_dynamicBody, PhysicsSystem::world));

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
					physComponent->getBody()->SetLinearVelocity(b2Vec2(number, number2));
				}
			}
		}
	}
	#endif
}