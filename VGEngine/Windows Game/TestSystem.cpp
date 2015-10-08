#include "TestSystem.h"
#include "engine/input/mouse.h"
#include <engine\game\quadrangleComponent.h>
#include <engine\game\game.h>
using namespace vg;
int layerShip = 0;
TestSystem::TestSystem(Scene *scene)
{
	this->scene = scene;
}
void TestSystem::update(std::vector<vg::GameObject*> *gameObjects, float deltaTime)
{
	if (vg::input::Mouse::isKeyPressed(vg::input::LEFT))
	{

		vg::Vector2<float> pos = vg::input::Mouse::getMousePos();
		GameObject *doge = new GameObject("shipgotreal");
		TransformComponent *transform = new TransformComponent(Vector2<int>(pos.getX(), pos.getY()),
			Vector2<int>(128, 128), 0.0f, layerShip++, Vector2<int>(64, 64));
		doge->addComponent(transform);

		QuadrangleComponent *quadre = Game::getInstance()->getFactory()->createRenderComponent<QuadrangleComponent>("shipkoala.png");
		doge->addComponent(quadre);
		scene->getObjectPool()->addGameObject(doge);
	}
	for (auto it = gameObjects->begin(); it != gameObjects->end(); it++)
	{
		if ((*it)->getName() == "doge")
		{
			vg::Vector2<int> pos = (*it)->getComponent<TransformComponent>()->getWorldPosition();
			pos.setX(pos.getX() + 2);
			(*it)->getComponent<TransformComponent>()->setPosition(pos);
		}
	}
}