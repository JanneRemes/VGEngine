#include "engine/game/System.h"
using namespace vg;
System::System()
{
	mPriority = NORMAL;
}


System::~System()
{
}
void System::update(std::vector<GameObject*> *gameObjects,float deltaTime)
{

}