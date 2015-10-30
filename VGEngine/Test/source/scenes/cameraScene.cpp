
#include "scenes/cameraScene.h"
#include "systems/cameraSystem.h"

#include "engine/game/transformComponent.h"
#include "engine/game/quadrangleComponent.h"

using namespace vg;

CameraScene::CameraScene()
{
}

CameraScene::~CameraScene()
{
}

void CameraScene::loadObjects()
{
	for (int i = 0; i < 10; i++)
	{
		GameObject *obj1 = new GameObject("test koala");
		obj1->addComponent(new TransformComponent(
			Vector2<float>(i * 64, i * 64), Vector2<float>(128, 128),
			0.0f, i, Vector2<float>(64, 64)));
		obj1->addComponent(new QuadrangleComponent("koala.png"));
		addGameObject(obj1);

		GameObject *obj2 = new GameObject("test koala 2");
		obj2->addComponent(new TransformComponent(
			Vector2<float>(256 + i * 64, i * 64), Vector2<float>(128, 128),
			0.0f, 1000000 - i, Vector2<float>(64, 64)));
		obj2->addComponent(new QuadrangleComponent("koala.png"));
		addGameObject(obj2);
	}

	CameraSystem* camSys = new CameraSystem();
	Game::getInstance()->addComponentSystem(this, camSys);
}