#include "Scenes\rockThrowScene.h"
#include "systems\rockSystem.h"


#include "engine/game/game.h"
#include "engine/game/transformComponent.h"
#include "engine/game/renderComponent.h"
#include "engine/game/physicsComponent.h"
#include "engine/game/PhysicsComponent.h"
#include "systems\sceneChangeSystem.h"

using namespace vg;

rockThrowScene::rockThrowScene()
{
}

rockThrowScene::~rockThrowScene()
{
}

void rockThrowScene::loadObjects()
{
	core::AssetManager* assetManager = Game::getInstance()->getAssetManager();

	rockSystem *rocksystem = new rockSystem(this);
	Game::getInstance()->addComponentSystem(this, rocksystem);

	// Scene change system
	sceneChangeSystem *sceneChange = new sceneChangeSystem(this);
	Game::getInstance()->addComponentSystem(this, sceneChange);
}