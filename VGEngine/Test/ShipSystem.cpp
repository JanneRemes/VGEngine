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
	//mBullet->addComponent(transform);
	//mScene = gamescene;
	Random::seed();
}


ShipSystem::~ShipSystem()
{
}
void ShipSystem::update(std::vector<vg::GameObject*> *gameObjects)
{
	for (auto it = gameObjects->begin(); it != gameObjects->end(); it++)
	{
		if ((*it)->getName() == "dip")
		{
			TransformComponent *comp = (*it)->GetComponent<TransformComponent>();
			(*it)->GetComponent<TransformComponent>()->setPosition( Vector2<int>(comp->getPosition().getX(), comp->getPosition().getY() -5));
		}
		if ((*it)->getName() == "ship")
		{
			Vector2<int> resolution(Game::getInstance()->getGraphics()->getContext()->getWidth(),
				Game::getInstance()->getGraphics()->getContext()->getHeight());


			Vector2<float> mScreenSize = Vector2<float>(mGame->getGraphics()->getContext()->getWidth(),
				mGame->getGraphics()->getContext()->getHeight());
			TransformComponent* transformComponent = (*it)->GetComponent<TransformComponent>();
			
			Vector2<int> newPos(
				((mScreenSize.getX()/ 20 * (Input::Input::getSensorX() + 10) - mScreenSize.getX()) * -1), 
				resolution.getY()-80);
			if (sqrt(pow(newPos.getX() - transformComponent->getPosition().getX(), 2)) > 15.0f)
			{
				transformComponent->setPosition(newPos);
			}
			if (Input::Input::getIsTouchReleased())
			{
				GameObject *dip = new GameObject("dip");
				TransformComponent *dippitransform = new TransformComponent(Vector2<int>(transformComponent->getPosition().getX(), transformComponent->getPosition().getY()),
					Vector2<int>(32, 32), 0.0f, 0u);
				dip->addComponent(dippitransform);
				QuadrangleComponent *dippiquadre = mGame->getFactory()->createRenderComponent<QuadrangleComponent>("koalapanos.png");
				dip->addComponent(dippiquadre);

				mScene->getObjectPool()->addGameObject(dip);
				break;
			}
		}
	}
}
