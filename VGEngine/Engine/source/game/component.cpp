
#include "engine/game.h"

using namespace vg;

void Component::setGameObject(GameObject *gameObject)
{
	mGameObject = gameObject;
}
GameObject *Component::getGameObject()
{
	return mGameObject;
}