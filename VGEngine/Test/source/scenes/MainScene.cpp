
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
	graphics::Screen::setColor(Color(180, 50, 25));

	Game::getInstance()->addComponentSystem(this, new MainMenuSystem(this));

	// sound
	Game::getInstance()->getAudioManager()->addSound("music1",
		*assetManager->get<sound::Sound>("Raise your Kappa!.mp3"));
	Game::getInstance()->getAudioManager()->play("music1");
	Game::getInstance()->getAudioManager()->loopEnabled("music1", true);

	//buttons
	float middle = 360;
	addGameObject(makeButton("mmButtonUp", "ArrowUp.png", middle - 150));
	addGameObject(makeButton("mmButtonDown", "ArrowDown.png", middle + 150));
	addGameObject(makeButton("mmButtonPlay", "ButtonPlay.png", middle));

	//scene name text
	GameObject* objText = new GameObject("mmSceneText");
	objText->addComponent(new TransformComponent(Vector2<float>(250, middle - 35), Vector2<float>(0, 0), 0.0f));
	TextComponent* text = new TextComponent("arial.ttf", 18u, "very long scene name");
	text->setColor(255, 255, 255);
	objText->addComponent(text);
	addGameObject(objText);
}

vg::GameObject* MainScene::makeButton(std::string name, std::string texture, float y)
{
	GameObject* obj = new GameObject(name);
	obj->addComponent(new TransformComponent(Vector2<float>(150, y), Vector2<float>(128, 128), 0.0f, Vector2<float>(64, 64)));
	QuadrangleComponent* quad = new QuadrangleComponent(texture);
	quad->setColor(Color(0, 64, 255));
	obj->addComponent(quad);
	return obj;
}
