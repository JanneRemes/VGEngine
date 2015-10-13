#include "TestSystem.h"
#include "engine/input/mouse.h"
#include <engine\game\quadrangleComponent.h>
#include <engine\game\game.h>
#include <engine/graphics/graphics.h>
#include <engine/graphics/camera.h>

using namespace vg;
using namespace vg::graphics;
int layerShip = 0;

TestSystem::TestSystem(Scene *scene)
{
	this->scene = scene;
	dogeDir = Vector2<int>(3, 0);
	camDir = 1;
	camRotDir = 0.05f;
	camZoom = 0.001f;
	camState = 0;
}

void TestSystem::update(std::vector<vg::GameObject*> *gameObjects, float deltaTime)
{
	//camera
	//Camera::zoom(camZoom);
	//Camera::move(Vector2<int>(camDir, -camDir));
	//Camera::rotate(camRotDir);
	
	if (Camera::getZoom() < 0.95f || Camera::getZoom() > 1.05f)
		camZoom *= -1.0f;
	if (abs(Camera::getRotation()) > 20.0f)
		camRotDir *= -1.0f;
	
	camState++;
	if (camState > 30)
	{
		camState = 0;
		camDir *= -1;
	}
		

	if (vg::input::Mouse::isKeyPressed(vg::input::LEFT))
	{
		vg::Vector2<float> pos = vg::input::Mouse::getMousePos();
		GameObject *doge = new GameObject("shipgotreal");
		TransformComponent *transform = new TransformComponent(Vector2<int>(pos.getX(), pos.getY()),
			Vector2<int>(64, 64), 0.0f, layerShip++, Vector2<int>(32, 32));
		doge->addComponent(transform);

		QuadrangleComponent *quadre = Game::getInstance()->getFactory()->createRenderComponent<QuadrangleComponent>("shipkoala.png");
		doge->addComponent(quadre);
		scene->getObjectPool()->addGameObject(doge);
	}
	for (auto it = gameObjects->begin(); it != gameObjects->end(); it++)
	{
		if ((*it)->getName() == "doge")
		{
			if ((*it)->getComponent<TransformComponent>()->getWorldPosition().getX() > Graphics::getResolution().getX())
				dogeDir = Vector2<int>(-3, 0);
			else if (((*it)->getComponent<TransformComponent>()->getWorldPosition().getX() < 0))
				dogeDir = Vector2<int>(3, 0);
			(*it)->getComponent<TransformComponent>()->move(dogeDir);
		}
	}
}