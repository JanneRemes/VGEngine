
#include "systems/cameraSystem.h"

#include "engine/game/physicsComponent.h"
#include "engine/game/transformComponent.h"
#include "engine/game/textComponent.h"
#include "engine/graphics/camera.h"
#include "engine/graphics/screen.h"
#include "engine/utility/random.h"
#include "engine/utility/string.h"

#ifdef OS_WINDOWS
#include "engine/input/mouse.h"
#include "engine/input/keyboard.h"
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
	if (Keyboard::getKeyState(Keyboard::W) == Keyboard::PRESSED)
		Camera::zoom(-1.0f * deltaTime);
	else if (Keyboard::getKeyState(Keyboard::S) == Keyboard::PRESSED)
		Camera::zoom(1.0f * deltaTime);
	#endif
	
	#ifdef OS_ANDROID
	if (Touch::getIsTouched())
		input = Touch::fromCenter();
	#endif

	if (input != Vec2f(0, 0))
	{
		input *= deltaTime * cameraSpeed;
		Camera::move(input);

		Vec2f pos = Camera::getPosition();
		if (pos.y > 500)
			Camera::setY(500);
		else if (pos.y < -1200)
			Camera::setY(-1200);

		if (pos.x > 1000)
			Camera::setX(1000);
		else if (pos.x < -600)
			Camera::setX(-600);
	}

	for (auto it = gameObjects->begin(); it != gameObjects->end(); it++)
	{
		if ((*it)->getName() == "origin test")
			(*it)->get<TransformComponent>()->rotate(2);
		else if ((*it)->getName() == "spinner")
			(*it)->get<PhysicsComponent>()->setAngularVelocity(20.0f);
		else if ((*it)->getName() == "timer text")
			(*it)->get<TextComponent>()->setText(toStringi(5 - static_cast<int>(timer.getCurrentTimeSeconds())));
	}

	if (timer.getCurrentTimeSeconds() > 5)
	{
		for (auto it = gameObjects->begin(); it != gameObjects->end(); it++)
		{
			if ((*it)->getName().find("test koala") != -1)
			{
				PhysicsComponent* phys = (*it)->get<PhysicsComponent>();
				if (phys != nullptr)
					phys->setVelocity(Vec2f(Random::nexti(-50, 50), Random::nexti(0, 75)));
			}
		}
		timer.restart();
	}
}
