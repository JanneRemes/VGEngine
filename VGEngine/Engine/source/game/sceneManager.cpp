#include "engine/game/sceneManager.h"
#include "engine/graphics/graphics.h"
#include <utility> 
using namespace vg;
SceneManager::SceneManager(){
	mSceneChanged = false; 
	//mSceneTemplates = map<string, Scene*>(); TODO: remove
};
SceneManager::~SceneManager()
{
}

void SceneManager::draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	for (vector<Scene*>::iterator it = mCurrentScenes.begin(); it != mCurrentScenes.end(); it++)
	{
		(*it)->draw();
	}
}

void SceneManager::update(float dt)
{
	for (vector<Scene*>::iterator it = mCurrentScenes.begin(); it != mCurrentScenes.end(); it++)
	{
		if (!(*it)->getPaused())
		{
			(*it)->mObjectPool.updateGameObjects();//TODO remove
			(*it)->update(dt);
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
