
#include "systems/mainMenuSystem.h"

#include "engine/game/game.h"
#include "engine/game/transformComponent.h"
#include "engine/game/textComponent.h"

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
	sceneNames.push_back("scene");
	sceneNames.push_back("cameraScene");
	sceneNames.push_back("pappaScene");
	sceneNames.push_back("Android");
	sceneNames.push_back("rockThrowScene");
	selectedScene = sceneNames.begin();
}

void MainMenuSystem::update(std::vector<vg::GameObject*> *gameObjects, float deltaTime)
{
	Vector2<float> input(0, 0);
	Vector2<float> inputOnce(0, 0);

	#ifdef OS_WINDOWS
	if (Mouse::isKeyDown(LEFT))
		input = Mouse::getPos();
	if (Mouse::isKeyPressed(LEFT))
		inputOnce = Mouse::getPos();
	#endif
	#ifdef OS_ANDROID
	if (Touch::getIsTouched())
		input = Touch::getPos();
	if (Touch::getIsReleased())
		inputOnce = Touch::getPos();
	#endif

	if (input != Vector2<float>(0, 0))
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

	//list
	for (auto it = gameObjects->begin(); it != gameObjects->end(); it++)
	{
		if ((*it)->getName() == "mmSceneText")
		{
			TextComponent* text = (*it)->getComponent<TextComponent>();
			if (text != nullptr)
				text->setText(*selectedScene);
		}

		TransformComponent* transform = (*it)->getComponent<TransformComponent>();
		if (transform != nullptr)
		{
			if ((*it)->getName() == "mmButtonLeft")
			{
				if (transform->contains(input))
				{
					if (selectedScene != sceneNames.begin())
						selectedScene--;
				}
			}
			else if ((*it)->getName() == "mmButtonRight")
			{
				if (transform->contains(input))
				{
					if (selectedScene != --sceneNames.end())
						selectedScene++;
				}
			}
			else if ((*it)->getName() == "mmButtonMiddle")
			{
			}
		}
	}
}
