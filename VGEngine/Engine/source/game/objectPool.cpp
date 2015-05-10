
#include "engine\game\objectPool.h"
#include "engine/game/transformComponent.h"

#include <algorithm>

using namespace vg;
using namespace std;

ObjectPool::ObjectPool()
{
	//loaded = false;
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
std::vector<GameObject*>::iterator ObjectPool::removeGameObject(GameObject *gObject)
{
	auto it = std::find(mActivePool.begin(), mActivePool.end(), gObject);
	if (it != mActivePool.end())
	{
		auto tempIt = mActivePool.erase(it);
		delete gObject;
		gObject = nullptr;
		return tempIt;
	}
	return it;
}


void ObjectPool::updateGameObjects()
{
	sortActivePool();
	mSystemManager.update(&mActivePool);
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