
#include <engine/engine.h>
#include <engine/game/game.h>
#include <engine/game/SceneManager.h>
#include <engine/game/scriptComponent.h>
#include <engine/game/transformComponent.h>
#include <stdlib.h> 
using namespace vg;
void test_dummy()
{
	
	main_dummy();
}
void mainGame(Game* game)
{
	Scene *scene = new Scene();
	GameObject doge("doge");
	ScriptComponent* testComponent = new ScriptComponent();
	TransformComponent* transform = new TransformComponent();
	doge.addComponent(testComponent);
	doge.addComponent(transform);

	doge.GetComponent<TransformComponent>()->mPosition.setX(rand() % 10);
	scene->mObjectPool.addGameObject(doge);


	game->getSceneManager()->changeScene(scene);
	//game->getSceneManager()->
	//game->mSceneManager->
}