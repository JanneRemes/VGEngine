
#include <engine\game\game.h>
#include <engine\game\scene.h>
#include <engine\game\quadrangleComponent.h>
#include <engine\game\physicsSystem.h>
#include <engine\game\physicsComponent.h>

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

	// Physics
	float gravity = 9.81;
	PhysicsSystem *physicsSystem = new PhysicsSystem(Vector2<float>(0, -gravity), true);
	game->addComponentSystem(scene, physicsSystem);

	GameObject *physicsTest = new GameObject("physicsTest1");
	physicsTest->addComponent(new PhysicsComponent(150, 0, 64, 64, b2BodyType::b2_dynamicBody, physicsSystem->getWorld()));

	QuadrangleComponent *physicsObject = game->getFactory()->createRenderComponent<QuadrangleComponent>("hippo.png");
	physicsTest->addComponent(physicsObject);

	TransformComponent *physicsTransform = new TransformComponent(Vector2<int>(64, 64),
		Vector2<int>(64, 64), 0.0f);
	physicsTest->addComponent(physicsTransform);

	scene->getObjectPool()->addGameObject(physicsTest);

	// 2nd physics object
	GameObject *physicsTest2 = new GameObject("physicsTest2");
	physicsTest2->addComponent(new PhysicsComponent(128, 128 * 3, 64, 64, b2BodyType::b2_dynamicBody, physicsSystem->getWorld()));

	QuadrangleComponent *physicsRender2 = game->getFactory()->createRenderComponent<QuadrangleComponent>("hippo.png");
	physicsTest2->addComponent(physicsRender2);

	TransformComponent *physicsTransform2 = new TransformComponent(Vector2<int>(64, 64),
		Vector2<int>(64, 64), 0.0f);
	physicsTest2->addComponent(physicsTransform2);

	scene->getObjectPool()->addGameObject(physicsTest2);
	

	PhysicsTestSystem *physicsTestSystem = new PhysicsTestSystem(scene);
	game->addComponentSystem(scene, physicsTestSystem);
}