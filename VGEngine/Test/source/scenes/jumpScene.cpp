
#include "scenes/jumpScene.h"

#include "engine/game/transformComponent.h"
#include "engine/game/renderComponent.h"
#include "systems/sceneChangeSystem.h"
#include "engine/game/animationComponent.h"
#include "engine/game/textComponent.h"
#include "engine\graphics\screen.h"
#include "engine/game/game.h"

#include "systems\jumpSystem.h"

using namespace vg;

JumpScene::JumpScene()
{
}

JumpScene::~JumpScene()
{
}

void JumpScene::loadObjects()
{
	core::AssetManager* assetManager = Game::getInstance()->getAssetManager();
	
	// koala platform
	TransformComponent *physicsTransform2 = new TransformComponent(Vec2f(1000, 300),
		Vec2f(500, 100));

	GameObject *physicsTest2 = new GameObject("physicsTest2");
	RenderComponent *physicsRender2 = new RenderComponent("koala.png");

	PhysicsComponent *physicsPolyComponent2 = new PhysicsComponent(physicsTransform2, PhysicsComponent::STATIC);

	physicsTest2->addComponent(physicsPolyComponent2);
	physicsTest2->addComponent(physicsTransform2);
	physicsTest2->addComponent(physicsRender2);

	addGameObject(physicsTest2);
	
	// custom physics shape
	std::vector<Vec2f> listOfCustomPoints;
	const int hillSize = 18;
	float hill[hillSize] = {
		0, 0,
		400, 500,
		415, 510,
		425, 515,
		440, 520,
		460, 525,
		480, 530,
		500, 530,
		520, 528 };

	hillSizeModifier = 5;
	lowestPoint = hill[hillSize] * hillSizeModifier;

	// Create hill from array
	for (int i = 0; i < hillSize; i += 2)
	{
		listOfCustomPoints.push_back(Vec2f(hill[i] * hillSizeModifier, hill[i + 1] * hillSizeModifier));
		std::cout << hill[i] * hillSizeModifier << " " << hill[i + 1] * hillSizeModifier << std::endl;

		float distance = sqrt((hill[i] - hill[i + 2])*(hill[i] - hill[i + 2]) +
				(hill[i + 1] - hill[i + 3])*(hill[i + 1] - hill[i + 3]));

		float deltaY = hill[i + 3] - hill[i + 1];
		float deltaX = hill[i + 2] - hill[i];
		float angleInDegrees = atan2(deltaY, deltaX) * 180 / 3.1415;

		// hill texturing parts
		TransformComponent *hillPartTransformNew = new TransformComponent(Vec2f(hill[i] * hillSizeModifier, hill[i + 1] * hillSizeModifier),
			Vec2f(distance * hillSizeModifier, 10), angleInDegrees);

		GameObject *hillPartObjectNew = new GameObject("hillPart");
		RenderComponent *hillPartQuadNew = new RenderComponent("koala.png");

		hillPartObjectNew->addComponent(hillPartTransformNew);
		hillPartObjectNew->addComponent(hillPartQuadNew);

		addGameObject(hillPartObjectNew);
	}

	/*
	// Circle collision shape
	for (int i = 0; i < 15; i++)
	{
		listOfCustomPoints.push_back(Vec2f(sin(i) * 100 + 200, cos(i) * 100 + 200));
		std::cout << listOfCustomPoints[i].x << " " << listOfCustomPoints[i].y << std::endl;
	}
	*/

	TransformComponent *hillTransform = new TransformComponent(Vec2f(0, 0),
		Vec2f(0, 0));

	GameObject *hillObject = new GameObject("hillObject");

	PhysicsComponent *hillPhysics = new PhysicsComponent(hillTransform, listOfCustomPoints);

	hillObject->addComponent(hillPhysics);
	hillObject->addComponent(hillTransform);
	hillObject->getComponent<PhysicsComponent>()->setFriction(0.1);

	addGameObject(hillObject);

	// Jump systems
	JumpSystem *jumpSystem = new JumpSystem(this);
	Game::getInstance()->addComponentSystem(this, jumpSystem);
	
	// Scene change system
	sceneChangeSystem *sceneChange = new sceneChangeSystem(this);
	Game::getInstance()->addComponentSystem(this, sceneChange);
}
