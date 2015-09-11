
#include "engine/game/sceneManager.h"
#include "engine/graphics/graphics.h"
#include "engine/game/scene.h"
#include <utility> 

using namespace vg;

SceneManager::SceneManager(){
	mSceneChanged = false;
};

SceneManager::~SceneManager()
{
	emptyScenes();
}

void SceneManager::draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	for (vector<Scene*>::iterator it = mCurrentScenes.begin(); it != mCurrentScenes.end(); it++)
	{
		(*it)->draw();
	}
}

void SceneManager::update(float deltaTime)
{
	int size = mCurrentScenes.size();
	for (vector<Scene*>::iterator it = mCurrentScenes.begin(); it != mCurrentScenes.end(); it++)
	{
		if ((*it) == nullptr)
			continue;
		if (!(*it)->getPaused())
		{
			(*it)->getObjectPool()->updateGameObjects(deltaTime);
			(*it)->update(deltaTime);
		}
		if (mSceneChanged)
		{
			mSceneChanged = false;
			break;
		}
	}
}

void SceneManager::openScene(Scene *scene)
{
	mCurrentScenes.push_back(scene);
	mSceneChanged = true;
}

void SceneManager::changeScene(Scene *scene)
{
	emptyScenes();
	openScene(scene);
}

void SceneManager::emptyScenes()
{
	if (mCurrentScenes.size() > 0)
	{
		for (vector<Scene*>::iterator it = mCurrentScenes.begin(); it != mCurrentScenes.end(); it++)
			delete (*it);
	}
	mCurrentScenes.clear();
}

void SceneManager::closeCurrentScene()
{
	if (mCurrentScenes.size() > 0)
	{
		delete mCurrentScenes.back();
		mCurrentScenes.pop_back();
		mSceneChanged = true;
	}
}

void SceneManager::addTemplateScene(string key,Scene *scene)
{
	mSceneTemplates.insert(std::make_pair(key, new Scene(*scene)));
}
