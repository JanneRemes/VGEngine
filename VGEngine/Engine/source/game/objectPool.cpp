
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
/*
void ObjectPool::createGameObjectPool(std::vector<PoolObjectType> *prefabs)
{
	for (auto it = prefabs->begin(); it != prefabs->end(); it++)
	{
		addPrefabToPool((*it));
	}
	loaded = true;
}
void ObjectPool::addPrefabToPool(PoolObjectType type)
{
	for (int i = 0; i < type.amount; i++)
		mInactivePool.push_back(*type.prefab);
}*/
void ObjectPool::addGameObject(GameObject *gObject)
{
	/*GameObject* pooledObject = getGameObjectFromPool(gObject.getName());
	if (pooledObject == nullptr)
	{*/
		mActivePool.push_back(gObject);
	/*}
	else
	{
		mActivePool.push_back(*pooledObject);
		removeGameObjectInactivePool(*pooledObject);
	}*/
}
/*
GameObject *ObjectPool::getGameObjectFromPool(std::string name)
{
	for (auto it = mInactivePool.begin(); it != mInactivePool.end(); it++)
	{
		if ((*it).getName() == name)
		{
			return &(*it);
		}
	}
}
void ObjectPool::removeGameObjectInactivePool(GameObject gObject)
{
	for (auto it = mInactivePool.begin(); it != mInactivePool.end(); it++)
	{
		if ((*it).getName() == gObject.getName())
		{
			mInactivePool.erase(it);
		}
	}
}*/

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
		int layerA = -1;
		int layerB = -1;
		if (transformA != nullptr)
			layerA = transformA->getLayer();
		if (transformB != nullptr)
			layerB = transformB->getLayer();
		return layerA < layerB;
	});
}