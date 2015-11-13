
#include "systems/mainMenuSystem.h"

#include "engine/game/game.h"
#include "engine/game/transformComponent.h"
#include "engine/game/textComponent.h"
#include "engine/game/quadrangleComponent.h"

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
		QuadrangleComponent* quad = (*it)->getComponent<QuadrangleComponent>();
		if (transform != nullptr && quad != nullptr)
		{
			if ((*it)->getName() == "mmButtonLeft")
			{
				if (transform->contains(inputOnce))
				{
					Log("vgengine", "Main menu left button click", "");
					if (selectedScene != sceneNames.begin())
						selectedScene--;
				}
				else if (transform->contains(input))
					setGreen(quad);
				else
					setBlue(quad);
			}
			else if ((*it)->getName() == "mmButtonRight")
			{
				if (transform->contains(inputOnce))
				{
					Log("vgengine", "Main menu right button click", "");
					if (selectedScene != --sceneNames.end())
						selectedScene++;
				}
				else if (transform->contains(input))
					setGreen(quad);
				else
					setBlue(quad);
			}
			else if ((*it)->getName() == "mmButtonMiddle")
			{
				if (transform->contains(inputOnce))
				{
					Log("vgengine", "Main menu right middle click", "");
					Game::getInstance()->getSceneManager()->changeScene(*selectedScene);
					return;
				}
				else if (transform->contains(input))
					setGreen(quad);
				else
					setBlue(quad);
			}
		}
	}
}

void MainMenuSystem::setGreen(QuadrangleComponent* quad)
{
	quad->setColor(0, 255, 64);
}

void MainMenuSystem::setBlue(QuadrangleComponent* quad)
{
	quad->setColor(0, 64, 255);
}
