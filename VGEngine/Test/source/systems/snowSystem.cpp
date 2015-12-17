
#pragma once

#include "systems/snowSystem.h"

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
#include "SnowComponent.h"
#include <vector>

using namespace vg;
using namespace vg::graphics;

snowSystem::snowSystem(Scene *scene)
{
	int max = 150;
	int increase = 20;
	for (int i = 0; i < max; i++)
	{
		Vec2f startPos;
		if (i < max / 8)
			startPos = vg::Vec2f(0, i * increase);
		else
			startPos = vg::Vec2f((i - max / 8) * increase, 0);

		TransformComponent *snowTransform = new TransformComponent(startPos,
			Vec2f(8, 8), 0.0f,Vec2f(0,0), TransformComponent::HIGH, false);

		GameObject *snowFlake = new GameObject("snowFlake");
		RenderComponent *snowRender = new RenderComponent("doge_white.png");
		snowRender->setColor(vg::Color(255, 255, 255, 255));

		snowFlake->addComponent(snowTransform);
		snowFlake->addComponent(snowRender);

		snowFlake->addComponent(new SnowComponent(startPos,vg::Vec2f(rand () % 200,rand () % 200)));
		scene->addGameObject(snowFlake);
	}
}

snowSystem::~snowSystem()
{

}
void snowSystem::update(std::vector<vg::GameObject*> *gameObjects, float deltaTime)
{
	for (auto it = gameObjects->begin(); it != gameObjects->end(); it++)
	{
		if ((*it)->getName() == "snowFlake")
		{
			TransformComponent* trans = (*it)->get<TransformComponent>();
			SnowComponent *snow = (*it)->get<SnowComponent>();
			if (trans != nullptr)
				trans->move(Vec2f(deltaTime * snow->velocity.x, deltaTime * snow->velocity.y));

			if (trans->getWorldPosition().y > Screen::getSize().y)
			{
				trans->setY(-trans->getSize().y);
				trans->setX(0.0f);
				trans->setPosition(snow->startPos);
			}
		}
	}
}