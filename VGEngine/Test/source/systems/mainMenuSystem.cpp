
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
	lightDelay = 0.25f;
	lightMaxCount = 20;
	lightSpawnAtOnce = 2;
	currentLightCount = 0;
}

void MainMenuSystem::update(std::vector<vg::GameObject*> *gameObjects, float deltaTime)
{
	inputDown = Vec2f(0, 0);
	inputRelease = Vec2f(0, 0);


	if (lightSpawnTimer.getCurrentTimeSeconds() >= lightDelay && currentLightCount < lightMaxCount)
	{
		//top, left right
		vg::Vec2f spawnareas[][3] = { 
				//top
				{ vg::Vec2f(1060, 300),vg::Vec2f(935,450),vg::Vec2f(1160,450)} ,
				//middle
				{ vg::Vec2f(1060, 400), vg::Vec2f(880, 575), vg::Vec2f(1220, 575)},
				//bottom
				{ vg::Vec2f(1060, 500), vg::Vec2f(850, 700), vg::Vec2f(1230, 700)}
		};
		for (int i = 0; i < lightSpawnAtOnce; i++)
		{
			if (currentLightCount >= lightMaxCount)
				break;
			GameObject *valo = new GameObject("valo");
			int randomIndex = Random::nexti(0, sizeof(spawnareas) / sizeof(spawnareas[0]) -1 );
			vg::Vec2f topCorner = spawnareas[randomIndex][0];
			vg::Vec2f leftCorner = spawnareas[randomIndex][1];
			vg::Vec2f rightrCorner = spawnareas[randomIndex][02];
			vg::Vec2f pos;
			bool isInsideTriangle = false;
			while (!isInsideTriangle)
			{
				pos = Vec2f(leftCorner.x + Random::nexti(0, rightrCorner.x - leftCorner.x), topCorner.y + Random::nexti(0, leftCorner.y - topCorner.y));
				isInsideTriangle = Vec2f::hasTrianglePoint(glm::vec2(pos.x, pos.y), glm::vec2(topCorner.x, topCorner.y), glm::vec2(leftCorner.x, leftCorner.y), glm::vec2(rightrCorner.x, rightrCorner.y));
			}
			TransformComponent *valoTransform = new TransformComponent(pos,
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
