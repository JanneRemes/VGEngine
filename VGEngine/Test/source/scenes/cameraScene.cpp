
#include "scenes/cameraScene.h"
#include "systems/cameraSystem.h"
#include "systems/sceneChangeSystem.h"

#include "engine/game/transformComponent.h"
#include "engine/game/quadrangleComponent.h"
#include "engine/game/animationComponent.h"
#include "engine/game/game.h"
#include "engine/game/textComponent.h"
#include "engine/graphics/screen.h"
#include "engine/utility/color.h"
#include "engine/utility/random.h"

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

	for (int i = 0; i < 20; i++)
	{
		GameObject* obj = new GameObject("test koala");
		obj->addComponent(new TransformComponent(
			Vector2<float>(Random::nexti(0, 1280), Random::nexti(0, 720)), Vector2<float>(128, 128),
			0.0f, Vector2<float>(64, 64)));
		QuadrangleComponent* quad = new QuadrangleComponent("koala.png");
		quad->setColor(Color::random());
		obj->addComponent(quad);
		addGameObject(obj);
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