
#include "engine/game.h"
#include <algorithm>
using namespace vg;
void GameObject::addComponent(Component* component)
{
	mComponents.insert(std::make_pair(&typeid(*component), component));
}