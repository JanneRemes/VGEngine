
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

	// sound
	Game::getInstance()->getAudioManager()->addSound("music1",
		*assetManager->get<sound::Sound>("Raise your Kappa!.mp3"));
	Game::getInstance()->getAudioManager()->play("music1");
	Game::getInstance()->getAudioManager()->loopEnabled("music1", true);

	//buttons
	Vector2<float> bSize(128, 128);
	Vector2<float> bOri(64, 64);
	float bx = 350;
	float by = 400;
	
	//left
	GameObject* objLeft = new GameObject("mmButtonLeft");
	objLeft->addComponent(new TransformComponent(Vector2<float>(bx, by), bSize, 0.0f, bOri));
	QuadrangleComponent* quadLeft = new QuadrangleComponent();
	quadLeft->setColor(0, 64, 255);
	objLeft->addComponent(quadLeft);
	addGameObject(objLeft);

	//right
	GameObject* objRight = new GameObject("mmButtonRight");
	objRight->addComponent(new TransformComponent(Vector2<float>(1280 - bx, by), bSize, 0.0f, bOri));
	QuadrangleComponent* quadRight = new QuadrangleComponent();
	quadRight->setColor(0, 64, 255);
	objRight->addComponent(quadLeft);
	addGameObject(objRight);

	//middle
	GameObject* objMiddle = new GameObject("mmButtonMiddle");
	objMiddle->addComponent(new TransformComponent(Vector2<float>(640, by), Vector2<float>(256, 128), 0.0f, Vector2<float>(128, 64)));
	QuadrangleComponent* quadMiddle = new QuadrangleComponent();
	quadMiddle->setColor(0, 255, 64);
	objMiddle->addComponent(quadMiddle);
	addGameObject(objMiddle);

	//scene name text
	GameObject* objText = new GameObject("mmSceneText");
	objText->addComponent(new TransformComponent(Vector2<float>(bx, by-180), Vector2<float>(0, 0), 0.0f));
	TextComponent* text = new TextComponent("arial.ttf", 18u, "very long scene name");
	text->setColor(255, 255, 255);
	objText->addComponent(text);
	addGameObject(objText);
}