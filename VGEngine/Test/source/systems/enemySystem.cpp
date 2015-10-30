
#include "systems/enemySystem.h"

#include "engine/game/transformComponent.h"
#include "engine/game/quadrangleComponent.h"
#include "engine/game/textComponent.h"
#include "engine/utility/random.h"
#include "engine/utility/vector2.h"
#include "engine/graphics/screen.h"

#include <sstream>

using namespace vg;
using namespace vg::graphics;

EnemySystem::EnemySystem()
:  mEnemyCount(0), mSpawnDelay(0), mBulletCount(0)
{
	mEnemyPrefab = new GameObject("enemy");
	TransformComponent *transform = new TransformComponent(Vector2<float>(0.0f, 0.0f),
		Vector2<float>(80, 80), 0.0f, 0u);
	transform->setOrigin(vg::Vector2<float>(40, 40));
	mEnemyPrefab->addComponent(transform);
	QuadrangleComponent *quadre = new QuadrangleComponent("koala.png");
	mEnemyPrefab->addComponent(quadre);
	mSpawnTimer.restart();
	fpsTimer.restart();
}

EnemySystem::~EnemySystem()
{
}

void EnemySystem::update(std::vector<vg::GameObject*> *gameObjects,float deltaTime)
{
	int screenWidth = Screen::getX();
	int screenHeight = Screen::getY();
	if (mSpawnTimer.getCurrentTimeSeconds() >= mSpawnDelay)
	{
		GameObject *gameObject = new GameObject(*mEnemyPrefab);
		Vector2<float> temppos(Random::nexti(45, screenWidth - 45), -10.0f);
		gameObject->getComponent<TransformComponent>()->setPosition(temppos);
		unsigned int size = gameObjects->size();
		mScene->addGameObject(gameObject);
		mSpawnDelay = Random::nextf(1.0, 3.5);
		mSpawnTimer.restart();
	}

	int tempEnemyCount = 0;
	for (auto i = gameObjects->begin(); i != gameObjects->end(); i++)
	{
		if ((*i)->getName() == "enemyText")
		{
			TextComponent* text = (*i)->getComponent<TextComponent>();
			if (text != nullptr)
			{
				std::stringstream stream;
				stream << "Enemies: " << mEnemyCount;
				text->setText(stream.str());
			}
		}
		else if ((*i)->getName() == "bulletText")
		{
			TextComponent* text = (*i)->getComponent<TextComponent>();
			if (text != nullptr )
			{
				std::stringstream stream;
				stream << "Bullets: " << mBulletCount;
				text->setText(stream.str());
				
			}
		}
		else if((*i)->getName() == "fpsText")
		{
			TextComponent* text = (*i)->getComponent<TextComponent>();
			if (text != nullptr && fpsTimer.getCurrentTimeSeconds() >= 0.5f)
			{
				std::stringstream stream;
				stream << "FPS: " << (int)(1/deltaTime);
				text->setText(stream.str());
				fpsTimer.restart();
			}
		}
		else if ((*i)->getName() == "enemy")
		{
			tempEnemyCount++;
			TransformComponent *comp = (*i)->getComponent<TransformComponent>();
			comp->move(Vector2<float>(0, 500 *deltaTime));
			comp->rotate(2.0f);
			if (comp->getWorldPosition().getY() - comp->getOrigin().getY() > screenHeight)
			{
				(*i)->markForDelete();
			}
				
			int tempBulletCount = 0;
			for (auto j = gameObjects->begin(); j != gameObjects->end(); j++)
			{
				if ((*j)->getName() == "bullet")
				{
					tempBulletCount++;
					TransformComponent *btransf = (*j)->getComponent<TransformComponent>();
					if (Vector2<float>::Distance(btransf->getWorldPosition(), comp->getWorldPosition()) 
						< (comp->getSize().getX() + comp->getSize().getY()) / 2.0f)
						(*i)->markForDelete();
				}
			}
			mBulletCount = tempBulletCount;
		}
	}
	mEnemyCount = tempEnemyCount;
}

void EnemySystem::setScene(Scene* scene)
{
	mScene = scene;
}