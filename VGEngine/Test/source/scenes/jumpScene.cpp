
#include "scenes/jumpScene.h"

#include "engine/game/transformComponent.h"
#include "engine/game/quadrangleComponent.h"
#include "systems/sceneChangeSystem.h"
#include "engine/game/animationComponent.h"
#include "engine/game/textComponent.h"
#include "engine/game/game.h"

#include "systems\jumpSystem.h"

using namespace vg;

JumpScene::JumpScene()
{
}

JumpScene::~JumpScene()
{
}

void JumpScene::loadObjects()
{
	core::AssetManager* assetManager = Game::getInstance()->getAssetManager();
	


	// 2nd physics object
	TransformComponent *physicsTransform2 = new TransformComponent(Vec2f(500, 500),
		Vec2f(500, 200), 45);

	GameObject *physicsTest2 = new GameObject("physicsTest2");
	QuadrangleComponent *physicsRender2 = new QuadrangleComponent("koala.png");

	PhysicsComponent *physicsPolyComponent2 = new PhysicsComponent(physicsTransform2, PhysicsComponent::STATIC);

	physicsTest2->addComponent(physicsPolyComponent2);
	physicsTest2->addComponent(physicsTransform2);
	physicsTest2->addComponent(physicsRender2);

	addGameObject(physicsTest2);


	// Jump systems
	JumpSystem *jumpSystem = new JumpSystem(this);
	Game::getInstance()->addComponentSystem(this, jumpSystem);
	
	// Scene change system
	sceneChangeSystem *sceneChange = new sceneChangeSystem(this);
	Game::getInstance()->addComponentSystem(this, sceneChange);
}
