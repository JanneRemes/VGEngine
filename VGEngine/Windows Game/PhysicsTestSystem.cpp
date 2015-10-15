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
}
void PhysicsTestSystem::update(std::vector<vg::GameObject*> *gameObjects, float deltaTime)
{
	if (vg::input::Mouse::isKeyPressed(vg::input::RIGHT))
	{
		vg::Vector2<float> pos = vg::input::Mouse::getMousePos();
		std::cout << "Wild moomi appears" << endl;

		GameObject *physicsTest = new GameObject("physicsTest");
		physicsTest->addComponent(new PhysicsComponent(pos.getX(), pos.getY(), 64, b2BodyType::b2_dynamicBody, PhysicsSystem::getWorld()));

		QuadrangleComponent *physicsRender2 = Game::getInstance()->getFactory()->createRenderComponent<QuadrangleComponent>("doge.png");
		physicsTest->addComponent(physicsRender2);

		TransformComponent *physicsTransform2 = new TransformComponent(Vector2<int>(64, 64),
			Vector2<int>(64, 64), 0.0f);
		physicsTest->addComponent(physicsTransform2);

		scene->addGameObject(physicsTest);
	}
	
	if (vg::input::Mouse::isKeyPressed(vg::input::MIDDLE))
	{
		//PhysicsSystem::getWorld()->SetGravity(b2Vec2(PhysicsSystem::getWorld()->GetGravity().x, -PhysicsSystem::getWorld()->GetGravity().y));
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
}