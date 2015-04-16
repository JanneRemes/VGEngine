
#include <engine/engine.h>
#include <engine/game/game.h>
#include <engine/game/SceneManager.h>
#include <engine/game/transformComponent.h>
#include "TestComponentSystem.h"
#include <stdlib.h> 
#include <engine/utility/logger.h>
#include "TestComponent.h"
#include <engine/game/triangleComponent.h>
//DEBUG
//#include <cstdio>
//#include <cstdlib>
using namespace vg;
/*void* operator new(size_t sz){
	Game::log("NEW TEST");
	void* m = malloc(sz);
	return m;
}

void operator delete(void* m) {
	Game::log("REMOVE TEST");
	free(m);
}*/

void test_dummy()
{
	
	main_dummy();
}
void mainGame(Game* game)
{
	Game::log("test");
	Scene *scene = new Scene();
	GameObject doge("doge");
	TransformComponent *transform = new TransformComponent();
	doge.addComponent(transform);
	TestComponentSystem *compSystem = new TestComponentSystem();
	TestComponent *testcomponent = new TestComponent();
	doge.addComponent(testcomponent);
	TriangleComponent *triangle = new TriangleComponent();
	doge.addComponent(triangle);
	//doge.GetComponent<TransformComponent>()->mPosition.setX(rand() % 10);
	scene->getObjectPool()->addGameObject(doge);
	game->addComponentSystem(scene, compSystem);

	game->getSceneManager()->changeScene(scene);
	//game->getSceneManager()->
	//game->mSceneManager->
}