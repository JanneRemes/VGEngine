
#include "engine/game/deleteSystem.h"

#include "engine/game/game.h"
#include "engine/game/gameObject.h"

using namespace vg;
using namespace std;

DeleteSystem::DeleteSystem() :vg::System()
{
	mPriority = System::FIRST;
}

DeleteSystem::~DeleteSystem()
{

}

void DeleteSystem::update(vector<GameObject*>* gameObjects,float deltaTime)
{
	for (vector<GameObject*>::iterator i = gameObjects->begin(); i != gameObjects->end(); i++)
	{
		if (*i == nullptr)
			continue;
		if ((*i)->markedForDelete())
		{
			delete *i;
			*i = nullptr;
			i = gameObjects->erase(i);
		}
	}
}

void DeleteSystem::setScene(Scene* scene)
{
	mScene = scene;
}