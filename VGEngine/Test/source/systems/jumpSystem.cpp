
#include "systems/jumpSystem.h"

#ifdef OS_WINDOWS
#include "engine/input/mouse.h"
#include "engine\input\keyboard.h"
#endif
#ifdef OS_ANDROID
#include "engine/input/touch.h"
#endif

#include "engine/game/renderComponent.h"
#include "engine/game/game.h"
#include <sstream>

#include "engine/game/animationComponent.h"
#include "engine/game/animationSystem.h"
#include "engine/game/textComponent.h"
#include "engine/utility/random.h"
#include "engine/graphics/screen.h"
#include "engine/utility/timer.h"
#include "engine/graphics/camera.h"

using namespace vg;
using namespace vg::graphics;
using namespace vg::input;

JumpSystem::JumpSystem(Scene *scene)
{
	slomo_state = NO_SLOMO;
	this->scene = scene;
	system = Game::getInstance()->getSceneManager()->getActiveScene()->getComponentSystemManager()->getSystem<PhysicsSystem>();
	
	launchPower = 0;
	jumpDistance = 0;
	jumpPosition = 0;
	launched = false;
	
	// Background
	background = new GameObject("background");
	TransformComponent *backgroundTransform = new TransformComponent(Vec2f(0, 0),
		Vec2f(1280, 720), 0.0f, Vec2f(0, 0), TransformComponent::BOTTOM);

	background->addComponent(backgroundTransform);
	RenderComponent *quadrBackground = new RenderComponent("muumiBG.png");
	background->addComponent(quadrBackground);
	scene->addGameObject(background);

	// Distance text
	textObject = new GameObject("Distance");
	TransformComponent* textTransform = new TransformComponent(Vec2f(0, 100), Vec2f(0, 0), 0.0f, Vec2f(0, 0), TransformComponent::TOP, false);
	TextComponent* text = new TextComponent("arial.ttf", 12);
	text->setColor(0, 255, 100);
	textObject->addComponent(text);
	textObject->addComponent(textTransform);

	scene->addGameObject(textObject);

	// Power text
	powerTextObject = new GameObject("Power");
	TransformComponent* powerTextTransform = new TransformComponent(Vec2f(0, 50), Vec2f(0, 0), 0.0f, Vec2f(0, 0), TransformComponent::TOP, false);
	TextComponent* powerText = new TextComponent("arial.ttf", 12);
	powerText->setColor(0, 255, 100);
	powerTextObject->addComponent(powerText);
	powerTextObject->addComponent(powerTextTransform);

	scene->addGameObject(powerTextObject);

	// Snowboard
	snowboard = new GameObject("physicsTest1");

	TransformComponent *physicsTransform = new TransformComponent(Vec2f(10, -10),
		Vec2f(64, 8), -45.0f);

	RenderComponent *physicsObject = new RenderComponent("koala.png");
	PhysicsComponent *physicsComponent = new PhysicsComponent(physicsTransform, PhysicsComponent::DYNAMIC);
	physicsObject->setColor(vg::Color(255, 0, 0));
	snowboard->addComponent(physicsComponent);
	snowboard->addComponent(physicsTransform);
	snowboard->addComponent(physicsObject);
	snowboard->getComponent<PhysicsComponent>()->setFriction(0.7);
	snowboard->getComponent<PhysicsComponent>()->setDensity(100);

	scene->addGameObject(snowboard);
	
	// Jumping muumi
	TransformComponent *muumiTransform = new TransformComponent(Vec2f(10, -10),
		Vec2f(64, 64), -45.0f);

	muumiObject = new GameObject("muumiObject");
	muumiObject->addComponent(muumiTransform);
	PhysicsComponent *muumiPhysics = new PhysicsComponent(muumiTransform, PhysicsComponent::DYNAMIC, 54);
	RenderComponent *muumiAnimation = new RenderComponent("papparunSmall2.png");

	muumiObject->addComponent(new AnimationComponent(0.04, 3, 8, 24));
	muumiObject->addComponent(muumiAnimation);
	muumiObject->addComponent(muumiPhysics);
	muumiObject->getComponent<PhysicsComponent>()->setFriction(300);
	muumiObject->getComponent<PhysicsComponent>()->setAngularDamping(5);

	scene->addGameObject(muumiObject);
	
	muumiJoint = new Joint(muumiPhysics, physicsComponent);
	muumiJoint->createRevoluteJoint();
	
	muumiJoint->setAnchorA(Vec2f(0, 36));
	muumiJoint->enableLimits(-50, 50, true);

	// 520, 528 * 5
	float lowX = 520 * 5;
	float lowY = 528 * 5;
	
	listOfCustomPoints.push_back(Vec2f(lowX, lowY + 500));
	listOfCustomPoints.push_back(Vec2f(lowX + 10000, lowY + 500));
	listOfCustomPoints.push_back(Vec2f(listOfCustomPoints[1].x, listOfCustomPoints[1].y - 1000));

	// land texture
	for (int i = 0; i < listOfCustomPoints.size()-1; i++)
	{
		TransformComponent *hillPartTransformNew = new TransformComponent(Vec2f(listOfCustomPoints[i].x, listOfCustomPoints[i].y), 10,
			Vec2f(listOfCustomPoints[i + 1].x, listOfCustomPoints[i+1].y));

		GameObject *hillPartObjectNew = new GameObject("hillPart1");
		RenderComponent *hillPartQuadNew = new RenderComponent("koala.png");
		hillPartQuadNew->setColor(vg::Color(0, 0, 0));
		hillPartObjectNew->addComponent(hillPartTransformNew);
		hillPartObjectNew->addComponent(hillPartQuadNew);

		scene->addGameObject(hillPartObjectNew);
	}
	TransformComponent *landTransform = new TransformComponent(Vec2f(0, 0),
		Vec2f(0, 0));

	landingZone = new GameObject("landingZone");

	PhysicsComponent *landPhysics = new PhysicsComponent(landTransform, listOfCustomPoints);

	landingZone->addComponent(landPhysics);
	landingZone->addComponent(landTransform);
	landingZone->getComponent<PhysicsComponent>()->setFriction(0.7);

	scene->addGameObject(landingZone);
	
	// Create scenery
	for (int i = listOfCustomPoints.at(0).x; i <= listOfCustomPoints.at(1).x; i += 500)
	{
		// Muumi distance text
		GameObject *muumiDistanceTextObject = new GameObject("MuumiDistance");
		TextComponent* MuumiDistanceText = new TextComponent("arial.ttf", 8);
		TransformComponent* MuumiDistanceTransform = new TransformComponent((Vec2f(i, listOfCustomPoints.at(0).y)));
		
		std::stringstream stream;
		stream << i / 100 - listOfCustomPoints[1].x / 100 + 100 << " m";
		MuumiDistanceText->setText(stream.str());

		MuumiDistanceText->setColor(255, 255, 255);
		muumiDistanceTextObject->addComponent(MuumiDistanceText);
		muumiDistanceTextObject->addComponent(MuumiDistanceTransform);

		scene->addGameObject(muumiDistanceTextObject);
	}
	core::AssetManager *assetManager = Game::getInstance()->getAssetManager();
	/*assetManager->load<sound::Sound>("shoot.mp3");
	assetManager->load<sound::Sound>("NOMORESLOMO.mp3");
	sound::Sound slomoSound = *assetManager->get<sound::Sound>("Raise your Kappa!.mp3");
	Game::getInstance()->getAudioManager()->addSound("slomo", slomoSound);

	sound::Sound noslomoSound = *assetManager->get<sound::Sound>("NOMORESLOMO.mp3");
	Game::getInstance()->getAudioManager()->addSound("noslomo", noslomoSound);*/
	Game::getInstance()->getAssetManager()->load<sound::Sound>("SLOMO.mp3");
	Game::getInstance()->getAssetManager()->load<sound::Sound>("NOMORESLOMO.mp3");

	Game::getInstance()->getAudioManager()->addSound("nomoreslomo",
		*assetManager->get<sound::Sound>("NOMORESLOMO.mp3"));



	GameObject* background1 = new GameObject("BG1");
	GameObject* background2 = new GameObject("BG2");
	TransformComponent* bgTransform1 = new TransformComponent(Vec2f(0 - Screen::getX() * 0.10, 0), Screen::getSize(), 0, Vec2f(0, 0), vg::TransformComponent::LayerGroup::BOTTOM,false);
	TransformComponent* bgTransform2 = new TransformComponent(Vec2f(Screen::getX() - Screen::getX() * 0.10, 0), Screen::getSize(), 0, Vec2f(0, 0), vg::TransformComponent::LayerGroup::BOTTOM,false);
	RenderComponent* bgRender1 = new RenderComponent("winter_scrolling.png");
	RenderComponent* bgRender2 = new RenderComponent("winter_scrolling.png");

	background1->addComponent(bgTransform1);
	background1->addComponent(bgRender1);
	background2->addComponent(bgTransform2);
	background2->addComponent(bgRender2);

	scene->addGameObject(background1);
	scene->addGameObject(background2);
	slomo_acceleration = 1.0f;

	/*
	Power bar initialization
	*/
	powerbar = new GameObject("PowerBar");
	TransformComponent *barTransform = new TransformComponent(Vec2f(-1000, 30),
		Vec2f(32, 126), 0.0f, Vec2f(0, 0));
	powerbar->addComponent(barTransform);
	RenderComponent* powerRender = new RenderComponent("bar.png");
	powerbar->addComponent(powerRender);
	bState = INCREASING;
	powerbarOn = false;
	jumped = false;
	barYIncrement = 0.0f;
	scene->addGameObject(powerbar);
}

void JumpSystem::update(std::vector<vg::GameObject*> *gameObjects, float deltaTime)
{	
	Camera::setPosition(Vec2f(muumiObject->getComponent<TransformComponent>()->getWorldPosition().x - Screen::getX() * 0.5,
		muumiObject->getComponent<TransformComponent>()->getWorldPosition().y - Screen::getY() * 0.5));

	background->getComponent<TransformComponent>()->setPosition(Camera::getPosition());

	if (launched)
	{
		// Jump distance
		jumpDistance = muumiObject->getComponent<TransformComponent>()->getWorldPosition().x + (listOfCustomPoints[1].x - listOfCustomPoints[0].x);
		std::stringstream stream;
		float distance = jumpDistance / 100 - listOfCustomPoints[1].x / 100;
		if (distance < 0)
			distance = 0;
		stream << "Distance: " << distance << "m";
		textObject->getComponent<TextComponent>()->setText(stream.str());
	}

	float snowboardY = snowboard->getComponent<TransformComponent>()->getWorldPosition().y;
	float groundY = listOfCustomPoints[0].y;
	if (sqrt(pow(snowboardY - groundY, 2)) < 400.0f && slomo_state == NO_SLOMO)
	{
		slomo_state = SLOMO;
		core::AssetManager *assetManager = Game::getInstance()->getAssetManager();
		Game::getInstance()->getAudioManager()->addSound("slomo",
			*assetManager->get<sound::Sound>("SLOMO.mp3"));
		Game::getInstance()->getAudioManager()->play("slomo");
		Game::getInstance()->getAudioManager()->loopEnabled("slomo", false); 
		if (snowboard->getComponent<PhysicsComponent>()->getVelocity().y <= -60.0f)
		{
			slomo_acceleration = 5.0f;
		}
		//std::cout << "Velocity: " << snowboard->getComponent<PhysicsComponent>()->getVelocity().y<< std::endl;
	}
	else if (slomo_state == SLOMO)
	{
		if (system->getTimeStep() > SLOMO_TIME_STEP)
		{
			float stepbefore = SLOMO_TIME_STEP_INCREASE;
			float step = system->getTimeStep() -  (stepbefore * slomo_acceleration);
			slomo_acceleration += 0.1f;
			system->setTimeStep(step);
		}
		else
			system->setTimeStep(SLOMO_TIME_STEP);
	}
	else if (slomo_state == SLOMO_ENDING)
	{
		if (slomoTimer.getCurrentTimeSeconds() >= ( SLOMO_TIME - 0.5f ))
		{
			slomo_state = SLOMO_MUSIC_STARTED;
			core::AssetManager *assetManager = Game::getInstance()->getAssetManager();
			Game::getInstance()->getAudioManager()->addSound("nomoreslomo",
				*assetManager->get<sound::Sound>("NOMORESLOMO.mp3"));

			Game::getInstance()->getAudioManager()->play("nomoreslomo");
			Game::getInstance()->getAudioManager()->loopEnabled("nomoreslomo", false);

		}
	}
	else if (slomo_state == SLOMO_MUSIC_STARTED)
	{
		if (slomoTimer.getCurrentTimeSeconds() >= SLOMO_TIME)
		{
			slomo_state = SLOMO_DONE;
			system->setTimeStep(DEFAULT_TIME_STEP);

		}
	
	}
	vg::Vec2f clickPos;
	vg::Vec2f ballPos = muumiObject->getComponent<TransformComponent>()->getWorldPosition();

	bool isInputDown = false;
#ifdef OS_WINDOWS
	if (input::Keyboard::getKeyState(vg::input::Keyboard::Space) == vg::input::Keyboard::KeyState::PRESSED)
	{
		clickPos = vg::input::Mouse::getPos();
		isInputDown = true;
	}

#endif

#ifdef OS_ANDROID
		if (input::Touch::getIsTouched())
		{
			clickPos = input::Touch::getPos();
			isInputDown = true;
		}
#endif
		if (!jumped)
		{
			if (isInputDown)
			{
				if (!powerbarOn)
				{
					barTexCoords[0] = glm::vec2(0, 0);
					barTexCoords[1] = glm::vec2(0, 0);
					barTexCoords[2] = glm::vec2(1, 0);
					barTexCoords[3] = glm::vec2(1, 0);
					powerbar->getComponent<RenderComponent>()->setTexCoords(barTexCoords);
				}
				powerbarOn = true;

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
				powerbar->getComponent<TransformComponent>()->setSize(vg::Vec2f(32, 126 * barYIncrement));
				powerbar->getComponent<TransformComponent>()->setPosition(vg::Vec2f(ballPos.x, ballPos.y - (126 * barYIncrement) - 50));
				powerbar->getComponent<RenderComponent>()->setTexCoords(barTexCoords);
			}
			else if(powerbarOn)
			{
				launchPower = barYIncrement * 50;
				Launch();
				jumped = true;
				powerbarOn = false;
			}
			//powerbar->getComponent<TransformComponent>()->setPosition(vg::Vec2f(ballPos.x, ballPos.y - (126 * barYIncrement) - 50));
		}
	


#ifdef OS_WINDOWS

	if (vg::input::Keyboard::getKeyState(vg::input::Keyboard::S) == vg::input::Keyboard::KeyState::PRESSED)
	{
		reset();
	}

	if (vg::input::Keyboard::getKeyState(vg::input::Keyboard::A) == vg::input::Keyboard::KeyState::PRESSED && muumiJoint->connected)
	{
		tiltLeft();
	}
	if (vg::input::Keyboard::getKeyState(vg::input::Keyboard::D) == vg::input::Keyboard::KeyState::PRESSED && muumiJoint->connected)
	{
		tiltRight();
	}

	if (vg::input::Keyboard::getKeyState(vg::input::Keyboard::Numpad1) == vg::input::Keyboard::KeyState::PRESSED)
	{
		system->setTimeStep(system->getTimeStep() - 0.0005);
	}
	if (vg::input::Keyboard::getKeyState(vg::input::Keyboard::Numpad2) == vg::input::Keyboard::KeyState::PRESSED)
	{
		system->setTimeStep(system->getTimeStep() + 0.0005);
	}
	if (vg::input::Keyboard::getKeyState(vg::input::Keyboard::Numpad3) == vg::input::Keyboard::KeyState::PRESSED)
	{
		snowboard->getComponent<PhysicsComponent>()->setVelocity(Vec2f(snowboard->getComponent<PhysicsComponent>()->getVelocity().x + 1000,
			snowboard->getComponent<PhysicsComponent>()->getVelocity().y ));
	}

#endif

#ifdef OS_ANDROID

	if (Touch::getIsTouched() && muumiJoint->connected && !launched)
	{
		prepareLaunch();
	}

	else if ((Touch::getIsReleased() && muumiJoint->connected && !launched) || launchPower >= 50 )
	{
		Launch();
	}

	if (Touch::getIsTouched() && muumiJoint->connected)
	{
		if (Touch::getPos(false).x > Screen::getX() / 2)
		{
			tiltRight();
		}
		else if (Touch::getPos(false).x < Screen::getX() / 2)
		{
			tiltLeft();
		}
	}
	if (Touch::getIsTouched() && launched)
	{
		if (Touch::getPos(false).y < 100)
		{
			reset();
		}
	}
#endif

	backgroundUpdate(gameObjects);
}

void JumpSystem::onHit(vg::GameObject *other, vg::GameObject *other2)
{
	if (other->getName() == "muumiObject" && other2->getName() == "landingZone" ||
		other2->getName() == "muumiObject" && other->getName() == "landingZone")
	{
		if (muumiJoint->connected)
		{	
			// check if muumi is standing up
			if (muumiObject->getComponent<PhysicsComponent>()->getRotation() > 30 ||
				muumiObject->getComponent<PhysicsComponent>()->getRotation() < -30)
			{	
				muumiJoint->removeJoint();
			}
		}
		if (slomo_state == SLOMO)
		{
			slomo_state = SLOMO_ENDING;
			slomoTimer.restart();
		}
	}


	if (other->getName() == "physicsTest1" && other2->getName() == "landingZone" ||
		other2->getName() == "physicsTest1" && other->getName() == "landingZone")
	{

		if (muumiJoint->connected)
		{
			// check if muumi is standing up
			if (snowboard->getComponent<PhysicsComponent>()->getRotation() > 15 ||
				snowboard->getComponent<PhysicsComponent>()->getRotation() < -15)
			{
				muumiJoint->removeJoint();
			}
		}
		if (slomo_state == SLOMO)
		{
			slomo_state = SLOMO_ENDING;
			slomoTimer.restart();
		}
	}
}

void JumpSystem::prepareLaunch()
{
	if (launchPower < 50)
	{
		// launch power
		launchPower++;
		std::stringstream stream;
		stream << "Power: " << launchPower << " big boy watts";
		powerTextObject->getComponent<TextComponent>()->setText(stream.str());
	}
}

void JumpSystem::Launch()
{
	snowboard->getComponent<PhysicsComponent>()->setVelocity(Vec2f(snowboard->getComponent<PhysicsComponent>()->getVelocity().x + launchPower,
		snowboard->getComponent<PhysicsComponent>()->getVelocity().y + launchPower));
	jumpPosition = snowboard->getComponent<TransformComponent>()->getWorldPosition().x;
	launchPower = 0;
	launched = true;
}

void JumpSystem::tiltLeft()
{
	muumiObject->getComponent<PhysicsComponent>()->setAngularVelocity(snowboard->getComponent<PhysicsComponent>()->getAngularVelocity() + 2.5);
	snowboard->getComponent<PhysicsComponent>()->setAngularVelocity(snowboard->getComponent<PhysicsComponent>()->getAngularVelocity() + 0.5);
}

void JumpSystem::tiltRight()
{
	muumiObject->getComponent<PhysicsComponent>()->setAngularVelocity(snowboard->getComponent<PhysicsComponent>()->getAngularVelocity() - 2.5);
	snowboard->getComponent<PhysicsComponent>()->setAngularVelocity(snowboard->getComponent<PhysicsComponent>()->getAngularVelocity() - 0.5);
}

void JumpSystem::reset()
{
	snowboard->getComponent<PhysicsComponent>()->setPosition(Vec2f(10, -10));
	snowboard->getComponent<PhysicsComponent>()->setAngularVelocity(0);
	snowboard->getComponent<PhysicsComponent>()->setVelocity(Vec2f(0, 0));
	snowboard->getComponent<PhysicsComponent>()->setRotation(-45);

	muumiObject->getComponent<PhysicsComponent>()->setPosition(Vec2f(10, -10));
	muumiObject->getComponent<PhysicsComponent>()->setAngularVelocity(0);
	muumiObject->getComponent<PhysicsComponent>()->setVelocity(Vec2f(0, 0));
	muumiObject->getComponent<PhysicsComponent>()->setRotation(-45);
	muumiObject->getComponent<PhysicsComponent>()->setAngularDamping(5);
	muumiObject->getComponent<PhysicsComponent>()->setDensity(1);
	muumiObject->getComponent<PhysicsComponent>()->wake(true);

	launchPower = 0;
	jumpDistance = 0;
	jumpPosition = 0;
	launched = false;
	textObject->getComponent<TextComponent>()->setText("");
	powerTextObject->getComponent<TextComponent>()->setText("");
	system->setTimeStep(1.0f / 60.0f); // Default timestep
	slomo_state = NO_SLOMO;
	slomo_acceleration = 0.1f;
	if (!muumiJoint->connected)
		muumiJoint->createRevoluteJoint();

	jumped = false;
	powerbar->getComponent<TransformComponent>()->setPosition(Vec2f(-1000, 30));

	bState = INCREASING;
	barYIncrement = 0.0f;
	
}
void JumpSystem::backgroundUpdate(std::vector<vg::GameObject*> *gameObjects)
{
	GameObject* background1;
	GameObject* background2;
	string objectName;

	TransformComponent* background1Trans;
	TransformComponent* background2Trans;

	for (auto it = gameObjects->begin(); it < gameObjects->end(); it++)
	{
		objectName = (*it)->getName();

		if (objectName == "BG1")
		{
			background1 = (*it);
			background1Trans = (*it)->getComponent<TransformComponent>();
		}

		if (objectName == "BG2")
		{
			background2 = (*it);
			background2Trans = (*it)->getComponent<TransformComponent>();
		}

	}


		vg::Vec2f back1Vec = vg::Vec2f(-Camera::getPosition().x, 0);


		if (back1Vec.x < -background1Trans->getSize().x)
		{
			int verymage = floor(sqrt(pow(back1Vec.x, 2.0f)) / background1Trans->getSize().x);
			back1Vec.x += verymage * background1Trans->getSize().x;
		}
		else if (back1Vec.x > 0)
		{
			back1Vec.x -= background1Trans->getSize().x;
		}
		background1Trans->setPosition(back1Vec);
		vg::Vec2f back2Vec = vg::Vec2f(background1Trans->getWorldPosition().x + background1Trans->getSize().x, 0);

		background2Trans->setPosition(back2Vec);
	
	
}