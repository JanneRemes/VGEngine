
#include "scenes/MainScene.h"
#include "systems/ShipSystem.h"
#include "systems/enemySystem.h"
#include "systems/PhysicsTestSystem.h"
#include "systems/sceneChangeSystem.h"

#include "engine/game/transformComponent.h"
#include "engine/game/triangleComponent.h"
#include "engine/game/quadrangleComponent.h"
#include "engine/game/textComponent.h"
#include "engine/game/physicsComponent.h"
#include "engine/game/animationComponent.h"
#include "engine/game/animationSystem.h"
#include "engine/game/game.h"

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
	GameObject *ship = new GameObject("ship");
	TransformComponent *transform = new TransformComponent(Vector2<float>(64, 64),
		Vector2<float>(128, 128), 0.0f, 2, Vector2<float>(64, 64));
	ship->addComponent(transform);
	QuadrangleComponent *quadre = new QuadrangleComponent("shipkoala.png");
	ship->addComponent(quadre);
	addGameObject(ship);
	

	//SHIP

	GameObject *ship2 = new GameObject("ship2");
	TransformComponent *transformship = new TransformComponent(Vector2<float>(64, -64),
		Vector2<float>(128, 128), 0.0f, 1, Vector2<float>(64, 64));
	ship2->addComponent(transformship);
	QuadrangleComponent *quadreship = new QuadrangleComponent("shipkoala.png");
	ship2->addComponent(quadreship);
	addGameObject(ship2);
	ship2->setParent(ship);


	ShipSystem *shipSystem = new ShipSystem();
	shipSystem->mScene = this;
	Game::getInstance()->addComponentSystem(this, shipSystem);

	//text
	TextComponent* tempText = new TextComponent("arial.ttf", 6u);
	tempText->setText("Enemies: ");
	tempText->setColour(127, 0, 0);
	GameObject* textObj = new GameObject("enemyText");
	textObj->addComponent(new TransformComponent(Vector2<float>(4, 64),
		Vector2<float>(0, 0), 0.0f, 10000));
	textObj->addComponent(tempText);
	addGameObject(textObj);

	//text
	TextComponent* tempText2 = new TextComponent("arial.ttf", 6u);
	tempText2->setText("Bullets: ");
	tempText2->setColour(0, 0, 127);
	GameObject* textObj2 = new GameObject("bulletText");
	textObj2->addComponent(new TransformComponent(Vector2<float>(4, 128),
		Vector2<float>(0, 0), 0.0f, 10000));
	textObj2->addComponent(tempText2);
	addGameObject(textObj2);

	//FPS text
	TextComponent* fpstextComponent = new TextComponent("arial.ttf", 6u);
	fpstextComponent->setText("FPS: ");
	fpstextComponent->setColour(0, 0, 127);
	GameObject* fpstextObject = new GameObject("fpsText");
	fpstextObject->addComponent(new TransformComponent(Vector2<float>(4, 178),
		Vector2<float>(0, 0), 0.0f, 10000));
	fpstextObject->addComponent(fpstextComponent);
	addGameObject(fpstextObject);

	//enemy
	EnemySystem *enemySystem = new EnemySystem();
	enemySystem->setScene(this);
	Game::getInstance()->addComponentSystem(this, enemySystem);
	
	// Scene change system
	sceneChangeSystem *sceneChange = new sceneChangeSystem(this);
	Game::getInstance()->addComponentSystem(this, sceneChange);
	
	// sound
	assetManager->load<sound::Sound>("Raise your Kappa!.mp3");
	Game::getInstance()->getAudioManager()->addSound("music1",
		*assetManager->get<sound::Sound>("Raise your Kappa!.mp3"));
	Game::getInstance()->getAudioManager()->play("music1");
	Game::getInstance()->getAudioManager()->loopEnabled("music1", true);
}