
#include "scenes/cameraScene.h"
#include "systems/cameraSystem.h"

#include "engine/game/transformComponent.h"
#include "engine/game/quadrangleComponent.h"
#include "systems/sceneChangeSystem.h"
#include "engine/game/animationComponent.h"
#include "engine/game/game.h"
#include "engine/game/textComponent.h"
#include "engine/graphics/screen.h"

using namespace vg;

CameraScene::CameraScene()
{
}

CameraScene::~CameraScene()
{
}

void CameraScene::loadObjects()
{
	graphics::Screen::setColor(1.0f, 1.0f, 1.0f, 1.0f);

	for (int i = 0; i < 10; i++)
	{
		GameObject *obj1 = new GameObject("test koala");
		obj1->addComponent(new TransformComponent(
			Vector2<float>(100 + i * 64, 32 + i * 64), Vector2<float>(128, 128),
			0.0f, Vector2<float>(64, 64)));
		obj1->addComponent(new QuadrangleComponent("koala.png"));
		addGameObject(obj1);

		GameObject *obj2 = new GameObject("test koala 2");
		obj2->addComponent(new TransformComponent(
			Vector2<float>(300 + i * 64, i * 64), Vector2<float>(128, 128),
			0.0f, Vector2<float>(64, 64)));
		obj2->addComponent(new QuadrangleComponent("koala.png"));
		addGameObject(obj2);
	}

	CameraSystem* camSys = new CameraSystem();
	Game::getInstance()->addComponentSystem(this, camSys);

	// Scene change system
	sceneChangeSystem *sceneChange = new sceneChangeSystem(this);
	Game::getInstance()->addComponentSystem(this, sceneChange);

	//text
	{
		TextComponent* text = new TextComponent("arial.ttf", 12u);
		text->setText("KoalaKoala");
		text->setColour(127, 256, 256);
		GameObject* obj = new GameObject("koalatext");
		obj->addComponent(new TransformComponent(Vector2<float>(0, 560),
			Vector2<float>(0, 0), 0.0f));
		obj->addComponent(text);
		addGameObject(obj);
	}
	{
		TextComponent* text = new TextComponent("arial.ttf", 12u);
		text->setText("KoalaKoala");
		text->setColour(256, 127, 256);
		GameObject* obj = new GameObject("koalatext");
		obj->addComponent(new TransformComponent(Vector2<float>(30, 590),
			Vector2<float>(0, 0), 0.0f));
		obj->addComponent(text);
		addGameObject(obj);
	}
}