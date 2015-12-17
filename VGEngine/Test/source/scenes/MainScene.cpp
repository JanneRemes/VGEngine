
#include "scenes/MainScene.h"
#include "systems/sceneChangeSystem.h"
#include "systems/mainMenuSystem.h"

#include "engine/game/transformComponent.h"
#include "engine/game/renderComponent.h"
#include "engine/game/textComponent.h"
#include "engine/game/game.h"
#include "engine/graphics/screen.h"
#include "engine/game/physicsComponent.h"
#include "systems/snowSystem.h"
#include "engine/game/animationComponent.h"
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
		*assetManager->get<sound::Sound>("christmasremix.mp3"));
	Game::getInstance()->getAudioManager()->play("music1");
	Game::getInstance()->getAudioManager()->loopEnabled("music1", true);

	//buttons
	float middle = 360;
	addGameObject(makeButton("mmButtonUp", "ArrowUp.png", middle - 150));
	addGameObject(makeButton("mmButtonDown", "ArrowDown.png", middle + 150));
	addGameObject(makeButton("mmButtonPlay", "ButtonPlay.png", middle));

	//scene name text
	GameObject* objText = new GameObject("mmSceneText");
	objText->addComponent(new TransformComponent(Vec2f(250, middle - 35), Vec2f(0, 0), 0.0f));
	TextComponent* text = new TextComponent("arial.ttf", 18u, "very long scene name");
	text->setColor(255, 255, 255);
	objText->addComponent(text);
	addGameObject(objText);

	GameObject *background = new GameObject("background");
	TransformComponent *backgroundTransform = new TransformComponent(Vec2f(0, 0),
		Vec2f(1280, 720), 0.0f, Vec2f(0, 0),vg::TransformComponent::BOTTOM);
	background->addComponent(backgroundTransform);
	RenderComponent *quadrBackground = new RenderComponent("christmasbackground2.png");
	background->addComponent(quadrBackground);
	addGameObject(background);

	//Minion
	GameObject *minion = new GameObject("minion");
	TransformComponent *minionTransform = new TransformComponent(Vec2f(100, 100),
		Vec2f(90, 162), 0.0f, Vec2f(45, 81), vg::TransformComponent::MIDDLE);
	minion->addComponent(minionTransform);
	PhysicsComponent *physicsMinion = new PhysicsComponent(minionTransform, PhysicsComponent::DYNAMIC);
	physicsMinion->setRestitution(1.0f);
	physicsMinion->setVelocity(Vec2f(100.0f, 50.0f));
	physicsMinion->setAngularVelocity(20.0f);
	minion->addComponent(physicsMinion);
	RenderComponent *quadrMinion = new RenderComponent("peruna_minion.png");
	minion->addComponent(quadrMinion);
	addGameObject(minion);

	//Koala
	GameObject *koala = new GameObject("koala");
	TransformComponent *koalaTransform = new TransformComponent(Vec2f(0, 0),
		Vec2f(134, 134), 0.0f, Vec2f(0, 0), vg::TransformComponent::MIDDLE);
	koala->addComponent(koalaTransform);
	PhysicsComponent *physicsKoala = new PhysicsComponent(koalaTransform, PhysicsComponent::DYNAMIC);
	physicsKoala->setRestitution(1.0f);
	physicsKoala->setVelocity(Vec2f(100.0f, 50.0f));
	physicsKoala->setAngularVelocity(20.0f);
	koala->addComponent(physicsKoala);
	RenderComponent *quadrKoala = new RenderComponent("koala.png");
	koala->addComponent(quadrKoala);
	addGameObject(koala);

	//mursu
	GameObject *mursu = new GameObject("mursu");
	TransformComponent *mursuTransform = new TransformComponent(Vec2f(0, 0),
		Vec2f(134, 134), 0.0f, Vec2f(0, 0), vg::TransformComponent::MIDDLE);
	mursu->addComponent(mursuTransform);
	PhysicsComponent *physicsMursu = new PhysicsComponent(mursuTransform, PhysicsComponent::DYNAMIC);
	physicsMursu->setRestitution(1.0f);
	physicsMursu->setVelocity(Vec2f(100.0f, 50.0f));
	physicsMursu->setAngularVelocity(20.0f);
	mursu->addComponent(physicsMursu);
	RenderComponent *quadrMursu = new RenderComponent("hippo.png");
	mursu->addComponent(quadrMursu);
	addGameObject(mursu);

	//
	GameObject *doge = new GameObject("doge");
	TransformComponent *dogeTransform = new TransformComponent(Vec2f(150, 150),
		Vec2f(120, 120), 0.0f, Vec2f(60, 60), vg::TransformComponent::MIDDLE);
	doge->addComponent(dogeTransform);
	PhysicsComponent *physicsDoge = new PhysicsComponent(dogeTransform, PhysicsComponent::DYNAMIC,120);
	physicsDoge->setRestitution(1.0f);
	physicsDoge->setAngularVelocity(20.0f);
	physicsDoge->setVelocity(Vec2f(100.0f, 150.0f));
	//physicsMursu->setAngularVelocity(20.0f);
	doge->addComponent(physicsDoge);
	RenderComponent *quadrDoge = new RenderComponent("doge.png");
	doge->addComponent(quadrDoge);
	addGameObject(doge);

	GameObject *muumi = new GameObject("muumi");
	TransformComponent *muumiTransform = new TransformComponent(Vec2f(100, 100),
		Vec2f(75, 134), 0.0f, Vec2f(47, 72), vg::TransformComponent::MIDDLE);
	muumi->addComponent(muumiTransform);
	PhysicsComponent *physicsmuumi = new PhysicsComponent(muumiTransform, PhysicsComponent::DYNAMIC);
	physicsmuumi->setRestitution(1.0f);
	physicsmuumi->setVelocity(Vec2f(100.0f, 50.0f));
	physicsmuumi->setAngularVelocity(20.0f);
	muumi->addComponent(physicsmuumi);
	RenderComponent *quadrmuumi = new RenderComponent("mursupappa.png");
	muumi->addComponent(quadrmuumi);
	addGameObject(muumi);



	GameObject *kuusi = new GameObject("kuusi");
	TransformComponent *kuusiTransform = new TransformComponent(Vec2f(1050, 465),
		Vec2f(416, 512), 0.0f, Vec2f(-1, -1), vg::TransformComponent::BOTTOM);
	kuusi->addComponent(kuusiTransform);
	RenderComponent *quadrkuusi = new RenderComponent("joulukuusi.png");
	kuusi->addComponent(quadrkuusi);
	addGameObject(kuusi);

	//BORDERS
	std::vector<Vec2f> listOfCustomPoints;
	listOfCustomPoints.push_back(Vec2f(0, 0));
	listOfCustomPoints.push_back(Vec2f(0, graphics::Screen::getY()));
	listOfCustomPoints.push_back(Vec2f(1280, 720));
	listOfCustomPoints.push_back(Vec2f(graphics::Screen::getX(), 0));
	listOfCustomPoints.push_back(Vec2f(0, 0));

	TransformComponent *customTransform = new TransformComponent(Vec2f(600, 600),
		Vec2f(200, 64));

	GameObject *customPhysicsTest = new GameObject("customPhysicsTest");

	PhysicsComponent *customPhysics = new PhysicsComponent(customTransform, listOfCustomPoints);

	customPhysicsTest->addComponent(customPhysics);
	customPhysicsTest->addComponent(customTransform);
	addGameObject(customPhysicsTest);
	Game::getInstance()->addComponentSystem(this,new snowSystem(this));
	// END OF BOTDERS

}

vg::GameObject* MainScene::makeButton(std::string name, std::string texture, float y)
{
	GameObject* obj = new GameObject(name);
	obj->addComponent(new TransformComponent(Vec2f(150, y), Vec2f(128, 128), 0.0f, Vec2f(64, 64)));
	RenderComponent* quad = new RenderComponent(texture);
	quad->setColor(Color(255, 0, 0));
	obj->addComponent(quad);
	return obj;
}
