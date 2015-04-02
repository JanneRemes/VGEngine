#include "engine\game\objectPool.h"
using namespace vg;
ObjectPool::ObjectPool()
{
	//loaded = false;
	mComponentSystemManager = ComponentSystemManager();
}


ObjectPool::~ObjectPool()
{
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
void ObjectPool::addGameObject(GameObject gObject)
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
void  ObjectPool::updateGameObjects()
{
	for (auto it = mActivePool.begin(); it != mActivePool.end(); it++)
	{
		mComponentSystemManager.update(&(*it));
	}
}