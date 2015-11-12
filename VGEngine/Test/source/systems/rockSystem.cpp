
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
#include "engine/utility/Vector2.h"
#include "engine/game/transformComponent.h"
#include "engine/game/quadrangleComponent.h"
#include "engine/game/physicsPolygonComponent.h"
#include "engine/utility/random.h"
#include "engine/input/touch.h"
#include "engine/graphics/screen.h"
#include "engine/game/physicsSystem.h"

#include <vector>

using namespace vg;
using namespace vg::graphics;
using namespace vg::input;

rockSystem::rockSystem(Scene *scene)
{
	this->scene = scene;
	system = Game::getInstance()->getSceneManager()->getActiveScene()->getComponentSystemManager()->getSystem<PhysicsSystem>();
	system->createBorders(0, 0, 3000, Screen::getY());

	//ROCK
	rock = new GameObject("rock");
	TransformComponent *transformRock = new TransformComponent(Vector2<float>(100, 600),
		Vector2<float>(100, 100), 0.0f);
	QuadrangleComponent *quadre = new QuadrangleComponent("rock.png");
	PhysicsPolygonComponent *rockPhysicsComponent = new PhysicsPolygonComponent(transformRock, PhysicsComponent::DYNAMIC);

	rock->addComponent(transformRock);
	rock->addComponent(quadre);
	rock->addComponent(rockPhysicsComponent);

	scene->addGameObject(rock);

	//HEIGHTBAR
	bar1 = new GameObject("bar1");
	TransformComponent *transformBar1 = new TransformComponent(Vector2<float>(20, 10),
		Vector2<float>(50, 170), 0.0f);
	QuadrangleComponent *quadreBar = new QuadrangleComponent("bar.png");

	bar1->addComponent(transformBar1);
	bar1->addComponent(quadreBar);

	scene->addGameObject(bar1);

	//INDICATOR FOR HEIGHTBAR
	indicator1 = new GameObject("indicator1");
	TransformComponent *transformIndicator1 = new TransformComponent(Vector2<float>(0, 170),
		Vector2<float>(100, 10), 0.0f);
	QuadrangleComponent *quadreIndicator = new QuadrangleComponent("indicator.png");

	indicator1->addComponent(transformIndicator1);
	indicator1->addComponent(quadreIndicator);

	scene->addGameObject(indicator1);

	//POWERBAR
	bar2 = new GameObject("bar2");
	TransformComponent *transformBar2 = new TransformComponent(Vector2<float>(120, 10),
		Vector2<float>(50, 170), 0.0f);

	bar2->addComponent(transformBar2);
	bar2->addComponent(quadreBar);

	scene->addGameObject(bar2);

	//INDICATOR FOR POWERBAR
	indicator2 = new GameObject("indicator2");
	TransformComponent *transformIndicator2 = new TransformComponent(Vector2<float>(100, 170),
		Vector2<float>(100, 10), 0.0f);

	indicator2->addComponent(transformIndicator2);
	indicator2->addComponent(quadreIndicator);

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
	
}

rockSystem::~rockSystem()
{
}
void rockSystem::update(std::vector<vg::GameObject*> *gameObjects, float deltaTime)
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

		indicator1->getComponent<TransformComponent>()->setPosition(Vector2<float>(0, height));

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

		indicator2->getComponent<TransformComponent>()->setPosition(Vector2<float>(100, power));

	}

#ifdef OS_WINDOWS
	if (vg::input::Keyboard::getKeyState(vg::input::Keyboard::E) == vg::input::Keyboard::KeyState::DOWN)
	{
		if (!heightLock)
		{
			heightLock = true;
			powerLock = false;
		}
		if (!powerLock)
		{
			powerLock = true;
			rock->getComponent<PhysicsPolygonComponent>()->setVelocity(Vector2<float>(power, maxHeight - height));
		}
	}
#endif

#ifdef OS_ANDROID
	if (Touch::getIsReleased())
	{
		if (!heightLock)
		{
			heightLock = true;
			powerLock = false;
		}
		if (!powerLock)
		{
			powerLock = true;
			rock->getComponent<PhysicsPolygonComponent>()->setVelocity(Vector2<float>(power, maxHeight - height));
		}
	}

#endif
}

