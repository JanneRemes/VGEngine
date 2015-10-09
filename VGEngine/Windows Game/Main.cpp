
#include <engine\game\game.h>
#include <engine\game\scene.h>
#include <engine\game\quadrangleComponent.h>
#include <engine\game\animationComponent.h>
#include <engine\game\animationSystem.h>
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

	/*AnimationSystem *animationSystem = new AnimationSystem();
	game->addComponentSystem(scene, animationSystem);
	GameObject *animationTest = new GameObject("animationTest");
	

	QuadrangleComponent *animationComponent = game->getFactory()->createRenderComponent<QuadrangleComponent>("runningcat.png");
	animationTest->addComponent(animationComponent);

	TransformComponent *animationTransform = new TransformComponent(Vector2<int>(256, 128), Vector2<int>(256, 256), 0.0f);
	animationTest->addComponent(animationTransform);

	animationTest->addComponent(new AnimationComponent(0.20, 4, 2, 8, 256, 256));

	scene->getObjectPool()->addGameObject(animationTest);*/
}