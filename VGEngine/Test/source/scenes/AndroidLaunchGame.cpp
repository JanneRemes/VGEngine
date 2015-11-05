#include "Scenes\AndroidLaunchGame.h"

#include "systems/PhysicsTestSystem.h"
#include "engine/game/transformComponent.h"
#include "engine/game/triangleComponent.h"
#include "engine/game/quadrangleComponent.h"
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
	core::AssetManager* assetManager = Game::getInstance()->getAssetManager();
	GameObject *android = new GameObject("Android");
	TransformComponent *androidTransform = new TransformComponent(Vector2<float>(64, 64),
		Vector2<float>(128, 128), 0.0f, 0, Vector2<float>(64, 64));
	android->addComponent(androidTransform);
	QuadrangleComponent *quadre = new QuadrangleComponent("android.png");
	android->addComponent(quadre);
	addGameObject(android);
}