#ifdef OS_WINDOWS
#include "engine/input/mouse.h"
#include "engine\input\keyboard.h"
#endif
#ifdef OS_ANDROID
#include "engine/input/touch.h"
#endif

#include "engine/game/game.h"
#include "engine/utility/random.h"
#include "engine/graphics/screen.h"
#include "systems\sceneChangeSystem.h"

using namespace vg;

sceneChangeSystem::sceneChangeSystem(Scene *scene)
{
	this->scene = scene;
}
void sceneChangeSystem::update(std::vector<vg::GameObject*> *gameObjects, float deltaTime)
{
#ifdef OS_WINDOWS

	if (vg::input::Keyboard::getKeyState(vg::input::Keyboard::Num1) == vg::input::Keyboard::KeyState::PRESSED)
	{
		Game::getInstance()->getSceneManager()->changeScene("scene");
	}

	if (vg::input::Keyboard::getKeyState(vg::input::Keyboard::Num2) == vg::input::Keyboard::KeyState::PRESSED)
	{
		Game::getInstance()->getSceneManager()->changeScene("cameraScene");
	}

	if (vg::input::Keyboard::getKeyState(vg::input::Keyboard::Num3) == vg::input::Keyboard::KeyState::PRESSED)
	{
		Game::getInstance()->getSceneManager()->changeScene("pappaScene");
	}

	if (vg::input::Keyboard::getKeyState(vg::input::Keyboard::Num4) == vg::input::Keyboard::KeyState::PRESSED)
	{
		Game::getInstance()->getSceneManager()->changeScene("Android");
	}

#endif

#ifdef OS_ANDROID

#endif
}