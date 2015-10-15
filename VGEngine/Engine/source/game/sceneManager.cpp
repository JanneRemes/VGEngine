
#include "engine/game/sceneManager.h"
#include "engine/graphics/graphics.h"
#include "engine/game/scene.h"
#include <utility> 
#include "engine\graphics\opengl.h"
using namespace vg;
using namespace vg::graphics::gl;
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
	clear(getGL_COLOR_BUFFER_BIT());

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
	if (mActiveScene != nullptr)
		mActiveScene->clearObjects();
	for (auto it = mSceneTemplates.begin(); it != mSceneTemplates.end(); it++)
	{
		if (it->first == key)
		{
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