
#pragma once

#include "ShipSystem.h"

#include "engine/input/input.h"
#include "engine/game/game.h"
#include "engine/utility/Vector2.h"
#include "engine/game/transformComponent.h"
#include "engine/game/quadrangleComponent.h"
#include "engine/utility/random.h"

using namespace vg;

ShipSystem::ShipSystem(Game *game) :System()
{
	mGame = game;
	Random::seed();
    mCoolDown = 0.25f;
    mCoolDownTimer.restart();

	whyudodis = new GameObject("bullet");

	TransformComponent *transform = new TransformComponent(Vector2<int>(0.0f, 0.0f),
		Vector2<int>(32, 32), 0.0f, 0u, Vector2<int>(16, 16));
	whyudodis->addComponent(transform);
	QuadrangleComponent *quadre = mGame->getFactory()->createRenderComponent<QuadrangleComponent>("koalapanos2.png");
	whyudodis->addComponent(quadre);
}


ShipSystem::~ShipSystem()
{
}
void ShipSystem::update(std::vector<vg::GameObject*> *gameObjects)
{
	Vector2<int> resolution(Game::getInstance()->getGraphics()->getContext()->getWidth(),
		Game::getInstance()->getGraphics()->getContext()->getHeight());
	for (auto it = gameObjects->begin(); it != gameObjects->end(); it++)
	{
		if ((*it)->getName() == "bullet")
		{
			TransformComponent *comp = (*it)->getComponent<TransformComponent>();
			comp->move(Vector2<int>(0, -10));
			if (comp->getPosition().getY() < 0)
				it = mScene->getObjectPool()->removeGameObject((*it));
			if (it == gameObjects->end())
				break;
		}
		else if ((*it)->getName() == "ship")
		{
			Vector2<float> mScreenSize = Vector2<float>(mGame->getGraphics()->getContext()->getWidth(),
				mGame->getGraphics()->getContext()->getHeight());
			TransformComponent* transformComponent = (*it)->getComponent<TransformComponent>();
			
			Vector2<int> newPos(
				((mScreenSize.getX()/ 20 * (Input::Input::getSensorX() + 10) - mScreenSize.getX()) * -1), 
				resolution.getY()-80);
			if (sqrt(pow(newPos.getX() - transformComponent->getPosition().getX(), 2)) > 15.0f)
			{
				transformComponent->setPosition(newPos);
			}
            if (Input::Input::getIsTouchReleased() && mCoolDownTimer.getCurrentTimeSeconds() > mCoolDown)
			{
                sound::Sound* testSound = new sound::Sound("shoot.mp3");
                testSound->load(Game::getInstance()->getFileManager());
                Game::getInstance()->getAudioManager()->addSound(*testSound);

				GameObject *g = new GameObject(*whyudodis);
				Vector2<int> temppos(transformComponent->getPosition().getX(),
					transformComponent->getPosition().getY() - transformComponent->getOrigin().getY());
				g->getComponent<TransformComponent>()->setPosition(temppos);
				
				mScene->getObjectPool()->addGameObject(g);
                mCoolDownTimer.restart();
				break;
			}
		}
	}
}
