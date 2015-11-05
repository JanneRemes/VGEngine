
#include "scenes/pappaScene.h"

#include "engine/game/transformComponent.h"
#include "engine/game/quadrangleComponent.h"
#include "systems/sceneChangeSystem.h"
#include "engine/game/animationComponent.h"
#include "engine/game/game.h"

using namespace vg;

PappaScene::PappaScene()
{
}

PappaScene::~PappaScene()
{
}

void PappaScene::loadObjects()
{

	GameObject *animationTest = new GameObject("animationTest");
	QuadrangleComponent *animationComponent = new QuadrangleComponent("papparunSmall2.png");
	animationTest->addComponent(animationComponent);

	TransformComponent *animationTransform = new TransformComponent(Vector2<float>(128, 128), Vector2<float>(512, 512), 0.0f);
	animationTest->addComponent(animationTransform);
	animationTest->addComponent(new AnimationComponent(0.04, 3, 8, 24));

	addGameObject(animationTest);
	
	// Scene change system
	sceneChangeSystem *sceneChange = new sceneChangeSystem(this);
	Game::getInstance()->addComponentSystem(this, sceneChange);
}