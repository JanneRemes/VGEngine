
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

#include <vector>

using namespace vg;
using namespace vg::graphics;

rockSystem::rockSystem(Scene *scene)
{
	this->scene = scene;

	//ROCK
	rock = new GameObject("rock");
	TransformComponent *transformRock = new TransformComponent(Vector2<float>(100, 600),
		Vector2<float>(100, 100), 0.0f, 1);	
	QuadrangleComponent *quadre = new QuadrangleComponent("rock.png");	
	PhysicsPolygonComponent *rockPhysicsComponent = new PhysicsPolygonComponent(transformRock, PhysicsComponent::DYNAMIC);
	
	rock->addComponent(transformRock);
	rock->addComponent(quadre);
	rock->addComponent(rockPhysicsComponent);

	scene->addGameObject(rock);

	bar1 = new GameObject("bar1");
	TransformComponent *transformBar1 = new TransformComponent(Vector2<float>(20, 10),
		Vector2<float>(50, 170), 0.0f, 2);
	QuadrangleComponent *quadreBar1 = new QuadrangleComponent("bar.png");

	bar1->addComponent(transformBar1);
	bar1->addComponent(quadreBar1);

	scene->addGameObject(bar1);
}

rockSystem::~rockSystem()
{
}
void rockSystem::update(std::vector<vg::GameObject*> *gameObjects, float deltaTime)
{
#ifdef OS_WINDOWS
	if (vg::input::Keyboard::getKeyState(vg::input::Keyboard::E) == vg::input::Keyboard::KeyState::PRESSED)
	{
		rock->getComponent<PhysicsPolygonComponent>()->setVelocity(Vector2<float>(100, 100));
	}
#endif

}
