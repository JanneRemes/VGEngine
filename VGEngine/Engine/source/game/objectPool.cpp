#include "engine\game\objectPool.h"
using namespace vg;
ObjectPool::ObjectPool()
{
	loaded = false;
}


ObjectPool::~ObjectPool()
{
}
void ObjectPool::addPrefabType(GameObject gameObject, int amount)
{
	PoolObjectType prefab(gameObject, amount);
	mPoolPrefabs.push_back(prefab);
	if (loaded)
	{
		addPrefabToPool(prefab);
	}
}
void ObjectPool::removePrefabType(GameObject gameObject, bool clear)
{
	if (clear)
	{
		//TODO clear all gameobjects
	}
	else
	{
		//set all inactive gameobjects with type not pooled
	}
}
void ObjectPool::createGameObjectPool()
{
	for (auto it = mPoolPrefabs.begin(); it != mPoolPrefabs.end(); it++)
	{
		addPrefabToPool((*it));
	}
	loaded = true;
}
void ObjectPool::addPrefabToPool(PoolObjectType type)
{
	for (int i = 0; i < type.amount; i++)
		mInactivePool.push_back(type.prefab);
}