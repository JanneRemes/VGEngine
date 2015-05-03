#include <engine/engine.h>
#include <engine/game/game.h>
#include <engine/game/SceneManager.h>
#include <engine/game/transformComponent.h>
#include <engine/utility/Vector2.h>
#include "TestComponentSystem.h"
#include <stdlib.h> 
#include <engine/utility/logger.h>
#include "TestComponent.h"
#include <engine/game/triangleComponent.h>
#include <engine/game/quadrangleComponent.h>
#include "ShipSystem.h"

using namespace vg;
using namespace vg::graphics;

void mainGame(Game* game)
{
	Game::log("test");
	Scene *scene = new Scene();

	//SHIP
	GameObject *ship = new GameObject("ship");
    TransformComponent *transform = new TransformComponent(Vector2<int>(64, 64),
        Vector2<int>(80, 80), 0.0f, 0u);
	ship->addComponent(transform);
	TestComponent *testcomponent = new TestComponent();
	ship->addComponent(testcomponent);
	QuadrangleComponent *quadre = game->getFactory()->createRenderComponent<QuadrangleComponent>("koala2.png");
	ship->addComponent(quadre);
	 
	game->getSceneManager()->changeScene(scene);
	scene->getObjectPool()->addGameObject(ship);
	ShipSystem *doge = new ShipSystem();
	game->addComponentSystem(scene, doge);
	//TestComponentSystem *compSystem = new TestComponentSystem();
	//game->addComponentSystem(scene, compSystem);

	game->getGraphics()->append(new DebugSprite("koala.png",
		Vector2<int>(200, 200), Vector2<int>(256, 256), 90.0f, 0));
}