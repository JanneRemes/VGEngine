
#include <engine\game\game.h>
#include <engine\game\scene.h>
#include <engine\game\quadrangleComponent.h>
#include <engine\game\animationComponent.h>
#include <engine\game\animationSystem.h>

#include "PhysicsTestSystem.h"
#include "TestSystem.h"
#include "DogeScene.h"
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
	DogeScene *dogeScene = new DogeScene();
	game->getSceneManager()->addTemplateScene("doge", dogeScene);
	game->getSceneManager()->addTemplateScene("scene", scene);
	game->getSceneManager()->changeScene("scene");
	GameObject *doge = new GameObject("doge");

	TransformComponent *transform = new TransformComponent(Vector2<int>(64, 64),
		Vector2<int>(128, 128), 0.0f, layer++, Vector2<int>(64, 64));
	doge->addComponent(transform);

	QuadrangleComponent *quadre = game->getFactory()->createRenderComfile:///C:/Users/KariTir/Desktop/VGEngineponent<QuadrangleComponent>("shipkoala.png");
	doge->addComponent(quadre);
	scene->addGameObject(doge);
	TestSystem *testSystem = new TestSystem(scene);
	game->addComponentSystem(scene, testSystem);
	
	//Animation
	
	GameObject *animationTest = new GameObject("animationTest");

	QuadrangleComponent *animationComponent = game->getFactory()->createRefile:///C:/Users/KariTir/Desktop/VGEnginenderComponent<QuadrangleComponent>("runningcat.png");
	animationTest->addComponent(animationComponent);

	TransformComponent *animationTransform = new TransformComponent(Vector2<int>(512, 512), Vector2<int>(256, 128), 0.0f);
	animationTest->addComponent(animationTransform);

	animationTest->addComponent(new AnimationComponent(0.03, 4, 2, 8, 256, 128));

	AnimationSystem *animationSystem = new AnimationSystem();
	game->addComponentSystem(scene, animationSystem);

	scene->addGameObject(animationTest);
	PhysicsTestSystem *physicsTestSystem = new PhysicsTestSystem(scene);
	Game::getInstance()->addComponentSystem(scene, physicsTestSystem);

	game->getSceneManager()->changeScene("doge");
}