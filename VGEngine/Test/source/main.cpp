
#include <engine/engine.h>
#include <engine/game/game.h>
#include <engine/game/SceneManager.h>
#include <engine/game/transformComponent.h>
#include <engine/utility/Vector2.h>
#include <engine/utility/logger.h>
#include <engine/game/triangleComponent.h>
#include <engine/game/quadrangleComponent.h>
#include <engine/game/textComponent.h>
#include <engine/game/textRenderSystem.h>

#include "TestComponent.h"
#include "ShipSystem.h"
#include "enemySystem.h"
#include "TestComponentSystem.h"

#include <stdlib.h> 

using namespace vg;
using namespace vg::graphics;

void mainGame(Game* game)
{
	Game::log("test");
	Scene *scene = new Scene();
	core::AssetManager* assetManager = game->getAssetManager();
	game->getSceneManager()->changeScene(scene);

	//SHIP
	GameObject *ship = new GameObject("ship");
    TransformComponent *transform = new TransformComponent(Vector2<int>(64, 64),
        Vector2<int>(128, 128), 0.0f, 0, Vector2<int>(64,64));
	ship->addComponent(transform);
	TestComponent *testcomponent = new TestComponent();
	ship->addComponent(testcomponent);
	QuadrangleComponent *quadre = game->getFactory()->createRenderComponent<QuadrangleComponent>("shipkoala.png");
	ship->addComponent(quadre);
	scene->getObjectPool()->addGameObject(ship);

	ShipSystem *shipSystem = new ShipSystem(game);
	shipSystem->mScene = scene;
	game->addComponentSystem(scene, shipSystem);

	//text
	TextComponent* tempText = game->getFactory()->create("arial.ttf", 6u);
	tempText->setText("Enemies: ");
	tempText->setColour(127, 0, 0);
	GameObject* textObj = new GameObject("enemyText");
	textObj->addComponent(new TransformComponent(Vector2<int>(4, 64),
		Vector2<int>(0, 0), 0.0f, 10000));
	textObj->addComponent(tempText);
	scene->getObjectPool()->addGameObject(textObj);
	game->addComponentSystem(scene, new TextRenderSystem());
	
	//text
	TextComponent* tempText2 = game->getFactory()->create("arial.ttf", 6u);
	tempText2->setText("Bullets: ");
	tempText2->setColour(0, 0, 127);
	GameObject* textObj2 = new GameObject("bulletText");
	textObj2->addComponent(new TransformComponent(Vector2<int>(4, 128),
		Vector2<int>(0, 0), 0.0f, 10000));
	textObj2->addComponent(tempText2);
	scene->getObjectPool()->addGameObject(textObj2);

	//FPS text
	TextComponent* tempText3= game->getFactory()->create("arial.ttf", 6u);
	tempText3->setText("FPS: ");
	tempText3->setColour(0, 0, 127);
	GameObject* textObj3 = new GameObject("fpsText");
	textObj3->addComponent(new TransformComponent(Vector2<int>(4, 156),
		Vector2<int>(0, 0), 0.0f, 10000));
	textObj3->addComponent(tempText2);
	scene->getObjectPool()->addGameObject(textObj3);
	
	//enemy
	EnemySystem *enemySystem = new EnemySystem(game);
	enemySystem->setScene(scene);
	game->addComponentSystem(scene, enemySystem);

	//sound
	assetManager->load<sound::Sound>("Kalimba.mp3");
    Game::getInstance()->getAudioManager()->addSound("music",
		*assetManager->get<sound::Sound>("Kalimba.mp3"));
    Game::getInstance()->getAudioManager()->play("music");
}