
#include "systems/cameraSystem.h"

#include "engine\game\physicsComponent.h"
#include "engine/graphics/camera.h"
#include "engine/graphics/screen.h"
#include "engine/game/transformComponent.h"
#include "engine/utility/random.h"

#ifdef OS_WINDOWS
#include "engine/input/mouse.h"
#endif
#ifdef OS_ANDROID
#include "engine/input/touch.h"
#endif

using namespace vg;
using namespace vg::graphics;
using namespace vg::input;

CameraSystem::CameraSystem()
{
	cameraSpeed = 1.5f;
	timer.restart();
}

CameraSystem::~CameraSystem()
{

}

void CameraSystem::update(std::vector<vg::GameObject*> *gameObjects, float deltaTime)
{
	Vec2f input(0,0);

	#ifdef OS_WINDOWS
	if (Mouse::isKeyDown(LEFT))
		input = Mouse::fromCenter();
	#endif
	
	#ifdef OS_ANDROID
	if (Touch::getIsTouched())
		input = Touch::fromCenter();
	#endif

	if (input != Vec2f(0, 0))
	{
		input *= deltaTime * cameraSpeed;
		Camera::move(input);
	}
	/*
	for (auto it = gameObjects->begin(); it != gameObjects->end(); it++)
		if ((*it)->getName() == "origin test")
			(*it)->get<TransformComponent>()->rotate(2);
			*/

	if (timer.getCurrentTimeSeconds() > 3)
	{
		for (auto it = gameObjects->begin(); it != gameObjects->end(); it++)
		{
			if ((*it)->getName().find("test koala") != -1)
			{
				PhysicsComponent* phys = (*it)->get<PhysicsComponent>();
				if (phys != nullptr)
					phys->setVelocity(Vec2f(Random::nexti(-50, 50), Random::nexti(0, 50)));
			}
		}
		timer.restart();
	}
}
