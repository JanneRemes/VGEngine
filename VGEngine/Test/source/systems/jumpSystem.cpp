
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
	
	muumiJoint->setAnchorA(Vec2f(0, 35));
	muumiJoint->enableLimits(-50, 50, true);

	// 520, 528 * 5
	float lowX = 520 * 5;
	float lowY = 528 * 5;
	
	float steep = 1; // Hill landing steepness modifier
	listOfCustomPoints.push_back(Vec2f(lowX, lowY + 250));
	listOfCustomPoints.push_back(Vec2f(lowX + 10000, lowY + 250 * steep));
	
	// land texture
	TransformComponent *hillPartTransformNew = new TransformComponent(Vec2f(listOfCustomPoints[0].x, listOfCustomPoints[0].y), 10,
		Vec2f(listOfCustomPoints[1].x, listOfCustomPoints[1].y));

	GameObject *hillPartObjectNew = new GameObject("hillPart1");
	RenderComponent *hillPartQuadNew = new RenderComponent("koala.png");
	hillPartQuadNew->setColor(vg::Color(0, 0, 0));
	hillPartObjectNew->addComponent(hillPartTransformNew);
	hillPartObjectNew->addComponent(hillPartQuadNew);

	scene->addGameObject(hillPartObjectNew);

	TransformComponent *landTransform = new TransformComponent(Vec2f(0, 0),
		Vec2f(0, 0));

	landingZone = new GameObject("landingZone");

	PhysicsComponent *landPhysics = new PhysicsComponent(landTransform, listOfCustomPoints);

	landingZone->addComponent(landPhysics);
	landingZone->addComponent(landTransform);
	landingZone->getComponent<PhysicsComponent>()->setFriction(0.7);

	scene->addGameObject(landingZone);
	
	// Create scenery
	for (int i = listOfCustomPoints.at(0).x; i < listOfCustomPoints.at(1).x; i += 500)
	{
		// Muumi distance text
		GameObject *muumiDistanceTextObject = new GameObject("MuumiDistance");
		TextComponent* MuumiDistanceText = new TextComponent("arial.ttf", 8);
		TransformComponent* MuumiDistanceTransform = new TransformComponent((Vec2f(i, lowY + 225 + 3*8 + 10)));
		
		std::stringstream stream;
		stream <<  i / 100 << " m";
		MuumiDistanceText->setText(stream.str());

		MuumiDistanceText->setColor(255, 255, 255);
		muumiDistanceTextObject->addComponent(MuumiDistanceText);
		muumiDistanceTextObject->addComponent(MuumiDistanceTransform);

		scene->addGameObject(muumiDistanceTextObject);
	}
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
		stream << "Distance: " << jumpDistance / 100 - 100 << "m";
		textObject->getComponent<TextComponent>()->setText(stream.str());
		
		if (!muumiJoint->connected)
		{
			//muumiObject->getComponent<PhysicsComponent>()->setAngularDamping(1000);
			//muumiObject->getComponent<PhysicsComponent>()->setDensity(1000);
			//snowboard->getComponent<PhysicsComponent>()->setAngularVelocity(100);
		}
	}
#ifdef OS_WINDOWS

	if (vg::input::Keyboard::getKeyState(vg::input::Keyboard::S) == vg::input::Keyboard::KeyState::PRESSED)
	{
		reset();
	}

	if (vg::input::Keyboard::getKeyState(vg::input::Keyboard::Space) == vg::input::Keyboard::KeyState::PRESSED && muumiJoint->connected && !launched)
	{
		prepareLaunch();
	}
	else if ((vg::input::Keyboard::getKeyState(vg::input::Keyboard::Space) == vg::input::Keyboard::KeyState::UP && muumiJoint->connected && !launched) || launchPower >= 50)
	{
		Launch();
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

	if (Touch::getIsTouched() && launched)
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
#endif
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

	if (!muumiJoint->connected)
		muumiJoint->createRevoluteJoint();
}