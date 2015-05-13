#include "Test\EnemySystem.h"
#include <engine\game\transformComponent.h>
#include <engine\game\quadrangleComponent.h>
#include <engine\utility\random.h>
#include <engine\utility\vector2.h>
using namespace vg;
EnemySystem::EnemySystem(Game *game) :mGame(game)
{
	mEnemyPrefab = new GameObject("enemy");
	TransformComponent *transform = new TransformComponent(Vector2<int>(0.0f, 0.0f),
		Vector2<int>(80, 80), 0.0f, 0u);
	transform->setOrigin(vg::Vector2<int>(40, 40));
	mEnemyPrefab->addComponent(transform);
	QuadrangleComponent *quadre = mGame->getFactory()->createRenderComponent<QuadrangleComponent>("koala.png");
	mEnemyPrefab->addComponent(quadre);
	mSpawnTimer.restart();
	mSpawnDelay = 0.0f;
}



EnemySystem::~EnemySystem()
{
}
void EnemySystem::update(std::vector<vg::GameObject*> *gameObjects)
{
    int screenWidth = Game::getInstance()->getGraphics()->getScreenWidth();
	if (mSpawnTimer.getCurrentTimeSeconds() >= mSpawnDelay)
	{
		GameObject *gameObject = new GameObject(*mEnemyPrefab);
        Vector2<int> temppos(Random::nexti(45, screenWidth - 45), -10.0f);
		gameObject->getComponent<TransformComponent>()->setPosition(temppos);
		unsigned int size = gameObjects->size();
		mScene->getObjectPool()->addGameObject(gameObject);
		mSpawnDelay = Random::nextf(1.0, 3.5);
		mSpawnTimer.restart();
	}
	for (auto it = gameObjects->begin(); it != gameObjects->end(); it++)
	{
		if ((*it)->getName() == "enemy")
		{
			TransformComponent *comp = (*it)->getComponent<TransformComponent>();
			(*it)->getComponent<TransformComponent>()->setPosition(Vector2<int>(comp->getPosition().getX(), comp->getPosition().getY() + 5));
			if (comp->getPosition().getY() > 1500.0f)
			{
				it= mScene->getObjectPool()->removeGameObject((*it));
			}
			for (auto ij = gameObjects->begin(); ij != gameObjects->end(); ij++)
			{
				if ((*ij)->getName() == "bullet")
				{
					TransformComponent *btransf = (*ij)->getComponent<TransformComponent>();
					if (Vector2<int>::Distance(btransf->getPosition(), comp->getPosition()) < 40.0f)
					{
						it = mScene->getObjectPool()->removeGameObject((*it));
                        if (it == gameObjects->end())
                            return;
                        else
						    break;
					}
				}
			}
		}
	}
}