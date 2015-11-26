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
#include "engine/game/renderComponent.h"
#include "engine/game/textComponent.h"
#include "engine/utility/string.h"
#include "Scenes/DogeScene.h"

using namespace vg;
using namespace vg::input;

sceneChangeSystem::sceneChangeSystem(Scene *scene)
{
	this->scene = scene;

	fpsTime = 0;
	frameCount = 0;
	Vec2f buttonPos(1280 - 210, 0);
	Vec2f buttonSize(256, 50);
	
	GameObject* button = new GameObject("main menu button");
	button->addComponent(new TransformComponent(buttonPos, buttonSize, 0.0f, Vec2f(0, 0), TransformComponent::TOP, false));
	RenderComponent* quad = new RenderComponent();
	quad->setColor(Color(127, 127, 127));
	button->addComponent(quad);
	scene->addGameObject(button);

	GameObject* label = new GameObject("main menu button label");
	label->addComponent(new TransformComponent(Vec2f(4, 8) + buttonPos, Vec2f(0,0), 0.0f, Vec2f(0, 0), TransformComponent::TOP, false));
	TextComponent* text = new TextComponent("arial.ttf", 10u, "Main Menu");
	text->setColor(255, 255, 255);
	label->addComponent(text);
	scene->addGameObject(label);

	GameObject* fps = new GameObject("fps");
	fps->add(new TransformComponent(Vec2f(0, 0), Vec2f(0, 0), 0, Vec2f(0, 0), TransformComponent::TOP, false));
	TextComponent* text2 = new TextComponent("arial.ttf", 6u, "FPS 60.00");
	text2->setColor(255, 255, 255);
	fps->add(text2);
	scene->add(fps);
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

	if (Keyboard::getKeyState(Keyboard::Num6) == Keyboard::KeyState::PRESSED)
	{
		Game::getInstance()->getSceneManager()->changeScene("jumpScene");
	}
	if (Keyboard::getKeyState(Keyboard::Num0) == Keyboard::KeyState::PRESSED)
	{
		Game::getInstance()->getSceneManager()->changeScene("Doges");
	}

#endif

	Vec2f input(0, 0);

#ifdef OS_WINDOWS
	if (Mouse::isKeyDown(LEFT))
		input = Mouse::getPos(false);
#endif
#ifdef OS_ANDROID
	if (Touch::getIsTouched())
		input = Touch::getPos(false);
#endif

	fpsTime += deltaTime;
	frameCount++;

	for (auto it = gameObjects->begin(); it != gameObjects->end(); it++)
	{
		if (fpsTime > 1)
		{
			if ((*it)->getName() == "fps")
			{
				TextComponent* text = (*it)->get<TextComponent>();
				if (text != nullptr)
				{
					text->setText("FPS " + toStringf(static_cast<float>(frameCount) / fpsTime, 2, 5));
					frameCount = 0;
					fpsTime = 0;
				}
			}
		}

		if (input != Vec2f(0, 0))
		{
			if ((*it)->getName() == "main menu button")
			{
				TransformComponent* transform = (*it)->get<TransformComponent>();
				RenderComponent* render = (*it)->get<RenderComponent>();
				if (transform != nullptr && render != nullptr)
				{
					if (transform->contains(input))
					{
						Game::getInstance()->getSceneManager()->changeScene("scene");
						return;
					}
				}
			}
		}
	}
}