
#include "systems/cameraSystem.h"

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
	cameraSpeed = 300.0f;
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
				transform->rotate(Random::nexti(-50, 50) * deltaTime);

				float x = Random::nexti(-100, 100) * deltaTime;
				float y = Random::nexti(-100, 100) * deltaTime;
				transform->move(Vector2<float>(x, y));
			}
		}
	}
}