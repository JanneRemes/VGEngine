
#include <engine/engine.h>
#include <engine/game/game.h>
#include <engine/game/SceneManager.h>
#include <engine/game/transformComponent.h>
#include "TestComponentSystem.h"
#include <stdlib.h> 
#include <engine/utility/logger.h>
#include "TestComponent.h"
#include <engine/game/triangleComponent.h>
#include <engine/game/quadrangleComponent.h>
//DEBUG
//#include <cstdio>
//#include <cstdlib>
using namespace vg;


void test_dummy()
{
	
	main_dummy();
}
void mainGame(Game* game)
{
	Game::log("test");
	Scene *scene = new Scene();
	GameObject *doge = new GameObject("doge");
	TransformComponent *transform = new TransformComponent();
	transform->setRotation(20);
	doge->addComponent(transform);
	TestComponentSystem *compSystem = new TestComponentSystem();
	TestComponent *testcomponent = new TestComponent();
	doge->addComponent(testcomponent);
	//TriangleComponent *triangle = new TriangleComponent();
	//doge->addComponent(triangle);
	//QuadrangleComponent *quadre = new QuadrangleComponent();
	QuadrangleComponent *quadre = game->getFactory()->createRenderComponent<QuadrangleComponent>("koala.png");
	doge->addComponent(quadre);
	//doge.GetComponent<TransformComponent>()->mPosition.setX(rand() % 10);
	scene->getObjectPool()->addGameObject(doge);
	game->addComponentSystem(scene, compSystem);

	game->getSceneManager()->changeScene(scene);
	//game->getSceneManager()->
	//game->mSceneManager->
}