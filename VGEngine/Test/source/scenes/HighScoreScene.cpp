#include "Scenes\HighScoreScene.h"
#include <engine/game/gameObject.h>
#include <engine/game/transformComponent.h>
#include <engine/game/textComponent.h>
#include <engine/utility/string.h>
#include <engine/graphics/font.h>
#include "systems/HighScoreSystem.h"
#include <engine/game/renderComponent.h>
#include "systems/sceneChangeSystem.h"
#include "engine/game/game.h"
using namespace vg;
HighScoreScene::HighScoreScene()
{
}


HighScoreScene::~HighScoreScene()
{
}
void HighScoreScene::loadObjects()
{
	sceneChangeSystem *sceneChange = new sceneChangeSystem(this);
	Game::getInstance()->addComponentSystem(this, sceneChange);
	GameObject* titleText = new GameObject("title");
	titleText->addComponent(new TextComponent("arial.ttf", 12, "Highscores:"));
	titleText->addComponent(new TransformComponent(Vec2f(1280 / 2 - 200, 60), Vec2f(0, 0), 0.0f, Vec2f(0, 0), TransformComponent::TOP, false));
	addGameObject(titleText);

	for (int i = 0; i < 10; i++)
	{
		GameObject* someText = new GameObject("score" + toStringi(i));
		TextComponent *nakkimies = new TextComponent("arial.ttf", 12, "Score" + toStringi(i));
		someText->addComponent(nakkimies);

		someText->addComponent(new TransformComponent(Vec2f(1280 / 2 - 200, 115 + (i * nakkimies->getFont()->getFontSize() * 3 + i*5)), Vec2f(0, 0), 0.0f, Vec2f(0, 0), TransformComponent::TOP, false));
		addGameObject(someText);
	}
	getComponentSystemManager()->addSystem(new HighScoreSystem());

	GameObject *nappi = new GameObject("nappi");
	nappi->addComponent(new TransformComponent(Vec2f(0, 720 - 144), Vec2f(350, 175), 0.0f, Vec2f(0, 0), TransformComponent::TOP, false));
	nappi->addComponent(new RenderComponent("dogenappi.png"));
	addGameObject(nappi);

	GameObject* newScoreText = new GameObject("addScore");
	TextComponent *text = new TextComponent("arial.ttf", 12, "Add new Score");
	text->setColor(255, 0, 0, 255);
	newScoreText->addComponent(text);
	newScoreText->addComponent(new TransformComponent(Vec2f(0, 720 - 100), Vec2f(0, 0), 0.0f, Vec2f(0, 0), TransformComponent::TOP, false));
	addGameObject(newScoreText);

	GameObject* actionObject = new GameObject("action");
	TextComponent *textAction = new TextComponent("arial.ttf", 8, "");
	actionObject->addComponent(textAction);
	actionObject->addComponent(new TransformComponent(Vec2f(1280 / 2, 720 - 40), Vec2f(0, 0), 0.0f, Vec2f(0, 0), TransformComponent::TOP, false));
	addGameObject(actionObject);

	GameObject* infoText = new GameObject("Showing top 10 Scores");
	TextComponent *textInfo = new TextComponent("arial.ttf", 12, "Showing top 10 scores, scores saved to Doge.txt");
	infoText->addComponent(textInfo);
	infoText->addComponent(new TransformComponent(Vec2f(0,0), Vec2f(0, 0), 0.0f, Vec2f(0, 0), TransformComponent::TOP, false));
	addGameObject(infoText);
}