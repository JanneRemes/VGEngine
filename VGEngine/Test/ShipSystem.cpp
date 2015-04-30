#include "ShipSystem.h"

#include "engine/input/input.h"
#include "engine/game/game.h"
#include "engine/utility/Vector2.h"
#include "engine/game/transformComponent.h"
#include "engine/game/quadrangleComponent.h"
using namespace vg;
ShipSystem::ShipSystem() :System()
{
	mBullet = new GameObject("bullet");
	QuadrangleComponent *quadre = Game::getInstance()->getFactory()->createRenderComponent<QuadrangleComponent>("koalapanos.png");
	mBullet->addComponent(quadre);
}


ShipSystem::~ShipSystem()
{
}
void ShipSystem::update(std::vector<vg::GameObject*> *gameObjects)
{
	for (auto it = gameObjects->begin(); it != gameObjects->end(); it++)
	{
		if ((*it)->getName() == "ship")
		{
			Vector2<float> mScreenSize = Vector2<float>(Game::getInstance()->getGraphics()->getContext()->getWidth(),
				Game::getInstance()->getGraphics()->getContext()->getHeight());
			TransformComponent* transformComponent = (*it)->GetComponent<TransformComponent>();
			Vector2<int> newPos(((mScreenSize.getX()/ 20 * (Input::Input::getSensorX() + 10) - mScreenSize.getX()) * -1), 400);
			if (sqrt(pow(newPos.getX() - transformComponent->getPosition().getX(), 2)) > 15.0f)
			{
				transformComponent->setPosition(newPos);
			}
			if (Input::Input::getIsTouchReleased())
			{
	
				TransformComponent *transform = new TransformComponent(Vector2<int>(transformComponent->getPosition().getX(), transformComponent->getPosition().getY()),
					Vector2<int>(80, 80), 0.0f, 1u);
				mBullet->addComponent(transform);

				//myScene->getObjectPool()->addGameObject(mBullet);
			}
			//Input::Input::
		}
	}
}