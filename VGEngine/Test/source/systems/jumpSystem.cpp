
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
	//muumiObject->getComponent<PhysicsComponent>()->setFriction(0.7);
	//muumiObject->getComponent<PhysicsComponent>()->setDensity(100);
	muumiObject->getComponent<PhysicsComponent>()->setAngularDamping(5);

	scene->addGameObject(muumiObject);
	
	muumiJoint = new Joint(muumiPhysics, physicsComponent);
	muumiJoint->createRevoluteJoint();
	
	muumiJoint->setAnchorA(Vec2f(0, 35));
	muumiJoint->enableLimits(-50, 50, true);

	// Landing zone
	std::vector<Vec2f> listOfCustomPoints;

	// 520, 528 * 5
	float lowX = 520 * 5;
	float lowY = 528 * 5;
	
	listOfCustomPoints.push_back(Vec2f(lowX, lowY + 250));
	listOfCustomPoints.push_back(Vec2f(lowX + 10000, lowY + 250));
	
	// land texture
	TransformComponent *hillPartTransformNew = new TransformComponent(Vec2f(listOfCustomPoints[0].x, listOfCustomPoints[0].y),
		Vec2f(10000, 10));

	GameObject *hillPartObjectNew = new GameObject("hillPart");
	RenderComponent *hillPartQuadNew = new RenderComponent("koala.png");

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
}

void JumpSystem::update(std::vector<vg::GameObject*> *gameObjects, float deltaTime)
{
	Camera::setPosition(Vec2f(muumiObject->getComponent<TransformComponent>()->getWorldPosition().x - Screen::getX() * 0.5,
		muumiObject->getComponent<TransformComponent>()->getWorldPosition().y - Screen::getY() * 0.5));

	background->getComponent<TransformComponent>()->setPosition(Camera::getPosition());

	//// Collision checking with land
	//if (muumiObject->getComponent<PhysicsComponent>()->isHitting(landingZone))
	//{
	//	if (muumiJoint->connected)
	//	muumiJoint->removeJoint();
	//}
	
#ifdef OS_WINDOWS
	if (snowboard->getComponent<TransformComponent>()->getWorldPosition().y >= 528 * 5 + 1000 ||
		vg::input::Keyboard::getKeyState(vg::input::Keyboard::S) == vg::input::Keyboard::KeyState::PRESSED)
	{
		for (auto it = gameObjects->begin(); it != gameObjects->end(); it++)
		{
			if ((*it)->getName().find("physicsTest1") != -1)
			{
				PhysicsComponent* phys = (*it)->get<PhysicsComponent>();
				if (phys != nullptr)
				{
					phys->setPosition(Vec2f(10, -10));
					phys->setAngularVelocity(0);
					phys->setVelocity(Vec2f(0, 0));
					phys->setRotation(-45);

					muumiObject->getComponent<PhysicsComponent>()->setPosition(Vec2f(10, -10));
					muumiObject->getComponent<PhysicsComponent>()->setAngularVelocity(0);
					muumiObject->getComponent<PhysicsComponent>()->setVelocity(Vec2f(0, 0));
					muumiObject->getComponent<PhysicsComponent>()->setRotation(-45);
					muumiObject->getComponent<PhysicsComponent>()->wake(true);
					launchPower = 0;
					jumpDistance = 0;
					jumpPosition = 0;
					launched = false;
					textObject->getComponent<TextComponent>()->setText("");
					powerTextObject->getComponent<TextComponent>()->setText("");

					if (!muumiJoint->connected)
						muumiJoint->createRevoluteJoint();
				}
			}
		}
	}

	if (vg::input::Keyboard::getKeyState(vg::input::Keyboard::Space) == vg::input::Keyboard::KeyState::PRESSED)
	{
		if (launchPower < 50)
		{
			launchPower++;
			std::cout << launchPower << std::endl;

			// launch power
			std::stringstream stream;
			stream << "Power: " << launchPower << " big boy watts";
			powerTextObject->getComponent<TextComponent>()->setText(stream.str());
		}
	}
	else if (vg::input::Keyboard::getKeyState(vg::input::Keyboard::Space) == vg::input::Keyboard::KeyState::UP || launchPower >= 100)
	{
		snowboard->getComponent<PhysicsComponent>()->setVelocity(Vec2f(snowboard->getComponent<PhysicsComponent>()->getVelocity().x + launchPower,
			snowboard->getComponent<PhysicsComponent>()->getVelocity().y + launchPower));
		jumpPosition = snowboard->getComponent<TransformComponent>()->getWorldPosition().x;
		launchPower = 0;
		launched = true;
	}

	if (launched)
	{
		// Jump distance
		jumpDistance = muumiObject->getComponent<TransformComponent>()->getWorldPosition().x - jumpPosition;
		std::stringstream stream;
		stream << "Distance: " << jumpDistance / 100 << "m";
		textObject->getComponent<TextComponent>()->setText(stream.str());
	}

	if (vg::input::Keyboard::getKeyState(vg::input::Keyboard::A) == vg::input::Keyboard::KeyState::PRESSED)
	{
		muumiObject->getComponent<PhysicsComponent>()->setAngularVelocity(snowboard->getComponent<PhysicsComponent>()->getAngularVelocity() + 2.5);
		snowboard->getComponent<PhysicsComponent>()->setAngularVelocity(snowboard->getComponent<PhysicsComponent>()->getAngularVelocity() + 0.5);
	}
	if (vg::input::Keyboard::getKeyState(vg::input::Keyboard::D) == vg::input::Keyboard::KeyState::PRESSED)
	{
		muumiObject->getComponent<PhysicsComponent>()->setAngularVelocity(snowboard->getComponent<PhysicsComponent>()->getAngularVelocity() - 2.5);
		snowboard->getComponent<PhysicsComponent>()->setAngularVelocity(snowboard->getComponent<PhysicsComponent>()->getAngularVelocity() - 0.5);
	}

#endif

#ifdef OS_ANDROID
	
#endif
}
void JumpSystem::onHit(vg::GameObject *other, vg::GameObject *other2)
{
	if (other->getName() == "muumiObject" && other2->getName() == "landingZone" ||
		other2->getName() == "muumiObject" && other->getName() == "landingZone")
	{
		if (muumiJoint->connected)
		{
		muumiJoint->removeJoint();
		}
	}
}