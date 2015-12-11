
#pragma once

#include "systems/rockSystem.h"

#ifdef OS_WINDOWS
#include "engine/input/mouse.h"
#include "engine\input\keyboard.h"
#endif
#ifdef OS_ANDROID
#include "engine/input/touch.h"
#endif

#include "engine/input/sensor.h"
#include "engine/game/game.h"
#include "engine/utility/vec2f.h"
#include "engine/game/transformComponent.h"
#include "engine/game/renderComponent.h"
#include "engine/game/PhysicsComponent.h"
#include "engine/utility/random.h"
#include "engine/input/touch.h"
#include "engine/graphics/screen.h"
#include "engine/game/physicsSystem.h"
#include "engine\graphics\camera.h"
#include "engine/utility/string.h"

#include <vector>

using namespace vg;
using namespace vg::graphics;
using namespace vg::input;

rockSystem::rockSystem(Scene *scene)
{
	timer.restart();
	this->scene = scene;
	system = Game::getInstance()->getSceneManager()->getActiveScene()->getComponentSystemManager()->getSystem<PhysicsSystem>();
	system->createBorders(0, 10000, 10000000000, Screen::getY());

	//BACKGROUND
	background1 = new GameObject("BG1");
	background2 = new GameObject("BG2");

	TransformComponent* bgTransform1 = new TransformComponent(Vec2f(0 - Screen::getX() * 0.10, 0), Screen::getSize(), 0, Vec2f(0, 0), vg::TransformComponent::LayerGroup::BOTTOM);
	TransformComponent* bgTransform2 = new TransformComponent(Vec2f(Screen::getX() - Screen::getX() * 0.10, 0), Screen::getSize(), 0, Vec2f(0, 0), vg::TransformComponent::LayerGroup::BOTTOM);

	RenderComponent* bgRender1 = new RenderComponent("desertBG.png");
	RenderComponent* bgRender2 = new RenderComponent("desertBG.png");

	background1->addComponent(bgTransform1);
	background1->addComponent(bgRender1);
	background2->addComponent(bgTransform2);
	background2->addComponent(bgRender2);

	scene->addGameObject(background1);
	scene->addGameObject(background2);

	//ROCK
	rock = new GameObject("rock");
	TransformComponent *transformRock = new TransformComponent(Vec2f(100, 600),
		Vec2f(100, 100), 0.0f);
	RenderComponent *quadre = new RenderComponent("rock.png");
	PhysicsComponent *rockPhysicsComponent = new PhysicsComponent(transformRock, PhysicsComponent::DYNAMIC);

	rock->addComponent(transformRock);
	rock->addComponent(quadre);
	rock->addComponent(rockPhysicsComponent);

	rock->getComponent<PhysicsComponent>()->setFriction(0.50);
	rock->getComponent<PhysicsComponent>()->setDensity(100);
	rock->getComponent<PhysicsComponent>()->setRestitution(0.60);

	scene->addGameObject(rock);

	//HEIGHTBAR
	bar1 = new GameObject("bar1");
	TransformComponent *transformBar1 = new TransformComponent(Vec2f(20, 10),
		Vec2f(50, 170), 0.0f,Vec2f(0,0));
	RenderComponent *quadreBar1 = new RenderComponent("bar.png");

	bar1->addComponent(transformBar1);
	bar1->addComponent(quadreBar1);

	scene->addGameObject(bar1);

	//INDICATOR FOR HEIGHTBAR
	indicator1 = new GameObject("indicator1");
	TransformComponent *transformIndicator1 = new TransformComponent(Vec2f(0, 170),
		Vec2f(100, 10), 0.0f, Vec2f(0, 0));
	RenderComponent *quadreIndicator1 = new RenderComponent("indicator.png");

	indicator1->addComponent(transformIndicator1);
	indicator1->addComponent(quadreIndicator1);

	scene->addGameObject(indicator1);

	//POWERBAR
	bar2 = new GameObject("bar2");
	TransformComponent *transformBar2 = new TransformComponent(Vec2f(120, 10),
		Vec2f(50, 170), 0.0f,Vec2f(0, 0));
	RenderComponent *quadreBar2 = new RenderComponent("bar.png");

	bar2->addComponent(transformBar2);
	bar2->addComponent(quadreBar2);

	scene->addGameObject(bar2);

	//INDICATOR FOR POWERBAR
	indicator2 = new GameObject("indicator2");
	TransformComponent *transformIndicator2 = new TransformComponent(Vec2f(100, 170),
		Vec2f(100, 10), 0.0f, Vec2f(0, 0));
	RenderComponent *quadreIndicator2 = new RenderComponent("indicator.png");

	indicator2->addComponent(transformIndicator2);
	indicator2->addComponent(quadreIndicator2);

	scene->addGameObject(indicator2);

	//VARIABLES
	//Heightbar
	heightLock = false;
	minHeight = 1;
	maxHeight = 170;
	height = 170;
	goUp = false;
	goDown = false;

	//Powerbar
	powerLock = true;
	minPower = 1;
	maxPower = 170;
	power = 170;
	powerUp = false;
	powerDown = false;

	shot = false;
	bgState = BACKGROUND1;
	i = 0;

}

rockSystem::~rockSystem()
{
}
void rockSystem::update(std::vector<vg::GameObject*> *gameObjects, float deltaTime)
{
	updateBars();
	updateInputs();
	updateView();
	updateExplosives(2, gameObjects);
}

void rockSystem::updateBars()
{
	//Indicator on heightbar
	if (!heightLock)
	{
		if (height <= minHeight)
		{
			goUp = true;
			goDown = false;
		}
		if (height >= maxHeight)
		{
			goUp = false;
			goDown = true;
		}

		if (goUp)
			height++;

		else
			height--;

		indicator1->getComponent<TransformComponent>()->setPosition(Vec2f(0, height));

	}

	//Indicator on powerbar
	if (!powerLock)
	{
		if (power <= minPower)
		{
			powerUp = true;
			powerDown = false;

		}
		if (power >= maxPower)
		{
			powerUp = false;
			powerDown = true;
		}
		if (powerUp)
			power++;
		else
			power--;

		indicator2->getComponent<TransformComponent>()->setPosition(Vec2f(100, power));

	}
}

void rockSystem::updateInputs()
{

	//INPUT FOR WINDOWS
#ifdef OS_WINDOWS
	if (vg::input::Mouse::isKeyPressed(vg::input::LEFT))
	{
		if (!powerLock)
		{
			powerLock = true;
			rock->getComponent<PhysicsComponent>()->setVelocity(Vec2f(power, maxHeight - height));
			shot = true;
		}

		if (!heightLock)
		{
			heightLock = true;
			powerLock = false;
		}

	}
#endif

	//INPUT FOR ANDROID
#ifdef OS_ANDROID
	if (Touch::getIsReleased())
	{
		if (!powerLock)
		{
			powerLock = true;
			rock->getComponent<PhysicsComponent>()->setVelocity(Vec2f(power, maxHeight - height));
			shot = true;
		}

		if (!heightLock)
		{
			heightLock = true;
			powerLock = false;
		}

	}
#endif
}

void rockSystem::updateView()
{
	if (shot)
	{
		//MOVING CAMERA
		Camera::setPosition(Vec2f(rock->get<TransformComponent>()->getWorldPosition().x - Screen::getX() * 0.10, Camera::getPosition().y));

		//SCROLLING BACKGROUND
		switch (bgState)
		{
		case Background::BACKGROUND1:

			currentBackground = background1->getComponent<TransformComponent>();

			if (rock->getComponent<TransformComponent>()->getWorldPosition().x >= currentBackground->getWorldPosition().x + Screen::getX() + Screen::getX() * 0.10)
			{
				currentBackground->setPosition(Vec2f(currentBackground->getWorldPosition().x + (2 * Screen::getX()), 0));
				bgState = Background::BACKGROUND2;
			}
			break;

		case Background::BACKGROUND2:

			currentBackground = background2->getComponent<TransformComponent>();

			if (rock->getComponent<TransformComponent>()->getWorldPosition().x >= currentBackground->getWorldPosition().x + Screen::getX() + Screen::getX() * 0.10)
			{
				currentBackground->setPosition(Vec2f(currentBackground->getWorldPosition().x + (2 * Screen::getX()), 0));
				bgState = Background::BACKGROUND1;
			}
			break;

		case Background::RESET:

			bgState = BACKGROUND1;
			break;
		}
	}
}

void rockSystem::updateExplosives(int amount, std::vector<vg::GameObject*> *gameObjects) //TODO
{
	//EXPLOSIVE
	//if (timer.getCurrentTimeSeconds() > amount)
	//{
	//	explosive = new GameObject("explosive " + toStringi(i, 2));
	//	i++;
	//	TransformComponent *explosiveTransform = new TransformComponent(Vec2f(rock->getComponent<TransformComponent>()->getWorldPosition().x + 100, 600), Vec2f(100,100));
	//	RenderComponent *explosiveRender = new RenderComponent("android.png");

	//	explosive->addComponent(explosiveTransform);
	//	explosive->addComponent(explosiveRender);

	//	scene->addGameObject(explosive);
	//	timer.restart();
	//}

	////UPDATE
	//for (auto it = gameObjects->begin(); it != gameObjects->end(); it++)
	//{
	//	if ((*it)->getName().find("explosive") != -1)
	//	{
	//		TransformComponent* trans = (*it)->get<TransformComponent>();
	//		if (trans != nullptr)
	//		{
	//			if (trans->getWorldPosition() == rock->getComponent<TransformComponent>()->getWorldPosition())
	//			{
	//				rock->getComponent<PhysicsComponent>()->applyForce(Vec2f(120, 120));
	//			}
	//		}
	//	}
	//}
}
