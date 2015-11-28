
#include "scenes/cameraScene.h"
#include "systems/cameraSystem.h"
#include "systems/sceneChangeSystem.h"

#include "engine/game/transformComponent.h"
#include "engine/game/renderComponent.h"
#include "engine/game/animationComponent.h"
#include "engine/game/game.h"
#include "engine/game/textComponent.h"
#include "engine/graphics/screen.h"
#include "engine/utility/random.h"
#include "engine/game/physicsSystem.h"
#include "engine/utility/string.h"

using namespace vg;
using namespace vg::graphics;

CameraScene::CameraScene()
{
}

CameraScene::~CameraScene()
{
}

void CameraScene::loadObjects()
{
	Screen::setColor(vg::Color(0, 0, 127));

	CameraSystem* camSys = new CameraSystem();
	Game::getInstance()->addComponentSystem(this, camSys);

	sceneChangeSystem *sceneChange = new sceneChangeSystem(this);
	Game::getInstance()->addComponentSystem(this, sceneChange);

	PhysicsSystem* physics = Game::getInstance()->getSceneManager()->getActiveScene()->getComponentSystemManager()->getSystem<PhysicsSystem>();
	physics->createBorders(128, 128, Screen::getX() - 64, Screen::getY() - 64);

	//borders
	createBorder(new TransformComponent(Vec2f(64, 64), Vec2f(1280 - 64, 96), Vec2f(640 - 32, 16)));
	createBorder(new TransformComponent(Vec2f(64, 720 - 96), Vec2f(1280 - 64, 720 - 64), Vec2f(640 - 32, 16)));
	createBorder(new TransformComponent(Vec2f(64, 96), Vec2f(96, 720 - 96), Vec2f(16, 640 - 32)));
	createBorder(new TransformComponent(Vec2f(1280 - 96, 96), Vec2f(1280 - 64, 720 - 96), Vec2f(16, 640 - 32)));

	//koala
	for (int i = 0; i < 30; i++)
	{
		GameObject* obj = new GameObject("test koala " + toStringi(i, 2));
		TransformComponent* transform = new TransformComponent(
			Vec2f(Random::nexti(500, 750), Random::nexti(300, 400)), Vec2f(64, 64),
			0.0f, Vec2f(32, 32));
		RenderComponent* quad = new RenderComponent("koala.png");
		quad->setColor(vg::Color::random());

		obj->add(transform);
		obj->add(new PhysicsComponent(transform, PhysicsComponent::DYNAMIC));
		obj->add(quad);
		addGameObject(obj);
	}
	// origin test
	{
		GameObject* obj = new GameObject("origin test");
		TransformComponent* transform = new TransformComponent(
			Vec2f(640, 360), Vec2f(15, 15), 0.0f, Vec2f(0, 0), TransformComponent::HIGH);
		RenderComponent* quad = new RenderComponent();
		quad->setColor(vg::Color(200, 150, 100));
		obj->add(transform);
		obj->add(quad);
		addGameObject(obj);
	}

	//text
	string str = "aAbBcCdDeEfFgGhHiIjJkKlLmMnNoOpPqQrRsStTuUvVxXyYzZ";
	for (int i = 0; i < 3; i++)
	{
		reverse(str.begin(), str.end());
		int size = 12 + 4 * i;
		TextComponent* text = new TextComponent("arial.ttf", size);
		text->setText(str);
		text->setColor(255 - i * 64, 255 - i * 96, 255 - i * 128);
		GameObject* obj = new GameObject("koalatext");
		obj->add(new TransformComponent(Vec2f(-750, 660 + 2.5f * size * i), TransformComponent::LOW));
		obj->add(text);
		addGameObject(obj);
	}

	//angled rectangle
	{
		GameObject* obj = new GameObject("asdasd");
		obj->add(new TransformComponent(Vec2f(-200, 200), 50, Vec2f(-100, -1500), TransformComponent::TOP));
		RenderComponent* quad = new RenderComponent();
		quad->setColor(vg::Color(128, 255, 128));
		obj->add(quad);
		addGameObject(obj);
	}
}

void CameraScene::createBorder(TransformComponent* transform)
{
	GameObject* obj = new GameObject("border");
	obj->add(transform);
	RenderComponent* quad = new RenderComponent();
	quad->setColor(vg::Color(255, 0, 0));
	obj->add(quad);
	addGameObject(obj);
}
