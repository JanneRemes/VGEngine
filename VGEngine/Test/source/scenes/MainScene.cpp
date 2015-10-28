#include "MainScene.h"
#include <engine/game/transformComponent.h>
#include <engine/game/triangleComponent.h>
#include <engine/game/quadrangleComponent.h>
#include <engine/game/textComponent.h>
#include "ShipSystem.h"
#include "enemySystem.h"
#include "engine\game\physicsComponent.h"
#include "PhysicsTestSystem.h"
#include <engine/game/animationComponent.h>
#include <engine/game/animationSystem.h>
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
	TransformComponent *transform = new TransformComponent(Vector2<int>(64, 64),
		Vector2<int>(128, 128), 0.0f, 0, Vector2<int>(64, 64));
	ship->addComponent(transform);
	QuadrangleComponent *quadre = new QuadrangleComponent("shipkoala.png");
	ship->addComponent(quadre);
	addGameObject(ship);


	//SHIP

	GameObject *ship2 = new GameObject("ship2");
	TransformComponent *transformship = new TransformComponent(Vector2<int>(64, -64),
		Vector2<int>(128, 128), 0.0f, 1, Vector2<int>(64, 64));
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
	textObj->addComponent(new TransformComponent(Vector2<int>(4, 64),
		Vector2<int>(0, 0), 0.0f, 10000));
	textObj->addComponent(tempText);
	addGameObject(textObj);

	//text
	TextComponent* tempText2 = new TextComponent("arial.ttf", 6u);
	tempText2->setText("Bullets: ");
	tempText2->setColour(0, 0, 127);
	GameObject* textObj2 = new GameObject("bulletText");
	textObj2->addComponent(new TransformComponent(Vector2<int>(4, 128),
		Vector2<int>(0, 0), 0.0f, 10000));
	textObj2->addComponent(tempText2);
	addGameObject(textObj2);

	//FPS text
	TextComponent* fpstextComponent = new TextComponent("arial.ttf", 6u);
	fpstextComponent->setText("FPS: ");
	fpstextComponent->setColour(0, 0, 127);
	GameObject* fpstextObject = new GameObject("fpsText");
	fpstextObject->addComponent(new TransformComponent(Vector2<int>(4, 178),
		Vector2<int>(0, 0), 0.0f, 10000));
	fpstextObject->addComponent(fpstextComponent);
	addGameObject(fpstextObject);

	//enemy
	EnemySystem *enemySystem = new EnemySystem();
	enemySystem->setScene(this);
	Game::getInstance()->addComponentSystem(this, enemySystem);

	PhysicsTestSystem *fysiks = new PhysicsTestSystem(this);
	Game::getInstance()->addComponentSystem(this, fysiks);
	//Animation test

	GameObject *animationTest = new GameObject("animationTest");
	QuadrangleComponent *animationComponent = new QuadrangleComponent("papparunSmall2.png");
	animationTest->addComponent(animationComponent);

	TransformComponent *animationTransform = new TransformComponent(Vector2<int>(128, 128), Vector2<int>(256, 256), 0.0f);
	animationTest->addComponent(animationTransform);

	animationTest->addComponent(new AnimationComponent(0.04, 3, 8, 24));

	AnimationSystem *animationSystem = new AnimationSystem();
	Game::getInstance()->addComponentSystem(this, animationSystem);

	addGameObject(animationTest);

	//sound
	assetManager->load<sound::Sound>("muumitechno.mp3");
	Game::getInstance()->getAudioManager()->addSound("music",
		*assetManager->get<sound::Sound>("muumitechno.mp3"));
	Game::getInstance()->getAudioManager()->play("music");
	Game::getInstance()->getAudioManager()->loopEnabled("music", true);
}