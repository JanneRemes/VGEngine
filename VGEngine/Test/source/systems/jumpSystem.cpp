
#include "systems/jumpSystem.h"

#ifdef OS_WINDOWS
#include "engine/input/mouse.h"
#include "engine\input\keyboard.h"
#endif
#ifdef OS_ANDROID
#include "engine/input/touch.h"
#endif

#include "engine/game/quadrangleComponent.h"
#include "engine/game/game.h"
#include "engine/game/physicsCircleComponent.h"
#include "engine/game/physicsPolygonComponent.h"
#include "engine/game/animationComponent.h"
#include "engine/game/animationSystem.h"
#include "engine/utility/random.h"
#include "engine/graphics/screen.h"
#include "engine/utility/timer.h"

using namespace vg;
using namespace vg::graphics;
JumpSystem::JumpSystem(Scene *scene)
{
	this->scene = scene;
	system = Game::getInstance()->getSceneManager()->getActiveScene()->getComponentSystemManager()->getSystem<PhysicsSystem>();
	system->createBorders(0, 0, Screen::getX(), Screen::getY());


}
void JumpSystem::update(std::vector<vg::GameObject*> *gameObjects, float deltaTime)
{

#ifdef OS_WINDOWS
	
#endif


#ifdef OS_ANDROID
	
#endif
}