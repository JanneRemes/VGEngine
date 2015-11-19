
#include "scenes/pappaScene.h"

#include "engine/game/transformComponent.h"
#include "engine/game/quadrangleComponent.h"
#include "systems/sceneChangeSystem.h"
#include "engine/game/animationComponent.h"
#include "engine/game/textComponent.h"
#include "engine/game/game.h"
#include "engine\graphics\screen.h"

#include "systems\PhysicsTestSystem.h"

using namespace vg;

PappaScene::PappaScene()
{
}

PappaScene::~PappaScene()
{
}

void PappaScene::loadObjects()
{
	core::AssetManager* assetManager = Game::getInstance()->getAssetManager();

	// Background
	GameObject *background = new GameObject("background");
	TransformComponent *backgroundTransform = new TransformComponent(Vec2f(0, 0),
		Vec2f(1280, 720), 0.0f);
	background->addComponent(backgroundTransform);
	QuadrangleComponent *quadrBackground = new QuadrangleComponent("muumiBG.png");
	background->addComponent(quadrBackground);
	addGameObject(background);

	// 2nd physics object
	TransformComponent *physicsTransform2 = new TransformComponent(Vec2f(500, 500),
		Vec2f(500, 200), 45);

	GameObject *physicsTest2 = new GameObject("physicsTest2");
	QuadrangleComponent *physicsRender2 = new QuadrangleComponent("koala.png");

	PhysicsComponent *physicsPolyComponent2 = new PhysicsComponent(physicsTransform2, PhysicsComponent::STATIC);

	physicsTest2->addComponent(physicsPolyComponent2);
	physicsTest2->addComponent(physicsTransform2);
	physicsTest2->addComponent(physicsRender2);

	physicsTest2->getComponent<PhysicsComponent>()->setDensity(100);
	physicsTest2->getComponent<PhysicsComponent>()->setFriction(100);

	addGameObject(physicsTest2);


	// custom physics shape!

	std::vector<Vec2f> listOfCustomPoints;
	listOfCustomPoints.push_back(Vec2f(0,0));
	listOfCustomPoints.push_back(Vec2f(0, graphics::Screen::getY()));
	listOfCustomPoints.push_back(Vec2f(1280, 720));
	listOfCustomPoints.push_back(Vec2f(graphics::Screen::getX(), 0));


	TransformComponent *customTransform = new TransformComponent(Vec2f(600, 600),
		Vec2f(200, 64));

	GameObject *customPhysicsTest = new GameObject("customPhysicsTest");

	PhysicsComponent *customPhysics = new PhysicsComponent(customTransform, listOfCustomPoints);

	customPhysicsTest->addComponent(customPhysics);
	customPhysicsTest->addComponent(customTransform);
	addGameObject(customPhysicsTest);


	// Physics test system
	PhysicsTestSystem *fysiks = new PhysicsTestSystem(this);
	Game::getInstance()->addComponentSystem(this, fysiks);
	
	// sound
	Game::getInstance()->getAudioManager()->addSound("music",
		*assetManager->get<sound::Sound>("muumitechno.mp3"));
	Game::getInstance()->getAudioManager()->play("music");
	Game::getInstance()->getAudioManager()->loopEnabled("music", true);

	// Scene change system
	sceneChangeSystem *sceneChange = new sceneChangeSystem(this);
	Game::getInstance()->addComponentSystem(this, sceneChange);
}