#ifdef OS_WINDOWS
#include "engine/input/mouse.h"
#include "engine\input\keyboard.h"
#endif
#ifdef OS_ANDROID
#include "engine/input/touch.h"
#endif

#include "systems/sceneChangeSystem.h"
#include "engine/game/game.h"
#include "engine/utility/random.h"
#include "engine/graphics/screen.h"
#include "engine/game/transformComponent.h"
#include "engine/game/quadrangleComponent.h"
#include "engine/game/textComponent.h"

using namespace vg;
using namespace vg::input;

sceneChangeSystem::sceneChangeSystem(Scene *scene)
{
	this->scene = scene;

	buttonPos = Vector2 <float>(1280 - 256, 32);
	buttonSize = Vector2<float>(128, 32);
	GameObject* button = new GameObject("main menu button");
	button->addComponent(new TransformComponent(buttonPos, buttonSize, 0.0f, Vector2<float>(0, 0), TransformComponent::TOP, false));
	button->addComponent(new TextComponent("arial.ttf", 3u, "Main Menu"));
	scene->addGameObject(button);
}

void sceneChangeSystem::update(std::vector<vg::GameObject*> *gameObjects, float deltaTime)
{
#ifdef OS_WINDOWS

	if (Keyboard::getKeyState(Keyboard::Num1) == Keyboard::KeyState::PRESSED)
	{
		Game::getInstance()->getSceneManager()->changeScene("scene");
	}

	if (Keyboard::getKeyState(Keyboard::Num2) == Keyboard::KeyState::PRESSED)
	{
		Game::getInstance()->getSceneManager()->changeScene("cameraScene");
	}

	if (Keyboard::getKeyState(Keyboard::Num3) == Keyboard::KeyState::PRESSED)
	{
		Game::getInstance()->getSceneManager()->changeScene("pappaScene");
	}

	if (Keyboard::getKeyState(Keyboard::Num4) == Keyboard::KeyState::PRESSED)
	{
		Game::getInstance()->getSceneManager()->changeScene("Android");
	}

	if (Keyboard::getKeyState(Keyboard::Num5) == Keyboard::KeyState::PRESSED)
	{
		Game::getInstance()->getSceneManager()->changeScene("rockThrowScene");
	}

	if (Mouse::isKeyPressed(LEFT))
	{
		if (Mouse::getPos().getX() >= buttonPos.getX() && Mouse::getPos().getY() <= buttonSize.getY())
			Game::getInstance()->getSceneManager()->changeScene("scene");
	}

#endif

#ifdef OS_ANDROID

	if (Touch::getIsTouched())
	{
		if (Touch::getPos().getX() >= buttonPos.getX() && Touch::getPos().getY() <= buttonSize.getY())
			Game::getInstance()->getSceneManager()->changeScene("scene");
	}
#endif
}