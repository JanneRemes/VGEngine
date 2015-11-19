#include <math.h>
#include "systems\androidLaunchSystem.h"
#include "engine\input\mouse.h"
#include "engine\game\quadrangleComponent.h"
#include "engine\utility\logger.h"
#include "engine/graphics/screen.h"

using namespace vg;
using namespace graphics;

AndroidLaunchSystem::AndroidLaunchSystem(Scene *scene)
{
	this->scene = scene;
	physicSystem = Game::getInstance()->getSceneManager()->getActiveScene()->getComponentSystemManager()->getSystem<PhysicsSystem>();

	core::AssetManager* assetManager = Game::getInstance()->getAssetManager();
	android = new GameObject("Android");
	TransformComponent *androidTransform = new TransformComponent(Vector2<float>(60, Screen::getY() - 40),
		Vector2<float>(32, 32), 0.0f, Vector2<float>(0, 0));
	android->addComponent(androidTransform);
	QuadrangleComponent *quadre = new QuadrangleComponent("android.png");
	android->addComponent(quadre);
	android->addComponent(new PhysicsCircleComponent(androidTransform, PhysicsComponent::DYNAMIC, 0));

	android->getComponent<PhysicsCircleComponent>()->setFriction(0.90);
	android->getComponent<PhysicsCircleComponent>()->setRestitution(0.60);
	android->getComponent<PhysicsCircleComponent>()->setDensity(100);

	scene->addGameObject(android);

	powerBar = new GameObject("PowerBar");
	TransformComponent *barTransform = new TransformComponent(Vector2<float>(100, 30),
		Vector2<float>(32, 126), 0.0f, Vector2<float>(0, 0));
	powerBar->addComponent(barTransform);
	QuadrangleComponent *powerRender = new QuadrangleComponent("bar.png");
	powerBar->addComponent(powerRender);

	scene->addGameObject(powerBar);

	physicSystem->createBorders(0, 0, Screen::getX(), Screen::getY());

	bState = INCREASING;
	mouseIsDown = false;
	isShot = false;
	barYIncrement = 0.0f;
	defaultPos.setX(60);
	defaultPos.setY(Screen::getY() - 60);
	speed = 100;
	powerBar->getComponent<TransformComponent>()->setPosition(vg::Vector2<float>(-60, 200));
}
AndroidLaunchSystem::~AndroidLaunchSystem()
{

}
void AndroidLaunchSystem::update(std::vector<vg::GameObject*> *gameObjects, float deltaTime)
{
#ifdef OS_WINDOWS
	
	if (isShot == false)
	{
		if (vg::input::Mouse::isKeyPressed(vg::input::RIGHT))
		{
			clickPos = vg::input::Mouse::getPos();
			ballPos = android->getComponent<TransformComponent>()->getWorldPosition();
			barTexCoords[0] = glm::vec2(0, 0);
			barTexCoords[1] = glm::vec2(0, 0);
			barTexCoords[2] = glm::vec2(1, 0);
			barTexCoords[3] = glm::vec2(1, 0);
			powerBar->getComponent<QuadrangleComponent>()->setTexCoords(barTexCoords);
			mouseIsDown = true;
		}

		else if (vg::input::Mouse::isKeyDown(vg::input::RIGHT))
		{

			if (bState == BarState::INCREASING)
			{
				barYIncrement += 0.03f;
				Log("vgengine", "TexInc = %f.2, increasing", barYIncrement);

				if (barYIncrement >= 1.0f)
				{
					bState = DECREASING;
				}
			}

			if (bState == BarState::DECREASING)
			{
				barYIncrement -= 0.03f;
				Log("vgengine", "TexInc = %f.2, decreasing", barYIncrement);
				if (barYIncrement <= 0.0f)
				{
					bState = INCREASING;
				}
			}


			barTexCoords[0] = glm::vec2(0, barYIncrement);
			barTexCoords[1] = glm::vec2(0, 0);
			barTexCoords[2] = glm::vec2(1, 0);
			barTexCoords[3] = glm::vec2(1, barYIncrement);
			powerBar->getComponent<TransformComponent>()->setSize(vg::Vector2<float>(32, 126 * barYIncrement));
			powerBar->getComponent<TransformComponent>()->setPosition(vg::Vector2<float>(ballPos.getX(), ballPos.getY() - (126 * barYIncrement) - 50));
			powerBar->getComponent<QuadrangleComponent>()->setTexCoords(barTexCoords);
		}

		else if (mouseIsDown == true)
		{
			mouseIsDown = false;
			isShot = true;

			powerBar->getComponent<TransformComponent>()->setPosition(vg::Vector2<float>(-60, 200));
			Log("vgengine", "Touchdown!", "");
			vg::Vector2<float> tempVec = vg::input::Mouse::getPos() - android->getComponent<TransformComponent>()->getWorldPosition();
			normalizedVec = normalize(tempVec);

			vg::Vector2<float> velocity = vg::Vector2<float>(normalizedVec.getX() * barYIncrement * speed, normalizedVec.getY() * barYIncrement * speed);
			android->getComponent<PhysicsCircleComponent>()->setVelocity(vg::Vector2<float>(velocity.getX(), -velocity.getY()));
		}
	}

	else
	{
		if (vg::input::Mouse::isKeyPressed(vg::input::MIDDLE))
		{	
			android->getComponent<TransformComponent>()->setPosition(defaultPos);		
			android->getComponent<PhysicsCircleComponent>()->setVelocity(vg::Vector2<float>(0.0f, 0.0f));
			android->getComponent<TransformComponent>()->setRotation(0.0f);
			isShot = false;
		}
	}

#endif

#ifdef OS_ANROID

	if (vg::input::Touch::getIsTouched())
	{
		vg::Vector2<float> pos = vg::input::Touch::getPos();

		vg::Vector2<float> velocity = pos - android->getComponent<TransformComponent>()->getWorldPosition();
		android->getComponent<PhysicsCircleComponent>()->setVelocity(vg::Vector2<float>(velocity.getX(), velocity.getY()));
	}
#endif
}

vg::Vector2<float> AndroidLaunchSystem::normalize(vg::Vector2<float> vec2)
{
	float magnitude = sqrt((vec2.getX() * vec2.getX()) + (vec2.getY() * vec2.getY()));

	vg::Vector2<float> normalizedVec;

	normalizedVec.setX(vec2.getX() / magnitude);
	normalizedVec.setY(vec2.getY() / magnitude);

	return normalizedVec;
}