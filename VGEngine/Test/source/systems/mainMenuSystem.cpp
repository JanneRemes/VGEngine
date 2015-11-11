
#include "systems/mainMenuSystem.h"

#include "engine/game/game.h"

#ifdef OS_WINDOWS
#include "engine/input/mouse.h"
#endif
#ifdef OS_ANDROID
#include "engine/input/touch.h"
#endif

using namespace vg;
using namespace vg::input;

MainMenuSystem::MainMenuSystem(Scene* scene)
	:mScene(scene)
{
}

void MainMenuSystem::update(std::vector<vg::GameObject*> *gameObjects, float deltaTime)
{
	Vector2<float> input(-1, -1);
	bool newInput = false;

	#ifdef OS_WINDOWS
	if (Mouse::isKeyDown(LEFT))
	{
		newInput = true;
		input = Mouse::getPos();
	}
	#endif
	#ifdef OS_ANDROID
	if (Touch::getIsTouched())
	{
		newInput = true;
		input = Touch::getPos();
	}
	#endif

	if (newInput)
	{
		if (input.getX() < 360)
		{
			if (0 < input.getY() < 720)
			{
				if (input.getY() < 360)
					Game::getInstance()->getSceneManager()->changeScene("cameraScene");
				else if (input.getY() > 360)
					Game::getInstance()->getSceneManager()->changeScene("pappaScene");
			}
		}
	}
}
