#ifdef OS_WINDOWS
#include "engine/input/mouse.h"
#endif

#include "Scenes\AndroidLaunchGame.h"
#include "engine\game.h"
#include "systems\sceneChangeSystem.h"
#include "engine/game/transformComponent.h"
#include "engine/game/triangleComponent.h"
#include "engine/game/quadrangleComponent.h"
#include "engine/game/PhysicsComponent.h"
#include "engine/game/textComponent.h"
#include "engine/game/physicsComponent.h"
#include "engine/game/animationComponent.h"
#include "engine/game/animationSystem.h"

using namespace vg;

AndroidLaunchGame::AndroidLaunchGame()
{

}

AndroidLaunchGame::~AndroidLaunchGame()
{
}
void AndroidLaunchGame::loadObjects()
{
	// Scene change system
	sceneChangeSystem *sceneChange = new sceneChangeSystem(this);
	Game::getInstance()->addComponentSystem(this, sceneChange);

	AndroidLaunchSystem *androidLaunch = new AndroidLaunchSystem(this);
	Game::getInstance()->addComponentSystem(this, androidLaunch);
}

void AndroidLaunchGame::update(std::vector<vg::GameObject*> *gameObjects, float deltaTime)
{
	
}