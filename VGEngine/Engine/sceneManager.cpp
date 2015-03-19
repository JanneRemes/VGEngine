#include "sceneManager.h"
#include "engine/graphics/graphics.h"
using namespace vg;

sceneManager::sceneManager()
{
}


sceneManager::~sceneManager()
{
}

void sceneManager::draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	for (vector<Scene*>::iterator it = currentScenes.begin(); it != currentScenes.end(); it++)
	{
		(*it)->draw();
	}
}

void sceneManager::update(float dt)
{
	for (vector<Scene*>::iterator it = currentScenes.begin(); it != currentScenes.end(); it++)
	{
		if (!(*it)->getPaused())
		{
			(*it)->update(dt);
		}
		if (sceneChanged)
		{
			sceneChanged = false;
			break;
		}
	}
}

void sceneManager::openScene(Scene *scene)
{
	currentScenes.push_back(scene);
	sceneChanged = true;
}

void sceneManager::changeScene(Scene *scene)
{
	emptyScenes();
	openScene(scene);
}

void sceneManager::emptyScenes()
{
	if (currentScenes.size() > 0)
	{
		for (vector<Scene*>::iterator it = currentScenes.begin(); it != currentScenes.end(); it++)
			delete (*it);
	}
	currentScenes.clear();
}

void sceneManager::closeCurrentScene()
{
	if (currentScenes.size() > 0)
	{
		delete currentScenes.back();
		currentScenes.pop_back();
		sceneChanged = true;
	}
}
