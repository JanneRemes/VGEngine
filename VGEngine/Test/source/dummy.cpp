
#include <engine/engine.h>
#include <engine/game/game.h>
#include <engine/game/SceneManager.h>
#include <engine/game/transformComponent.h>
#include "TestComponentSystem.h"
#include <stdlib.h> 
#include <engine/utility/logger.h>
using namespace vg;
void test_dummy()
{
	
	main_dummy();
}
void mainGame(Game* game)
{
	game->log("test");
	Scene *scene = new Scene();
	GameObject doge("doge");
	TransformComponent *transform = new TransformComponent();
	doge.addComponent(transform);
	TestComponentSystem *compSystem = new TestComponentSystem();
	//doge.GetComponent<TransformComponent>()->mPosition.setX(rand() % 10);
	scene->getObjectPool()->addGameObject(doge);
	game->addComponentSystem(scene, compSystem);

	game->getSceneManager()->changeScene(scene);
	//game->getSceneManager()->
	//game->mSceneManager->
}