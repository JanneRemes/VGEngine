#include "DogeScene.h"
#include <engine/game/gameObject.h>
#include <engine/game/transformComponent.h>
#include <engine/game/quadrangleComponent.h>
using namespace vg;
DogeScene::DogeScene()
{
}


DogeScene::~DogeScene()
{
}
void DogeScene::loadObjects()
{
	GameObject *doge = new GameObject("doge");
	TransformComponent *transform = new TransformComponent(Vector2<int>(64, 64),
		Vector2<int>(128, 128), 0.0f, 0, Vector2<int>(64, 64));
	doge->addComponent(transform);

	QuadrangleComponent *quadre = Game::getInstance()->getFactory()->createRenderComponent<QuadrangleComponent>("shipkoala.png");
	doge->addComponent(quadre);
	addGameObject(doge);
}