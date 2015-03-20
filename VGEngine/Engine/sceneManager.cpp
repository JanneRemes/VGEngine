#include "sceneManager.h"
#include "engine/graphics/graphics.h"
using namespace vg;

sceneManager::~sceneManager()
{
}

void sceneManager::draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	for (vector<Scene*>::iterator it = mCurrentScenes.begin(); it != mCurrentScenes.end(); it++)
	{
		(*it)->draw();
	}
}

void sceneManager::update(float dt)
{
	for (vector<Scene*>::iterator it = mCurrentScenes.begin(); it != mCurrentScenes.end(); it++)
	{
		if (!(*it)->getPaused())
		{
			(*it)->update(dt);
		}
		if (mSceneChanged)
		{
			mSceneChanged = false;
			break;
		}
	}
}

void sceneManager::openScene(Scene *scene)
{
	mCurrentScenes.push_back(scene);
	mSceneChanged = true;
}

void sceneManager::changeScene(Scene *scene)
{
	emptyScenes();
	openScene(scene);
}

void sceneManager::emptyScenes()
{
	if (mCurrentScenes.size() > 0)
	{
		for (vector<Scene*>::iterator it = mCurrentScenes.begin(); it != mCurrentScenes.end(); it++)
			delete (*it);
	}
	mCurrentScenes.clear();
}

void sceneManager::closeCurrentScene()
{
	if (mCurrentScenes.size() > 0)
	{
		delete mCurrentScenes.back();
		mCurrentScenes.pop_back();
		mSceneChanged = true;
	}
}
