
#include "scenes/cameraScene.h"
#include "systems/cameraSystem.h"

#include "engine/game/transformComponent.h"
#include "engine/game/quadrangleComponent.h"
#include "systems/sceneChangeSystem.h"
#include "engine/game/animationComponent.h"
#include "engine/game/game.h"
#include "engine/game/textComponent.h"
#include "engine/graphics/screen.h"
#include "engine/utility/color.h"

#include <random>

using namespace vg;

CameraScene::CameraScene()
{
}

CameraScene::~CameraScene()
{
}

void CameraScene::loadObjects()
{
	graphics::Screen::setColor(Color(0, 0, 127));

	for (int i = 0; i < 10; i++)
	{
		GameObject *obj1 = new GameObject("test koala");
		obj1->addComponent(new TransformComponent(
			Vector2<float>(100 + i * 64, 32 + i * 64), Vector2<float>(128, 128),
			0.0f, Vector2<float>(64, 64)));
		QuadrangleComponent* quad1 = new QuadrangleComponent("koala.png");
		quad1->setColor(Color::random());
		obj1->addComponent(quad1);
		addGameObject(obj1);

		GameObject *obj2 = new GameObject("test koala");
		obj2->addComponent(new TransformComponent(
			Vector2<float>(300 + i * 64, i * 64), Vector2<float>(128, 128),
			0.0f, Vector2<float>(64, 64)));
		QuadrangleComponent* quad2 = new QuadrangleComponent("koala.png");
		quad2->setColor(Color::random());
		obj2->addComponent(quad2);
		addGameObject(obj2);
	}

	CameraSystem* camSys = new CameraSystem();
	Game::getInstance()->addComponentSystem(this, camSys);

	// Scene change system
	sceneChangeSystem *sceneChange = new sceneChangeSystem(this);
	Game::getInstance()->addComponentSystem(this, sceneChange);

	//text
	for (int i = 0; i < 5; i++)
	{
		TextComponent* text = new TextComponent("arial.ttf", 52u);
		text->setText("Koala");
		text->setColor(i * 32, i * 32, i * 32);
		GameObject* obj = new GameObject("koalatext");
		obj->addComponent(new TransformComponent(Vector2<float>(256 + 6 * i, 256 + 6 * i),
			Vector2<float>(0, 0), 0.0f));
		obj->addComponent(text);
		addGameObject(obj);
	}
}