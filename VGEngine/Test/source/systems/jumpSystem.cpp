
#include "systems/jumpSystem.h"

#ifdef OS_WINDOWS
#include "engine/input/mouse.h"
#include "engine\input\keyboard.h"
#endif
#ifdef OS_ANDROID
#include "engine/input/touch.h"
#endif

#include "engine/game/quadrangleComponent.h"
#include "engine/game/game.h"

#include "engine/game/animationComponent.h"
#include "engine/game/animationSystem.h"
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
	
	// Player
	physicsTest = new GameObject("physicsTest1");

	TransformComponent *physicsTransform = new TransformComponent(Vec2f(10, 10),
		Vec2f(128, 32), -45.0f);

	QuadrangleComponent *physicsObject = new QuadrangleComponent("koala.png");
	PhysicsComponent *physicsComponent = new PhysicsComponent(physicsTransform, PhysicsComponent::DYNAMIC);

	physicsTest->addComponent(physicsComponent);
	physicsTest->addComponent(physicsTransform);
	physicsTest->addComponent(physicsObject);
	//physicsTest->getComponent<PhysicsComponent>()->setFriction(0.8);

	scene->addGameObject(physicsTest);

}
void JumpSystem::update(std::vector<vg::GameObject*> *gameObjects, float deltaTime)
{
	Camera::setPosition(Vec2f(physicsTest->getComponent<TransformComponent>()->getWorldPosition().x - Screen::getX() * 0.5, physicsTest->getComponent<TransformComponent>()->getWorldPosition().y - Screen::getY() * 0.5));

#ifdef OS_WINDOWS
	if (vg::input::Keyboard::getKeyState(vg::input::Keyboard::S) == vg::input::Keyboard::KeyState::PRESSED)
	{
		vg::Vec2f pos = vg::input::Mouse::getPos();
		physicsTest->getComponent<PhysicsComponent>()->setPosition(pos);
		physicsTest->getComponent<PhysicsComponent>()->setAngularVelocity(0);
		physicsTest->getComponent<PhysicsComponent>()->setVelocity(Vec2f(0, 0));
		physicsTest->getComponent<PhysicsComponent>()->setRotation(0);
		physicsTest->getComponent<PhysicsComponent>()->wake(true);
	}
#endif


#ifdef OS_ANDROID
	
#endif
}