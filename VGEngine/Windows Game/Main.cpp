
#include <engine\game\game.h>
#include <engine\game\scene.h>
#include <engine\game\quadrangleComponent.h>

#include "PhysicsTestSystem.h"
#include "TestSystem.h"
//extern void main_dummy();
using namespace vg;
using namespace vg::graphics;
int layer = 0;
void test_dummy()
{

	//main_dummy();
}
void mainGame(Game* game)
{
	Scene *scene = new Scene();
	game->getSceneManager()->changeScene(scene);
	GameObject *doge = new GameObject("doge");
	TransformComponent *transform = new TransformComponent(Vector2<int>(64, 64),
		Vector2<int>(128, 128), 0.0f, layer++, Vector2<int>(64, 64));
	doge->addComponent(transform);

	QuadrangleComponent *quadre = game->getFactory()->createRenderComponent<QuadrangleComponent>("shipkoala.png");
	doge->addComponent(quadre);
	scene->getObjectPool()->addGameObject(doge);
	TestSystem *testSystem = new TestSystem(scene);
	game->addComponentSystem(scene, testSystem);
	
	PhysicsTestSystem *physicsTestSystem = new PhysicsTestSystem(scene);
	Game::getInstance()->addComponentSystem(scene, physicsTestSystem);
}