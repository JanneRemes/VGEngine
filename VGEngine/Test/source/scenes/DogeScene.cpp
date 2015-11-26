#include "Scenes/DogeScene.h"
#include <engine/game/transformComponent.h>
#include <engine/game/renderComponent.h>
#include <engine/game/textComponent.h>
#include <engine/game/game.h>
#include "systems/DogeSystem.h"
#include "systems/sceneChangeSystem.h"
using namespace vg;

DogeScene::DogeScene()
{
}


DogeScene::~DogeScene()
{
}
void DogeScene::loadObjects()
{
	GameObject *background = new GameObject("background");
	TransformComponent *backgroundTransform = new TransformComponent(Vec2f(0, 0),
		Vec2f(1280, 720), 0.0f);
	background->addComponent(backgroundTransform);
	RenderComponent *quadrBackground = new RenderComponent("followyourdreams.png");
	background->addComponent(quadrBackground);
	addGameObject(background);

	GameObject *doge = new GameObject("doge");
	TransformComponent *dogetransform = new TransformComponent(Vec2f(1280/2 +50, 720/2 -50),
		Vec2f(320, 320), 0.0f,Vec2f(160.0f));
	doge->addComponent(dogetransform);
	RenderComponent *dogerender = new RenderComponent("doge.png");
	doge->addComponent(dogerender);
	addGameObject(doge);

	GameObject* textObject = new GameObject("DogeText");
	TransformComponent* textTransform = new TransformComponent(Vec2f(1280/2, 20), Vec2f(0, 0), 0.0f, Vec2f(0, 0), TransformComponent::TOP, false);
	TextComponent* text = new TextComponent("arial.ttf", 12, "Doges: 0");
	text->setColor(255, 0, 0);
	textObject->addComponent(text);
	textObject->addComponent(textTransform);

	Game::getInstance()->getSceneManager()->getActiveScene()->addGameObject(textObject);

	Game::getInstance()->addComponentSystem(this, new DogeSystem());

	sceneChangeSystem *sceneChange = new sceneChangeSystem(this);
	Game::getInstance()->addComponentSystem(this, sceneChange);

}