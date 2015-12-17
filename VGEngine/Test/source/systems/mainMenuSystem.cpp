
#include "systems/mainMenuSystem.h"

#include "engine/game/game.h"
#include "engine/game/transformComponent.h"
#include "engine/game/textComponent.h"
#include "engine/game/renderComponent.h"
#include "engine/game/animationComponent.h"
#include "engine/utility/random.h"


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
	sceneNames.push_back("doge");
	sceneNames.push_back("highscorescene");
	selectedScene = sceneNames.begin();
	lightSpawnTimer = Timer();
	lightDelay = 0.12f;
	lightMaxCount = 40;
	lightSpawnAtOnce = 2;
	currentLightCount = 0;
}

void MainMenuSystem::update(std::vector<vg::GameObject*> *gameObjects, float deltaTime)
{
	inputDown = Vec2f(0, 0);
	inputRelease = Vec2f(0, 0);


	if (lightSpawnTimer.getCurrentTimeSeconds() >= lightDelay && currentLightCount < lightMaxCount)
	{
		for (int i = 0; i < lightSpawnAtOnce; i++)
		{
			if (currentLightCount >= lightMaxCount)
				break;
			GameObject *valo = new GameObject("valo");
			TransformComponent *valoTransform = new TransformComponent(Vec2f(920 + Random::nexti(0, 255), 440 + Random::nexti(0, 255)),
				Vec2f(28, 28), 0.0f, Vec2f(-1, -1), vg::TransformComponent::BOTTOM);
			valo->addComponent(valoTransform);
			RenderComponent *quadrvalo = new RenderComponent("valo.png");
			quadrvalo->setColor(vg::Color(rand() % 255, rand() % 255, rand() % 255, 255));
			valo->addComponent(quadrvalo);

			valo->addComponent(new AnimationComponent(0.12, 3, 6, 17));
			mScene->addGameObject(valo);
			currentLightCount++;
		}
		
		lightSpawnTimer.restart();
	}

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
				else
					selectedScene = sceneNames.end() - 1;
		}
		else if ((*it)->getName() == "mmButtonDown")
		{
			if (updateButton((*it)))
				if (selectedScene != --sceneNames.end())
					selectedScene++;
				else
					selectedScene = sceneNames.begin();
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
	RenderComponent* render = obj->getComponent<RenderComponent>();
	if (transform != nullptr && render != nullptr)
	{
		if (transform->contains(inputRelease))
			return true;
		else if (transform->contains(inputDown))
			render->setColor(vg::Color(0, 255, 64));
		else
			render->setColor(vg::Color(255, 0, 0));
	}
	return false;
}
