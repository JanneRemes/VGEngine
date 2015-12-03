#include <math.h>
#include <sstream>
#include "systems\androidLaunchSystem.h"
#include "engine\input\mouse.h"
#include "engine\input\touch.h"
#include "engine\game\RenderComponent.h"
#include "engine\game\textComponent.h"
#include "engine\utility\logger.h"
#include "engine/graphics/screen.h"
#include "engine/graphics/camera.h"
#include "engine/utility/string.h"

using namespace vg;
using namespace graphics;

AndroidLaunchSystem::AndroidLaunchSystem(Scene *scene)
{

	this->scene = scene;
	physicSystem = Game::getInstance()->getSceneManager()->getActiveScene()->getComponentSystemManager()->getSystem<PhysicsSystem>();

	core::AssetManager* assetManager = Game::getInstance()->getAssetManager();

	/*
		Android ball initialization
	*/
	GameObject* android = new GameObject("Android");
	TransformComponent* androidTransform = new TransformComponent(Vec2f(0,0),
		Vec2f(32, 32), 0.0f, Vec2f(0, 0));
	android->addComponent(androidTransform);
	RenderComponent* quadre = new RenderComponent("android.png");
	android->addComponent(quadre);
	android->addComponent(new PhysicsComponent(androidTransform, PhysicsComponent::DYNAMIC, 0));

	android->getComponent<PhysicsComponent>()->setFriction(100);
	android->getComponent<PhysicsComponent>()->setRestitution(0.60);
	android->getComponent<PhysicsComponent>()->setDensity(100);
	android->getComponent<PhysicsComponent>()->setAngularDamping(0.3);
	android->getComponent<PhysicsComponent>()->setLinearDamping(0.1);

	scene->addGameObject(android);

	/*
		Background initialization
	*/

	GameObject* background1 = new GameObject("BG1");
	GameObject* background2 = new GameObject("BG2");
	TransformComponent* bgTransform1 = new TransformComponent(Vec2f(0 - Screen::getX() * 0.10, 0), Screen::getSize(), 0, Vec2f(0,0), vg::TransformComponent::LayerGroup::BOTTOM);
	TransformComponent* bgTransform2 = new TransformComponent(Vec2f(Screen::getX() - Screen::getX() * 0.10, 0), Screen::getSize(), 0, Vec2f(0, 0), vg::TransformComponent::LayerGroup::BOTTOM);
	RenderComponent* bgRender1 = new RenderComponent("background.png");
	RenderComponent* bgRender2 = new RenderComponent("background.png");

	background1->addComponent(bgTransform1);
	background1->addComponent(bgRender1);
	background2->addComponent(bgTransform2);
	background2->addComponent(bgRender2);

	scene->addGameObject(background1);
	scene->addGameObject(background2);
	
	/*	
		Power bar initialization
	*/
	GameObject* powerBar = new GameObject("PowerBar");
	TransformComponent *barTransform = new TransformComponent(Vec2f(100, 30),
		Vec2f(32, 126), 0.0f, Vec2f(0, 0));
	powerBar->addComponent(barTransform);
	RenderComponent* powerRender = new RenderComponent("bar.png");
	powerBar->addComponent(powerRender);

	scene->addGameObject(powerBar);

	/*
		Text init
	*/

	GameObject* textObject = new GameObject("Distance");
	TransformComponent* textTransform = new TransformComponent(Vec2f(0, 50), Vec2f(0, 0), 0.0f, Vec2f(0,0), TransformComponent::TOP, false);
	TextComponent* text = new TextComponent("arial.ttf", 12, "Distance");
	text->setColor(255, 0, 0);
	textObject->addComponent(text);
	textObject->addComponent(textTransform);

	scene->addGameObject(textObject);

	/*
		Game status init
	*/

	std::vector<Vec2f> physicBorders;
	physicBorders.push_back(Vec2f(0, Screen::getY()));
	physicBorders.push_back(Vec2f(Screen::getX() * 100, Screen::getY()));

	TransformComponent *borderTransform = new TransformComponent(Vec2f(0, 0),
		Vec2f(200, 64));

	GameObject* physicBorder = new GameObject("borders");
	PhysicsComponent* borderPhysComponent = new PhysicsComponent(borderTransform, physicBorders);
	physicBorder->addComponent(borderPhysComponent);
	physicBorder->addComponent(borderTransform);

	scene->addGameObject(physicBorder);

	borderPhysComponent->setFriction(50);

	bState = INCREASING;
	bgState = BACKGROUND1;
	clickInit = false;
	isShot = false;
	gameObjectInit = false;
	barYIncrement = 0.0f;
	distance = 0;
	defaultPos.x = Screen::getX() * 0.20;
	defaultPos.y = Screen::getY() - 60;
	speed = 100;
	powerBar->getComponent<TransformComponent>()->setPosition(vg::Vec2f(-200, 200));
	android->getComponent<PhysicsComponent>()->setPosition(defaultPos);

	/*	
		Game reset button
	*/
	GameObject* label = new GameObject("reset button");
	label->addComponent(new TransformComponent(Vec2f(Screen::getX() * 0.5 - 50, 0), Vec2f(150, 40), 0.0f, Vec2f(0, 0), TransformComponent::TOP, false));
	RenderComponent* reset = new RenderComponent();
	reset->setColor(vg::Color(150, 150, 150));
	label->addComponent(reset);
	scene->addGameObject(label);
}
AndroidLaunchSystem::~AndroidLaunchSystem()
{

}
void AndroidLaunchSystem::update(std::vector<vg::GameObject*> *gameObjects, float deltaTime)
{
	GameObject* android;
	GameObject* powerBar;
	GameObject* background1;
	GameObject* background2;
	GameObject* textObject;
	GameObject* reset;

	string objectName = "";
	for (auto it = gameObjects->begin(); it < gameObjects->end(); it++)
	{
		objectName = (*it)->getName();
		if (objectName == "PowerBar")
		{
			powerBar = (*it);
		}

		if (objectName == "Android")
		{
			android = (*it);
		}

		if (objectName == "BG1")
		{
			background1 = (*it);
		}
		if (objectName == "BG2")
		{
			background2 = (*it);
		}

		if (objectName == "Distance")
		{
			textObject = (*it);
		}

		if (objectName == "reset button")
		{
			reset = (*it);
		}
	}

	if (isShot == false)
	{	
#ifdef OS_WINDOWS
		if (input::Mouse::isKeyDown(vg::input::RIGHT))
		{
			if (clickInit == false)
			{
				clickPos = vg::input::Mouse::getPos();

#endif

#ifdef OS_ANDROID
		if(input::Touch::getIsTouched())
		{
			if (clickInit == false)
			{ 
				clickPos = input::Touch::getPos();
#endif

				ballPos = android->getComponent<TransformComponent>()->getWorldPosition();
				barTexCoords[0] = glm::vec2(0, 0);
				barTexCoords[1] = glm::vec2(0, 0);
				barTexCoords[2] = glm::vec2(1, 0);
				barTexCoords[3] = glm::vec2(1, 0);
				powerBar->getComponent<RenderComponent>()->setTexCoords(barTexCoords);
			}
			clickInit = true;

			if (bState == BarState::INCREASING)
			{
				barYIncrement += 0.03f;

				if (barYIncrement >= 1.0f)
				{
					bState = DECREASING;
				}
			}

			if (bState == BarState::DECREASING)
			{
				barYIncrement -= 0.03f;

				if (barYIncrement <= 0.0f)
				{
					bState = INCREASING;
				}
			}


			barTexCoords[0] = glm::vec2(0, barYIncrement);
			barTexCoords[1] = glm::vec2(0, 0);
			barTexCoords[2] = glm::vec2(1, 0);
			barTexCoords[3] = glm::vec2(1, barYIncrement);
			powerBar->getComponent<TransformComponent>()->setSize(vg::Vec2f(32, 126 * barYIncrement));
			powerBar->getComponent<TransformComponent>()->setPosition(vg::Vec2f(ballPos.x, ballPos.y - (126 * barYIncrement) - 50));
			powerBar->getComponent<RenderComponent>()->setTexCoords(barTexCoords);
		}

		else if (clickInit == true)
		{
			clickInit = false;
			isShot = true;

			powerBar->getComponent<TransformComponent>()->setPosition(vg::Vec2f(-60, 200));
			vg::Vec2f tempVec = clickPos - android->getComponent<TransformComponent>()->getWorldPosition();
			normalizedVec = normalize(tempVec);

			vg::Vec2f velocity = vg::Vec2f(normalizedVec.x * barYIncrement * speed, normalizedVec.y * barYIncrement * speed);

			if (velocity.x < 0)
				velocity.x = 0;
			android->getComponent<PhysicsComponent>()->setVelocity(vg::Vec2f(velocity.x, -velocity.y));

			
		}
	}

	distance += (android->getComponent<PhysicsComponent>()->getVelocity().x * 0.0025f);
	std::stringstream stream;
	stream << "Distance: " << toStringf(static_cast<float>(distance), 1, 1) << "m";
	textObject->getComponent<TextComponent>()->setText(stream.str());

	backgroundUpdate(gameObjects);

#ifdef OS_WINDOWS

	if (input::Mouse::isKeyPressed(vg::input::LEFT))
	{
		clickPos = input::Mouse::getPos(false);

#endif

#ifdef OS_ANDROID
		if(input::Touch::getIsReleased())
		{ 
			clickPos = input::Touch::getPos(false);
#endif
		if (reset->getComponent<TransformComponent>()->contains(clickPos))
		{
			android->getComponent<PhysicsComponent>()->setPosition(defaultPos);
			android->getComponent<PhysicsComponent>()->setVelocity(vg::Vec2f(0.0f, 0.0f));
			android->getComponent<PhysicsComponent>()->setRotation(0.0f);
			android->getComponent<PhysicsComponent>()->setAngularVelocity(0.0f);
			isShot = false;

			background1->getComponent<TransformComponent>()->setPosition(Vec2f(0 - (Screen::getX() * 0.10), 0));
			background2->getComponent<TransformComponent>()->setPosition(Vec2f(Screen::getX() - Screen::getX() * 0.10, 0));

			bgState = Background::RESET;

			android->getComponent<PhysicsComponent>()->wake(true);

			distance = 0;
		}
	}
}

vg::Vec2f AndroidLaunchSystem::normalize(vg::Vec2f vec2)
{
	float magnitude = sqrt((vec2.x * vec2.x) + (vec2.y * vec2.y));

	vg::Vec2f normalizedVec;

	normalizedVec.x = vec2.x / magnitude;
	normalizedVec.y = vec2.y / magnitude;

	return normalizedVec;
}

void AndroidLaunchSystem::backgroundUpdate(std::vector<vg::GameObject*> *gameObjects)
{	
	GameObject* android;
	GameObject* background1;
	GameObject* background2;
	string objectName;

	TransformComponent* currentBackground;

	for (auto it = gameObjects->begin(); it < gameObjects->end(); it++)
	{
		objectName = (*it)->getName();

		if (objectName == "BG1")
		{
			background1 = (*it);
		}

		if (objectName == "BG2")
		{
			background2 = (*it);
		}

		if (objectName == "Android")
		{
			android = (*it);
		}
	}


	Camera::setPosition(Vec2f(android->getComponent<TransformComponent>()->getWorldPosition().x - Screen::getX() * 0.10, 0));
	
	
	switch (bgState)
	{
	case Background::BACKGROUND1:
		
		currentBackground = background1->getComponent<TransformComponent>();

		if (android->getComponent<TransformComponent>()->getWorldPosition().x >= currentBackground->getWorldPosition().x + Screen::getX() + Screen::getX() * 0.10)
		{
			currentBackground->setPosition(Vec2f(currentBackground->getWorldPosition().x + (2 * Screen::getX()), 0));
			bgState = Background::BACKGROUND2;
		}
		break;

	case Background::BACKGROUND2:

		currentBackground = background2->getComponent<TransformComponent>();

		if (android->getComponent<TransformComponent>()->getWorldPosition().x >= currentBackground->getWorldPosition().x + Screen::getX() + Screen::getX() * 0.10)
		{
			currentBackground->setPosition(Vec2f(currentBackground->getWorldPosition().x + (2 * Screen::getX()), 0));
			bgState = Background::BACKGROUND1;
		}
		break;

	case Background::RESET:

		bgState = BACKGROUND1;
		break;
	}
}