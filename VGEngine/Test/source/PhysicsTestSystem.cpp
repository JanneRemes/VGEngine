#include "PhysicsTestSystem.h"
#include "engine/input/mouse.h"
#include <engine\game\quadrangleComponent.h>
#include <engine\game\game.h>

#include <engine\game\physicsComponent.h>
#include <engine\game\physicsSystem.h>
#include <iostream>
using namespace vg;

PhysicsTestSystem::PhysicsTestSystem(Scene *scene)
{
	this->scene = scene;

	// Physics
	float gravity = 9.81;
	Vector2<int> resolution = Game::getInstance()->getGraphics()->getResolution();
	PhysicsSystem *physicsSystem = new PhysicsSystem(0, -9.81 * 20);
	// Remember to create borders here
	physicsSystem->createBorders(0, 0, resolution.getX(), resolution.getY());

	Game::getInstance()->addComponentSystem(scene, physicsSystem);

	TransformComponent *physicsTransform = new TransformComponent(Vector2<int>(64, 64),
		Vector2<int>(64, 64), 0.0f);

	GameObject *physicsTest = new GameObject("physicsTest1");
	physicsTest->addComponent(physicsTransform);
	physicsTest->addComponent(new PhysicsComponent(physicsTransform, b2BodyType::b2_dynamicBody, PhysicsSystem::world, PhysicsComponent::BOX));

	QuadrangleComponent *physicsObject = Game::getInstance()->getFactory()->createRenderComponent<QuadrangleComponent>("hippo.png");
	physicsTest->addComponent(physicsObject);

	scene->addGameObject(physicsTest);

	// 2nd physics object

	TransformComponent *physicsTransform2 = new TransformComponent(Vector2<int>(128, 128 * 3),
		Vector2<int>(64, 64), 0.0f);

	GameObject *physicsTest2 = new GameObject("physicsTest2");
	physicsTest2->addComponent(physicsTransform2);

	physicsTest2->addComponent(new PhysicsComponent(physicsTransform2, b2BodyType::b2_dynamicBody, PhysicsSystem::world, PhysicsComponent::BOX));

	QuadrangleComponent *physicsRender2 = Game::getInstance()->getFactory()->createRenderComponent<QuadrangleComponent>("hippo.png");
	physicsTest2->addComponent(physicsRender2);

	scene->addGameObject(physicsTest2);
}
void PhysicsTestSystem::update(std::vector<vg::GameObject*> *gameObjects, float deltaTime)
{
	/*
	if (vg::input::Mouse::isKeyPressed(vg::input::RIGHT))
	{
		vg::Vector2<float> pos = vg::input::Mouse::getMousePos();
		std::cout << "Wild moomi appears" << endl;
		cout << PhysicsSystem::world->GetGravity().x << " " << PhysicsSystem::world->GetGravity().y << endl;

		TransformComponent *physicsTransform2 = new TransformComponent(Vector2<int>(pos.getX(), pos.getY()),
			Vector2<int>(64, 64), 0.0f);

		GameObject *physicsTest = new GameObject("physicsTest");
		physicsTest->addComponent(new PhysicsComponent(physicsTransform2, b2BodyType::b2_dynamicBody, PhysicsSystem::world, PhysicsComponent::CIRCLE));

		QuadrangleComponent *physicsRender2 = Game::getInstance()->getFactory()->createRenderComponent<QuadrangleComponent>("doge.png");
		physicsTest->addComponent(physicsRender2);
		physicsTest->addComponent(physicsTransform2);

		scene->addGameObject(physicsTest);
	}
	
	if (vg::input::Mouse::isKeyPressed(vg::input::MIDDLE))
	{
		//PhysicsSystem::world->SetGravity(b2Vec2(PhysicsSystem::world->GetGravity().x, -PhysicsSystem::world->GetGravity().y));
		vg::Vector2<float> pos = vg::input::Mouse::getMousePos();

		for (auto it = gameObjects->begin(); it != gameObjects->end(); it++)
		{
			PhysicsComponent* physComponent = (*it)->getComponent<PhysicsComponent>();
			TransformComponent* transform = (*it)->getComponent<TransformComponent>();

			if (physComponent != nullptr && transform != nullptr)
			{
				physComponent->getBody()->SetLinearVelocity(b2Vec2(physComponent->getBody()->GetLinearVelocity().x + 100, physComponent->getBody()->GetLinearVelocity().y + 100));
			}
		}
	}
	*/
}