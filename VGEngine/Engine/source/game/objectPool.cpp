
#include "engine\game\objectPool.h"
#include "engine/game/transformComponent.h"

#include <algorithm>

using namespace vg;
using namespace std;

ObjectPool::ObjectPool()
{
	mSystemManager = SystemManager();
}


ObjectPool::~ObjectPool()
{
	for (int i = 0; i < mActivePool.size(); i++)
	{
		delete mActivePool[i];
	}
}

void ObjectPool::addGameObject(GameObject *gObject)
{

		mActivePool.push_back(gObject);

}

void ObjectPool::updateGameObjects(float deltaTime)
{
	sortActivePool();
	mSystemManager.update(&mActivePool,deltaTime);
}

void ObjectPool::sortActivePool()
{
	sort(mActivePool.begin(), mActivePool.end(),
		[](GameObject* a, GameObject* b)-> bool
	{
		TransformComponent* transformA = a->getComponent<TransformComponent>();
		TransformComponent* transformB = b->getComponent<TransformComponent>();
		float layerA = -1.0f;
		float layerB = -1.0f;
		if (transformA != nullptr)
			layerA = transformA->getLayer();
		if (transformB != nullptr)
			layerB = transformB->getLayer();
		return layerA < layerB;
	});
}