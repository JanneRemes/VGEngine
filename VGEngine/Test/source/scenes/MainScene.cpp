
#include "scenes/MainScene.h"
#include "systems/sceneChangeSystem.h"
#include "systems/mainMenuSystem.h"

#include "engine/game/transformComponent.h"
#include "engine/game/quadrangleComponent.h"
#include "engine/game/textComponent.h"
#include "engine/game/game.h"
#include "engine/graphics/screen.h"

using namespace vg;

MainScene::MainScene()
{
}

MainScene::~MainScene()
{
}

void MainScene::loadObjects()
{
	core::AssetManager* assetManager = Game::getInstance()->getAssetManager();
	graphics::Screen::setColor(0.7f, 0.2f, 0.1f, 1.0f);

	// Scene change system
	sceneChangeSystem *sceneChange = new sceneChangeSystem(this);
	Game::getInstance()->addComponentSystem(this, sceneChange);

	Game::getInstance()->addComponentSystem(this, new MainMenuSystem(this));
	
	GameObject* koala = new GameObject("koala button");
	koala->addComponent(new TransformComponent(Vector2<float>(0, 0), Vector2<float>(360, 360), 0.0f));
	koala->addComponent(new QuadrangleComponent("koala.png"));
	addGameObject(koala);

	GameObject* hippo = new GameObject("hippo button");
	hippo->addComponent(new TransformComponent(Vector2<float>(0, 360), Vector2<float>(360, 360), 0.0f));
	hippo->addComponent(new QuadrangleComponent("hippo.png"));
	addGameObject(hippo);

	// sound
	Game::getInstance()->getAudioManager()->addSound("music1",
		*assetManager->get<sound::Sound>("Raise your Kappa!.mp3"));
	Game::getInstance()->getAudioManager()->play("music1");
	Game::getInstance()->getAudioManager()->loopEnabled("music1", true);
}