
#include "scenes/cameraScene.h"
#include "systems/cameraSystem.h"
#include "systems/sceneChangeSystem.h"

#include "engine/game/transformComponent.h"
#include "engine/game/quadrangleComponent.h"
#include "engine/game/animationComponent.h"
#include "engine/game/game.h"
#include "engine/game/textComponent.h"
#include "engine/graphics/screen.h"
#include "engine/utility/random.h"
#include "engine/game/physicsSystem.h"
#include "engine/game/physicsPolygonComponent.h"
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
	physics->createBorders(0, 0, Screen::getX(), Screen::getY());
	
	//borders
	createBorder(0, 0, 1280, 32);
	createBorder(0, 720 - 32, 1280, 32);
	createBorder(0, 32, 32, 720 - 64);
	createBorder(1280 - 32, 32, 32, 720 - 64);

	//koala
	for (int i = 0; i < 30; i++)
	{
		GameObject* obj = new GameObject("test koala " + toString(i, 2));
		TransformComponent* transform = new TransformComponent(
			Vector2<float>(Random::nexti(500, 1000), Random::nexti(100, 300)), Vector2<float>(64, 64),
			0.0f, Vector2<float>(32, 32));
		QuadrangleComponent* quad = new QuadrangleComponent("koala.png");
		quad->setColor(Color::random());

		obj->add(transform);
		obj->add(new PhysicsPolygonComponent(transform, PhysicsComponent::DYNAMIC));
		obj->add(quad);
		addGameObject(obj);
	}

	//text
	for (int i = 0; i < 5; i++)
	{
		TextComponent* text = new TextComponent("arial.ttf", 52u);
		text->setText("Koala");
		text->setColor(i * 32, i * 32, i * 32);
		GameObject* obj = new GameObject("koalatext");
		obj->add(new TransformComponent(Vector2<float>(300 + 6 * i, 50 + 6 * i),
			Vector2<float>(0, 0), 0.0f));
		obj->add(text);
		addGameObject(obj);
	}
}

void CameraScene::createBorder(float x, float y, float w, float h)
{
	GameObject* obj = new GameObject("border");
	obj->add(new TransformComponent(Vector2<float>(x, y), Vector2<float>(w, h)));
	QuadrangleComponent* quad = new QuadrangleComponent();
	quad->setColor(vg::Color(255, 0, 0));
	obj->add(quad);
	addGameObject(obj);
}
