
#pragma once

#include "systems/ShipSystem.h"

#include "engine/input/sensor.h"
#include "engine/game/game.h"
#include "engine/utility/vec2f.h"
#include "engine/game/transformComponent.h"
#include "engine/game/quadrangleComponent.h"
#include "engine/utility/random.h"
#include "engine/input/touch.h"
#include "engine/graphics/screen.h"

#include <vector>

using namespace vg;
using namespace vg::graphics;

ShipSystem::ShipSystem() :System()
{
	Random::seed();
    mCoolDown = 0.25f;
    mCoolDownTimer.restart();

	core::AssetManager* assetManager = Game::getInstance()->getAssetManager();
	mBullet = new GameObject("bullet");
	if ((assetManager->get<sound::Sound>("shoot.mp3")) == nullptr)
		assetManager->load<sound::Sound>("shoot.mp3");

	TransformComponent *transform = new TransformComponent(Vec2f(0.0f, 0.0f),
		Vec2f(32, 32), 0.0f, Vec2f(16, 16));
	mBullet->addComponent(transform);
	QuadrangleComponent *quadre = new QuadrangleComponent("koalapanos2.png");
	mBullet->addComponent(quadre);
}


ShipSystem::~ShipSystem()
{
}
void ShipSystem::update(std::vector<vg::GameObject*> *gameObjects,float deltaTime)
{
	for (auto it = gameObjects->begin(); it != gameObjects->end(); it++)
	{
		if ((*it)->getName() == "bullet")
		{
			TransformComponent *comp = (*it)->getComponent<TransformComponent>();
			comp->move(Vec2f(0, -10));
			if (comp->getWorldPosition().y < 0)
				(*it)->markForDelete();
		}
		else if ((*it)->getName() == "ship")
		{
			Vec2f mScreenSize = Vec2f(Screen::getX(), Screen::getY());
			TransformComponent* transformComponent = (*it)->getComponent<TransformComponent>();
			
			Vec2f newPos(
				((mScreenSize.x/ 20 * (input::Sensor::getSensorX() + 10) - mScreenSize.x) * -1), 
				mScreenSize.y-80);
			if (sqrt(pow(newPos.x - transformComponent->getWorldPosition().x, 2)) > 15.0f)
			{
				transformComponent->setPosition(newPos);
			}
			if (input::Touch::getIsReleased() && mCoolDownTimer.getCurrentTimeSeconds() > mCoolDown)
			{
				core::AssetManager* assetManager = Game::getInstance()->getAssetManager();
				sound::Sound* sound = assetManager->get<sound::Sound>("shoot.mp3");
                Game::getInstance()->getAudioManager()->addSound(*sound);

				GameObject *g = new GameObject(*mBullet);
				Vec2f temppos(transformComponent->getWorldPosition().x,
					transformComponent->getWorldPosition().y - transformComponent->getOrigin().y);
				g->getComponent<TransformComponent>()->setPosition(temppos);
				
				mScene->addGameObject(g);
                mCoolDownTimer.restart();
				break;
			}
		}
	}
}
