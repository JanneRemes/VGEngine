#include <math.h>
#include <sstream>
#include "systems\androidLaunchSystem.h"
#include "engine\input\mouse.h"
#include "engine\game\quadrangleComponent.h"
#include "engine\game\textComponent.h"
#include "engine\utility\logger.h"
#include "engine/graphics/screen.h"
#include "engine/graphics/camera.h"

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
	android = new GameObject("Android");
	TransformComponent *androidTransform = new TransformComponent(Vec2f(0,0),
		Vec2f(32, 32), 0.0f, Vec2f(0, 0));
	android->addComponent(androidTransform);
	QuadrangleComponent *quadre = new QuadrangleComponent("android.png");
	android->addComponent(quadre);
	android->addComponent(new PhysicsComponent(androidTransform, PhysicsComponent::DYNAMIC, 0));

	android->getComponent<PhysicsComponent>()->setFriction(300);
	android->getComponent<PhysicsComponent>()->setRestitution(0.60);
	android->getComponent<PhysicsComponent>()->setDensity(100);
	scene->addGameObject(android);

	/*
		Background initialization
	*/

	background1 = new GameObject("BG1");
	background2 = new GameObject("BG2");
	TransformComponent *bgTransform1 = new TransformComponent(Vec2f(0 - Screen::getX() * 0.10, 0), Screen::getSize(), 0, Vec2f(0,0), vg::TransformComponent::LayerGroup::BOTTOM);
	TransformComponent *bgTransform2 = new TransformComponent(Vec2f(Screen::getX() - Screen::getX() * 0.10, 0), Screen::getSize(), 0, Vec2f(0, 0), vg::TransformComponent::LayerGroup::BOTTOM);
	QuadrangleComponent *bgRender1 = new QuadrangleComponent("background.png");
	QuadrangleComponent *bgRender2 = new QuadrangleComponent("background.png");

	background1->addComponent(bgTransform1);
	background1->addComponent(bgRender1);
	background2->addComponent(bgTransform2);
	background2->addComponent(bgRender2);

	scene->addGameObject(background1);
	scene->addGameObject(background2);
	
	/*	
		Power bar initialization
	*/
	powerBar = new GameObject("PowerBar");
	TransformComponent *barTransform = new TransformComponent(Vec2f(100, 30),
		Vec2f(32, 126), 0.0f, Vec2f(0, 0));
	powerBar->addComponent(barTransform);
	QuadrangleComponent *powerRender = new QuadrangleComponent("bar.png");
	powerBar->addComponent(powerRender);

	scene->addGameObject(powerBar);

	/*
		Text init
	*/

	textObject = new GameObject("Distance");
	TransformComponent *textTransform = new TransformComponent(Vec2f(20, 20), Vec2f(0, 0), vg::TransformComponent::LayerGroup::HIGH);
	TextComponent* text = new TextComponent("arial.ttf", 16);
	text->setColor(255, 0, 0);
	textObject->addComponent(text);
	textObject->addComponent(textTransform);

	scene->addGameObject(textObject);

	/*
		Game status init
	*/

	physicSystem->createBorders(0, Screen::getY() * 3, Screen::getX() * 100, Screen::getY());

	bState = INCREASING;
	bgState = BACKGROUND1;
	clickInit = false;
	isShot = false;
	barYIncrement = 0.0f;
	distance = 0;
	defaultPos.x = Screen::getX() * 0.10;
	defaultPos.y = Screen::getY() - 60;
	speed = 100;
	powerBar->getComponent<TransformComponent>()->setPosition(vg::Vec2f(-200, 200));
	android->getComponent<PhysicsComponent>()->setPosition(defaultPos);	
}
AndroidLaunchSystem::~AndroidLaunchSystem()
{

}
void AndroidLaunchSystem::update(std::vector<vg::GameObject*> *gameObjects, float deltaTime)
{
#ifdef OS_WINDOWS
	
	if (isShot == false)
	{	
		if (vg::input::Mouse::isKeyDown(vg::input::RIGHT))
		{
			if (clickInit == false)
			{
				clickPos = vg::input::Mouse::getPos();
				ballPos = android->getComponent<TransformComponent>()->getWorldPosition();
				barTexCoords[0] = glm::vec2(0, 0);
				barTexCoords[1] = glm::vec2(0, 0);
				barTexCoords[2] = glm::vec2(1, 0);
				barTexCoords[3] = glm::vec2(1, 0);
				powerBar->getComponent<QuadrangleComponent>()->setTexCoords(barTexCoords);
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
			powerBar->getComponent<QuadrangleComponent>()->setTexCoords(barTexCoords);
		}

		else if (clickInit == true)
		{
			clickInit = false;
			isShot = true;

			powerBar->getComponent<TransformComponent>()->setPosition(vg::Vec2f(-60, 200));
			vg::Vec2f tempVec = vg::input::Mouse::getPos() - android->getComponent<TransformComponent>()->getWorldPosition();
			normalizedVec = normalize(tempVec);

			vg::Vec2f velocity = vg::Vec2f(normalizedVec.x * barYIncrement * speed, normalizedVec.y * barYIncrement * speed);
			android->getComponent<PhysicsComponent>()->setVelocity(vg::Vec2f(velocity.x, -velocity.y));
		}
	}

	else
	{
		if (vg::input::Mouse::isKeyPressed(vg::input::MIDDLE))
		{	
			android->getComponent<PhysicsComponent>()->setPosition(defaultPos);		
			android->getComponent<PhysicsComponent>()->setVelocity(vg::Vec2f(0.0f, 0.0f));
			android->getComponent<PhysicsComponent>()->setRotation(0.0f);
			android->getComponent<PhysicsComponent>()->setAngularVelocity(0.0f);
			isShot = false;

			background1->getComponent<TransformComponent>()->setPosition(Vec2f(0 - (Screen::getX() * 0.10), 0));
			background2->getComponent<TransformComponent>()->setPosition(Vec2f(Screen::getX() - Screen::getX() * 0.10, 0));

			bgState = Background::RESET;

			distance = 0;
		}
	}

	distance += (android->getComponent<PhysicsComponent>()->getVelocity().x / 150.0f);
	std::stringstream stream;
	stream << "Distance: "  << distance << "m";
	textObject->getComponent<TextComponent>()->setText(stream.str());

	backgroundUpdate();

#endif

#ifdef OS_ANROID

	if (vg::input::Touch::getIsTouched())
	{
		vg::Vec2f pos = vg::input::Touch::getPos();

		vg::Vec2f velocity = pos - android->getComponent<TransformComponent>()->getWorldPosition();
		android->getComponent<PhysicsComponent>()->setVelocity(vg::Vec2f(velocity.x, velocity.y));
	}
#endif
}

vg::Vec2f AndroidLaunchSystem::normalize(vg::Vec2f vec2)
{
	float magnitude = sqrt((vec2.x * vec2.x) + (vec2.y * vec2.y));

	vg::Vec2f normalizedVec;

	normalizedVec.x = vec2.x / magnitude;
	normalizedVec.y = vec2.y / magnitude;

	return normalizedVec;
}

void AndroidLaunchSystem::backgroundUpdate()
{	

	Camera::setPosition(Vec2f(android->getComponent<TransformComponent>()->getWorldPosition().x - Screen::getX() * 0.10, 0));
	TransformComponent *currentBackground;
	
	textObject->getComponent<TransformComponent>()->setPosition(Vec2f(Camera::getPosition().x + 20, Camera::getPosition().y + 20));

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