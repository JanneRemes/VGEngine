
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
	sceneNames.push_back("jumpScene");
	selectedScene = sceneNames.begin();
}

void MainMenuSystem::update(std::vector<vg::GameObject*> *gameObjects, float deltaTime)
{
	inputDown = Vec2f(0, 0);
	inputRelease = Vec2f(0, 0);

#ifdef OS_WINDOWS
	if (Mouse::isKeyDown(LEFT))
		inputDown = Mouse::getPos();
	if (Mouse::isKeyPressed(LEFT))
		inputRelease = Mouse::getPos();
#endif
#ifdef OS_ANDROID
	if (Touch::getIsTouched())
		inputDown = Touch::getPos();
	if (Touch::getIsReleased())
		inputRelease = Touch::getPos();
#endif

	for (auto it = gameObjects->begin(); it != gameObjects->end(); it++)
	{
		if ((*it)->getName() == "mmSceneText")
		{
			TextComponent* text = (*it)->getComponent<TextComponent>();
			if (text != nullptr)
				text->setText(*selectedScene);
		}
		else if ((*it)->getName() == "mmButtonUp")
		{
			if (updateButton((*it)))
				if (selectedScene != sceneNames.begin())
					selectedScene--;
		}
		else if ((*it)->getName() == "mmButtonDown")
		{
			if (updateButton((*it)))
				if (selectedScene != --sceneNames.end())
					selectedScene++;
		}
		else if ((*it)->getName() == "mmButtonPlay")
		{
			if (updateButton((*it)))
			{
				Game::getInstance()->getSceneManager()->changeScene(*selectedScene);
				return;
			}
		}
	}
}

bool MainMenuSystem::updateButton(vg::GameObject* obj)
{
	TransformComponent* transform = obj->getComponent<TransformComponent>();
	QuadrangleComponent* render = obj->getComponent<QuadrangleComponent>();
	if (transform != nullptr && render != nullptr)
	{
		if (transform->contains(inputRelease))
			return true;
		else if (transform->contains(inputDown))
			render->setColor(Color(0, 255, 64));
		else
			render->setColor(Color(0, 64, 255));
	}
	return false;
}
