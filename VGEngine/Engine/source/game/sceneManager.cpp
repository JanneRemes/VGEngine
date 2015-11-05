#include "engine\graphics\camera.h"
#include "engine/game/sceneManager.h"
#include "engine/game/scene.h"

#include <utility>

using namespace vg;

SceneManager::SceneManager(){
	mSceneChanged = false;
	mActiveScene = nullptr;
};

SceneManager::~SceneManager()
{
	//mActiveScene->~Scene();
	
	for (auto it = mSceneTemplates.begin(); it != mSceneTemplates.end(); it++)
	{
		delete (*it).second;
		it = mSceneTemplates.erase(it);
	}
}

void SceneManager::draw()
{
	mActiveScene->draw();
}

void SceneManager::update(float deltaTime)
{

	if (mActiveScene == nullptr)
		return;
	if (!mActiveScene->getPaused())
		{
			mActiveScene->updateGameObjects(deltaTime);
			mActiveScene->update(deltaTime);
		}
	
}


void SceneManager::changeScene(string key)
{

	for (auto it = mSceneTemplates.begin(); it != mSceneTemplates.end(); it++)
	{
		if (it->first == key)
		{
			if (mActiveScene != nullptr)
			{
				mActiveScene->clearSystems();
				mActiveScene->clearObjects();
			}
			graphics::Camera::setPosition(Vector2<float>(0, 0));
			graphics::Camera::setZoom(1.0f);

			mActiveScene = it->second;


			mActiveScene->loadObjects();
			
		}
	}
}



void SceneManager::addTemplateScene(string key,Scene *scene)
{
	mSceneTemplates.insert(std::make_pair(key,scene));
}

Scene* SceneManager::getActiveScene()
{
	return mActiveScene;
}