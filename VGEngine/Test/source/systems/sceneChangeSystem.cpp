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

	buttonPos = Vec2f(1280 - 210, 0);
	buttonSize = Vec2f(256, 32);
	
	GameObject* button = new GameObject("main menu button");
	button->addComponent(new TransformComponent(buttonPos, buttonSize, 0.0f, Vec2f(0, 0), TransformComponent::TOP, false));
	QuadrangleComponent* quad = new QuadrangleComponent();
	quad->setColor(Color(127, 127, 127));
	button->addComponent(quad);
	scene->addGameObject(button);

	GameObject* label = new GameObject("main menu button label");
	label->addComponent(new TransformComponent(Vec2f(4,0) + buttonPos, Vec2f(0,0), 0.0f, Vec2f(0, 0), TransformComponent::TOP, false));
	TextComponent* text = new TextComponent("arial.ttf", 10u, "Main Menu");
	text->setColor(255, 255, 255);
	label->addComponent(text);
	scene->addGameObject(label);
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

	if (Mouse::isKeyDown(LEFT))
	{
		if (Mouse::getPos(false).x >= buttonPos.x && Mouse::getPos(false).y <= buttonSize.y)
			Game::getInstance()->getSceneManager()->changeScene("scene");
	}

#endif

#ifdef OS_ANDROID

	if (Touch::getIsTouched())
	{
		if (Touch::getPos(false).x >= buttonPos.x && Touch::getPos(false).y <= buttonSize.y)
			Game::getInstance()->getSceneManager()->changeScene("scene");
	}
#endif
}