
#include "engine/game.h"

using namespace vg;
void GameObject::setIsPooled(bool isPooled)
{
	mIsPooled = isPooled;
}
bool GameObject::getIsPooled()
{
	return mIsPooled;
}