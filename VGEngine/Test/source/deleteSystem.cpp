
#include "deleteSystem.h"

#include <engine/game/game.h>
#include <engine/game/gameObject.h>

using namespace vg;
using namespace std;

DeleteSystem::DeleteSystem(Game* game)
	: mGame(game)
{

}

DeleteSystem::~DeleteSystem()
{

}

void DeleteSystem::update(vector<GameObject*>* gameObjects)
{
	for (vector<GameObject*>::iterator i = gameObjects->begin(); i != gameObjects->end(); i++)
	{
		if ((*i)->markedForDelete())
		{
			delete *i;
			i = gameObjects->erase(i);
		}
	}
}

void DeleteSystem::setScene(Scene* scene)
{
	mScene = scene;
}