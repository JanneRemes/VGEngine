
#include "systems/cameraSystem.h"

#include "engine/graphics/camera.h"
#include "engine/graphics/screen.h"

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

}

CameraSystem::~CameraSystem()
{

}

void CameraSystem::update(std::vector<vg::GameObject*> *gameObjects, float deltaTime)
{
	///TODO fix, incompatible with scenechangesystem
	/*
	Vector2<float> input(0,0);
	bool newInput = false;

	#ifdef OS_WINDOWS
	if (Mouse::isKeyPressed(LEFT))
	{
		input = Mouse::getPos();
		newInput = true;
	}
	#endif
	
	#ifdef OS_ANDROID
	if (Touch::getIsTouched())
	{
		input = Touch::getPos();
		newInput = true;
	}
	#endif
	*/
	/*
	if (newInput)
	{
		float x = 10.0f, y = 10.0f;

		if (input.getX() <= Screen::getSize().getX() * 0.5f)
			x *= -1.0f;
		if (input.getY() <= Screen::getSize().getY() * 0.5f)
			y *= -1.0f;

		Camera::move(Vector2<float>(x, y));
	}
	*/
}