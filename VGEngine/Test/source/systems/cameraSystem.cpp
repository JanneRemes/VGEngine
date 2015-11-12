
#include "systems/cameraSystem.h"

#include "engine/graphics/camera.h"
#include "engine/graphics/screen.h"
#include "engine/game/transformComponent.h"

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
	cameraSpeed = 200.0f;
}

CameraSystem::~CameraSystem()
{

}

void CameraSystem::update(std::vector<vg::GameObject*> *gameObjects, float deltaTime)
{
	Vector2<float> input(0,0);

	#ifdef OS_WINDOWS
	if (Mouse::isKeyDown(LEFT))
		input = Mouse::fromCenter();
	#endif
	
	#ifdef OS_ANDROID
	if (Touch::getIsTouched())
		input = Touch::fromCenter();
	#endif

	if (input != Vector2<float>(0, 0))
	{
		input *= deltaTime * cameraSpeed;
		Camera::move(input);
	}

	for (auto it = gameObjects->begin(); it != gameObjects->end(); it++)
	{
		if ((*it)->getName() == "test koala")
		{
			TransformComponent* transform = (*it)->getComponent<TransformComponent>();
			if (transform != nullptr)
			{
				transform->rotate(deltaTime * (-50 + rand() % 100));

				float x = (-100 + (rand() % 200)) * deltaTime;
				float y = (-100 + (rand() % 200)) * deltaTime;
				transform->move(Vector2<float>(x, y));
			}
		}
	}
}