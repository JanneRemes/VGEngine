
#include <engine/engine.h>
#include <engine/game/game.h>
#include <engine/game/SceneManager.h>
#include <engine/game/transformComponent.h>
#include <engine/utility/Vector2.h>
#include "TestComponentSystem.h"
#include <stdlib.h> 
#include <engine/utility/logger.h>
#include "TestComponent.h"
#include <engine/game/triangleComponent.h>
#include <engine/game/quadrangleComponent.h>
#include "ShipSystem.h"
#include "engine/game/textComponent.h"
#include "engine/game/textRenderSystem.h"
#include "Test\EnemySystem.h"
using namespace vg;
using namespace vg::graphics;

void mainGame(Game* game)
{
	Game::log("test");
	Scene *scene = new Scene();

	//SHIP
	GameObject *ship = new GameObject("ship");
    TransformComponent *transform = new TransformComponent(Vector2<int>(64, 64),
        Vector2<int>(80, 80), 0.0f, 0u);
	ship->addComponent(transform);
	TestComponent *testcomponent = new TestComponent();
	ship->addComponent(testcomponent);
	QuadrangleComponent *quadre = game->getFactory()->createRenderComponent<QuadrangleComponent>("koala2.png");
	ship->addComponent(quadre);

	//text
	{
		TextComponent* tempText = game->getFactory()->create("arial.ttf", 16u);
		tempText->setText("test");
		tempText->setColour(0, 0, 255);
		GameObject* textObj = new GameObject("text1");
		textObj->addComponent(new TransformComponent(Vector2<int>(0, 500),
			Vector2<int>(0, 0), 0.0f, 100));
		textObj->addComponent(tempText);
		scene->getObjectPool()->addGameObject(textObj);
		game->addComponentSystem(scene, new TextRenderSystem());
	}
	{
		TextComponent* tempText2 = game->getFactory()->create("arial.ttf");
		tempText2->setFontSize(12);
		tempText2->setText("asd");
		tempText2->setColour(255, 0, 255);
		GameObject* textObj2 = new GameObject("text2");
		textObj2->addComponent(new TransformComponent(Vector2<int>(0, 525),
			Vector2<int>(0, 0), 0.0f, 0));
		textObj2->addComponent(tempText2);
		scene->getObjectPool()->addGameObject(textObj2);
	}

	game->getSceneManager()->changeScene(scene);
	scene->getObjectPool()->addGameObject(ship);
	ShipSystem *doge = new ShipSystem(game);
	EnemySystem *enemySystem = new EnemySystem(game);
	doge->mScene = scene;
	enemySystem->mScene = scene;
	game->addComponentSystem(scene, doge);
	game->addComponentSystem(scene, enemySystem);

    sound::Sound* testSound = new sound::Sound("Kalimba.mp3");
    testSound->load(game->getInstance()->getFileManager());

    Game::getInstance()->getAudioManager()->addSound("rust", *testSound);
    Game::getInstance()->getAudioManager()->Play("rust");

}