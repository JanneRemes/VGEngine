
#include "scenes/cameraScene.h"
#include "systems/cameraSystem.h"
#include "systems/sceneChangeSystem.h"

#include "engine/game/transformComponent.h"
#include "engine/game/renderComponent.h"
#include "engine/game/animationComponent.h"
#include "engine/game/game.h"
#include "engine/game/textComponent.h"
#include "engine/graphics/screen.h"
#include "engine/utility/random.h"
#include "engine/game/physicsSystem.h"
#include "engine/utility/string.h"

using namespace vg;
using namespace vg::graphics;

CameraScene::CameraScene()
{
}

CameraScene::~CameraScene()
{
}

void CameraScene::loadObjects()
{
	Screen::setColor(vg::Color(50, 50, 150));

	CameraSystem* camSys = new CameraSystem();
	Game::getInstance()->addComponentSystem(this, camSys);

	sceneChangeSystem *sceneChange = new sceneChangeSystem(this);
	Game::getInstance()->addComponentSystem(this, sceneChange);

	//koala
	for (int i = 0; i < 30; i++)
	{
		GameObject* obj = new GameObject("test koala " + toStringi(i, 2));
		TransformComponent* transform = new TransformComponent(
			Vec2f(Random::nexti(500, 750), Random::nexti(300, 400)), Vec2f(64, 64),
			0.0f, Vec2f(32, 32));
		RenderComponent* render;
		if (i % 2)
		{
			render = new RenderComponent("koala.png");
			obj->add(new PhysicsComponent(transform, PhysicsComponent::DYNAMIC));
		}	
		else
		{
			render = new RenderComponent("skype_monkey2.png");
			obj->add(new PhysicsComponent(transform, PhysicsComponent::DYNAMIC, 60));
			obj->add(new AnimationComponent(Random::nextf(0.001f, 0.1f), 5, 10, 50));
		}
		render->setColor(vg::Color::random());
		obj->add(transform);
		obj->add(render);
		addGameObject(obj);
	}
	// origin test
	{
		GameObject* obj = new GameObject("origin test");
		TransformComponent* transform = new TransformComponent(
			Vec2f(900, 650), Vec2f(15, 15), 0.0f, Vec2f(0, 0), TransformComponent::HIGH);
		RenderComponent* quad = new RenderComponent();
		quad->setColor(vg::Color(200, 150, 100));
		obj->add(transform);
		obj->add(quad);
		addGameObject(obj);
	}

	//text
	string str = "aAbBcCdDeEfFgGhHiIjJkKlLmMnNoOpPqQrRsStTuUvVxXyYzZ";
	for (int i = 0; i < 3; i++)
	{
		reverse(str.begin(), str.end());
		int size = 12 + 4 * i;
		TextComponent* text = new TextComponent("arial.ttf", size);
		text->setText(str);
		text->setColor(255 - i * 64, 255 - i * 96, 255 - i * 128);
		GameObject* obj = new GameObject("koalatext");
		obj->add(new TransformComponent(Vec2f(-750, 660 + 2.5f * size * i), TransformComponent::LOW));
		obj->add(text);
		addGameObject(obj);
	}

	//timer text
	{
		TextComponent* text = new TextComponent("arial.ttf", 46);
		text->setText("1");
		text->setColor(0, 255, 0);
		GameObject* obj = new GameObject("timer text");
		obj->add(new TransformComponent(Vec2f(600, 0), TransformComponent::TOP, false));
		obj->add(text);
		addGameObject(obj);
	}

	//border
	//left
	createBorder(Vec2f(-200, -1000), Vec2f(0, 500));
	createBorder(Vec2f(0, 500), Vec2f(640, 720 - 64));
	//right
	createBorder(Vec2f(640, 720 - 64), Vec2f(1280, 500));
	createBorder(Vec2f(1280, 500), Vec2f(1480, -1000));
	//top
	createBorder(Vec2f(-200, -1000), Vec2f(1480, -1000));

	//spinner
	{
		GameObject* obj = new GameObject("spinner");
		TransformComponent* transform = new TransformComponent(Vec2f(640 - 150, 400), 8, Vec2f(640 + 150, 400));
		obj->add(transform);
		PhysicsComponent* physics =	new PhysicsComponent(transform, PhysicsComponent::DYNAMIC);
		obj->add(physics);
		RenderComponent* quad = new RenderComponent();
		quad->setColor(vg::Color(128, 255, 128));
		obj->add(quad);
		addGameObject(obj);

		GameObject* obj2 = new GameObject("spinner middle");
		TransformComponent* transform2 = new TransformComponent(Vec2f(640, 400), TransformComponent::BOTTOM);
		obj2->add(transform2);
		PhysicsComponent* physics2 = new PhysicsComponent(transform2, PhysicsComponent::STATIC);
		obj2->add(physics2);
		add(obj2);

		Joint *joint;
		joint = new Joint(physics, physics2);
		joint->createRevoluteJoint();
	}
}

void CameraScene::createBorder(Vec2f lt, Vec2f rt)
{
	GameObject* obj = new GameObject("border");
	TransformComponent* transform = new TransformComponent(lt, 8, rt);
	obj->add(transform);
	obj->add(new PhysicsComponent(transform, PhysicsComponent::STATIC));
	RenderComponent* quad = new RenderComponent();
	quad->setColor(vg::Color(128, 255, 128));
	obj->add(quad);
	addGameObject(obj);
}
